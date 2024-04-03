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
#include "game.h"
#include "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/ext/rapidjson-master/include/rapidjson/document.h" // need to fix this path


namespace {
    std::unique_ptr<WebSocketHandler> wsHandler;


    int64_t exampleInt = 0;
    std::string exampleString;
} // namespace

using namespace sgct;

std::unique_ptr<AssimpLoader> modelsAssimp;
std::unique_ptr<AssimpLoader> bulletsAssimp;
std::unique_ptr<AssimpLoader> starsAssimp;
std::vector<std::unique_ptr<AssimpLoader>> objectsAssimp;
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
    std::string filePath1 = "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/src/models/" + allModelNames[2] + ".fbx";
    std::string filePath2 = "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/src/models/" + allModelNames[4] + ".fbx";
    std::string filePath3 = "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/src/models/" + allModelNames[5] + ".fbx";
    std::string filePath4 = "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/src/models/" + allModelNames[7] + ".fbx";
    std::string filePath5 = "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/src/models/" + allModelNames[8] + ".fbx";

    modelsAssimp = std::make_unique<AssimpLoader>(filePath1);
    bulletsAssimp = std::make_unique<AssimpLoader>(filePath4);
    starsAssimp = std::make_unique<AssimpLoader>(filePath5);
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath2));
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath3));
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
    Game::instance().update();

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

void draw(const RenderData& data) {

    //std::cout << "Draw called\n";
    Game& game = Game::instance();
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    if (game.hasPlayers()) { 
        for (const auto& player : game.getPlayers()) {
            player->draw(modelsAssimp, shaderProgram); 
        }
    }
    if (game.hasBullets()) { 
        for (const auto& bullet : game.getBullets()) {
            bullet->draw(bulletsAssimp, shaderProgram); 
        }
    }

    if(game.hasStars()) {
        for (const auto& stars : game.getStars()){
            stars->draw(starsAssimp, shaderProgram);
        }
    }

    for(size_t i = 0; i < objectsAssimp.size(); i++ ){

        glm::vec3 objectColor = glm::vec3(0.4f, 1.f, 0.2f);
        glm::vec3 pos = glm::vec3(-1.0f, 0.0f, 2.0f);
    
        if(i == 0){
            objectColor = glm::vec3(1.f, 0.2f, 0.2f);
            pos = glm::vec3(-1.0f, 0.0f, -2.0f);
        }

        Utility::setupShaderForDrawing(shaderProgram, pos, objectColor, 0, 0.4);
    
        //draw
        auto& meshes = objectsAssimp[i]->getMeshes(); // Using getMeshes() method to access the meshes

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
    Game& game = Game::instance();

    if (key == Key::Esc && action == Action::Press) {
        Engine::instance().terminate();
    }

    if (key == Key::Space && modifier == Modifier::Shift && action == Action::Release) {
        Log::Info("Released space key");
        wsHandler->disconnect();
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
    //Log::Info(fmt::format("Message received: {}", msg));
    std::string message = msg.data();
}

void globalKeyboardHandler(Key key, Modifier modifier, Action action, int, Window* window) {
    // Forward the event to your game's keyboard handler
    Game::instance().gameKeyboard(key, modifier, action, window);
}


int main(int argc, char** argv) {
    
    Game::instance().addPlayer(1, "Viktor");
    Game::instance().addPlayer(2, "Alex");

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
    //callbacks.keyboard = keyboard;
    callbacks.keyboard = globalKeyboardHandler;
    

    try {
        Engine::create(cluster, callbacks, config);
    }
    catch (const std::runtime_error& e) {
        Log::Error(std::string(e.what()));
        Engine::destroy();
        return EXIT_FAILURE;
    }

    // Won't work if this is commented out
    if (Engine::instance().isMaster()) 
    {
        wsHandler = std::make_unique<WebSocketHandler>(
            "wss://omni.itn.liu.se/ws/", // was localhost
            81, // 443 represents the port for https and 81 for http
            connectionEstablished, // callbacks
            connectionClosed, // callbacks
            messageReceived // callbacks
        );
         constexpr const int MessageSize = 1024;
         wsHandler->connect("wss", MessageSize);
    }

    Engine::instance().exec();

    Engine::destroy();
    return EXIT_SUCCESS;
}