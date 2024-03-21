//
//  Main.cpp provided under CC0 license
//

#include "sgct/sgct.h"
#include "websockethandler.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <memory>
#include <string>
#include <vector>
#include "assimp/Importer.hpp"
#include <AssimpLoader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "utility.h"
#include "objectValues.h"
#include "globals.h"
#include "player.h"
#include <cmath>
#include <GLFW/glfw3.h>

namespace {
    std::unique_ptr<WebSocketHandler> wsHandler;


    int64_t exampleInt = 0;
    std::string exampleString;
} // namespace

using namespace sgct;

std::unique_ptr<AssimpLoader> assimpLoader;
std::vector<std::unique_ptr<AssimpLoader>> objects;
GLuint shaderProgram;

const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos; // Position
layout (location = 1) in vec3 aNormal; // Normal vector

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 Normal; // Pass normal to the fragment shader
out vec3 FragPos; // Pass fragment position to the fragment shader

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Calculate normal for the fragment
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal; // Received from vertex shader
in vec3 FragPos; // Received from vertex shader

uniform vec3 lightPos; // Position of the light source in world space
uniform vec3 viewPos; // Position of the camera in world space
uniform vec3 lightColor; // Color of the light
uniform vec3 objectColor; // Color of the object

void main() {
    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine the two components
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}

)glsl";

void initOGL(GLFWwindow*) {
    glEnable(GL_DEPTH_TEST);
    GLint success;
    GLchar infoLog[1024];


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Set vertex shader source code and compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile errors...
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: VERTEX\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Set fragment shader source code and compile
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile errors...
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: FRAGMENT\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors...
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
    }

    // Delete shaders; they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Get the model via Assimp
    std::cout << "before file path \n";
    std::string filePath1 = "/Users/viktorsvensson/Desktop/MT/År 3/Termin 2/TNM094 - Kandidat/BachelorRep/candidateproject/SpaceDome/src/models/" + allModelNames[2] + ".fbx";
    std::string filePath2 = "/Users/viktorsvensson/Desktop/MT/År 3/Termin 2/TNM094 - Kandidat/BachelorRep/candidateproject/SpaceDome/src/models/" + allModelNames[4] + ".fbx";
    std::string filePath3 = "/Users/viktorsvensson/Desktop/MT/År 3/Termin 2/TNM094 - Kandidat/BachelorRep/candidateproject/SpaceDome/src/models/" + allModelNames[5] + ".fbx";



    assimpLoader = std::make_unique<AssimpLoader>(filePath1);

    objects.push_back(std::make_unique<AssimpLoader>(filePath2));
    objects.push_back(std::make_unique<AssimpLoader>(filePath3));
    std::cout << "after assimpLoader \n";
}


void preSync() {
    // Do the application simulation step on the server node in here and make sure that
    // the computed state is serialized and deserialized in the encode/decode calls

    if (Engine::instance().isMaster() && wsHandler->isConnected() &&
        Engine::instance().currentFrameNumber() % 100 == 0)
    {
        wsHandler->queueMessage("ping");
    }

    if (Engine::instance().isMaster()) {
        // This doesn't have to happen every frame, but why not?
        wsHandler->tick();
    }
}


std::vector<std::byte> encode() {
    // These are just two examples;  remove them and replace them with the logic of your
    // application that you need to synchronize
    std::vector<std::byte> data;
    serializeObject(data, exampleInt);
    serializeObject(data, exampleString);

    return data;
}


void decode(const std::vector<std::byte>& data) {
    // These are just two examples;  remove them and replace them with the logic of your
    // application that you need to synchronize
    unsigned pos = 0;
    deserializeObject(data, pos, exampleInt);
    deserializeObject(data, pos, exampleString);
}


void postSyncPreDraw() {
    // Apply the (now synchronized) application state before the rendering will start
}

GLuint compileShader(GLenum type, const char* source) {
    GLint success;
    GLchar infoLog[512];

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compile errors...
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
}
    return shader;
}

GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLint success;
    GLchar infoLog[512];
    
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors...
    glGetProgramiv(program, GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


std::vector<std::unique_ptr<Player>> players;
void addPlayer(int id, const std::string& name) {
    players.push_back(std::make_unique<Player>(id, name));
    std::cout << "Player: " << name << " joined with ID: " << id << std::endl;
}

void removePlayer(int id) {
    auto it = std::remove_if(players.begin(), players.end(), 
                             [id](const std::unique_ptr<Player>& player) {
                                return player->getID() == id;
                             });
    players.erase(it, players.end());
    std::cout << "Player with ID: " << id << " was removed.\n";
}



void draw(const RenderData& data) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    

if (!players.empty()) { 
    for (const auto& player : players) {
        player->draw(assimpLoader, shaderProgram); // If using unique_ptr
        // Or, if storing objects directly: player.draw(assimpLoader, shaderProgram);
        }
    }


    for(size_t i = 0; i < objects.size(); i++ ){
        glUseProgram(shaderProgram);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 500.0f, 0.1f, 100.0f);


    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 2.0f));
    glm::vec3 objectColor = glm::vec3(0.4f, 1.f, 0.2f);
    if(i == 0){
        objectColor = glm::vec3(1.f, 0.2f, 0.2f);
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -2.0f));
    }

    // Convert glm matrices to OpenGL format and set uniforms
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 viewPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Assuming you want to look at the origin
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f); //
    glm::mat4 viewMatrix = glm::lookAt(viewPos, cameraTarget, upDirection);

    
    // Set the matrices
    // And check so there are no problems
    if (modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        else std::cerr << "Uniform 'model' not found in shader program\n";

    if (viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        else std::cerr << "Uniform 'view' not found in shader program\n";

    if (projectionLoc != -1) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        else std::cerr << "Uniform 'projection' not found in shader program\n";

    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));

    //draw
    auto& meshes = objects[i]->getMeshes(); // Using getMeshes() method to access the meshes

    for (unsigned int p = 0; p < meshes.size(); p++) {
        meshes[p].Draw(); // Draw each mesh
    }
    //check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
    }
    
}


void cleanup() {
    // Cleanup all of your state, particularly the OpenGL state in here.  This function
    // should behave symmetrically to the initOGL function


}


void keyboard(Key key, Modifier modifier, Action action, int, Window*) {
    if (key == Key::Esc && action == Action::Press) {
        Engine::instance().terminate();
    }


    if (key == Key::Space && modifier == Modifier::Shift && action == Action::Release) {
        Log::Info("Released space key");
        wsHandler->disconnect();
    }

    if (players.empty()) return;

    // Assuming we control the first player for simplicity
    auto& player = players[0];
    /*
    float deltaTime = calculateDeltaTime();

    if (action == Action::Press || action == Action::Repeat) {
        if (key == Key::Right) {
            player->update(deltaTime,1);
        } else if (key == Key::Left) {
            player->update(deltaTime,2);
        };
*/

        const float moveSpeed = 0.1f; // Adjust as needed
        const float turnSpeed = 0.05f; // Adjust as needed

        if (key == Key::Right) {
            player->setOrientation(-turnSpeed);
        } else if (key == Key::Left) {
            player->setOrientation(turnSpeed);
        } else if (key == Key::Up) {
            // Move forward
            player->setPosition(glm::vec3(0.0f, cos(player->getOrientation()) * moveSpeed, sin(player->getOrientation()) * moveSpeed));
        } else if (key == Key::Down) {
            // Move backward
            player->setPosition(-glm::vec3(0.0f, cos(player->getOrientation()) * moveSpeed, sin(player->getOrientation()) * moveSpeed));
        }

    }


void connectionEstablished() {
    Log::Info("Connection established");
}


void connectionClosed() {
    Log::Info("Connection closed");
}


void messageReceived(const void* data, size_t length) {
    std::string_view msg = std::string_view(reinterpret_cast<const char*>(data), length);
    Log::Info(fmt::format("Message received: {}", msg));
}

double lastFrameTime = 0.0;

double calculateDeltaTime() {
    double currentFrameTime = glfwGetTime(); // Get current time
    double deltaTime = currentFrameTime - lastFrameTime; // Calculate difference
    lastFrameTime = currentFrameTime; // Update last frame time for the next frame
    return deltaTime;
}

int main(int argc, char** argv) {

    addPlayer(1, "Viktor");
    addPlayer(2, "Alex");

    std::vector<std::string> arg(argv + 1, argv + argc);
    Configuration config = sgct::parseArguments(arg);
    config::Cluster cluster = sgct::loadCluster(config.configFilename);

    Engine::Callbacks callbacks;
    callbacks.initOpenGL = initOGL;
    callbacks.preSync = preSync;
    callbacks.encode = encode;
    callbacks.decode = decode;
    callbacks.postSyncPreDraw = postSyncPreDraw;
    callbacks.draw = draw;
    callbacks.cleanup = cleanup;
    callbacks.keyboard = keyboard;

    try {
        Engine::create(cluster, callbacks, config);
    }
    catch (const std::runtime_error& e) {
        Log::Error(std::string(e.what()));
        Engine::destroy();
        return EXIT_FAILURE;
    }

    if (Engine::instance().isMaster()) {
        wsHandler = std::make_unique<WebSocketHandler>(
            "localhost",
            81,
            connectionEstablished,
            connectionClosed,
            messageReceived
        );
        constexpr const int MessageSize = 1024;
        wsHandler->connect("example-protocol", MessageSize);
    }

    Engine::instance().exec();

    Engine::destroy();
    return EXIT_SUCCESS;
}