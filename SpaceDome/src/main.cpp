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
#include "shaderManager.h"

namespace {
    std::unique_ptr<WebSocketHandler> wsHandler;


    int64_t exampleInt = 0;
    std::string exampleString;
} // namespace

using namespace sgct;

std::unique_ptr<AssimpLoader> modelsAssimp;
std::unique_ptr<AssimpLoader> bulletsAssimp;
std::unique_ptr<AssimpLoader> starsAssimp;
std::unique_ptr<AssimpLoader> skyboxAssimp;
std::vector<std::unique_ptr<AssimpLoader>> objectsAssimp;
std::unique_ptr<AssimpLoader> backgroundObjectsAssimp;
GLuint shaderProgram;
GLuint shaderProgramTexture;
GLuint shaderProgramText;


    

void initOGL(GLFWwindow*) {

    std::string filePath1 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[2] + ".fbx";
    std::string filePath2 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[4] + ".fbx";
    std::string filePath3 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[5] + ".fbx";
    std::string filePath4 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[7] + ".fbx";
    std::string filePath5 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[8] + ".fbx";
    std::string filePath6 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[6] + ".fbx";
    std::string filePath7 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[3] + ".fbx";
    std::string fontPath = std::string(MODELS_DIRECTORY) + "/font/Michroma-Regular.ttf";

    //Utility utility;
    shaderProgram = Utility::createShaderProgram(vertexShaderSource, fragmentShaderSource);
    shaderProgramTexture = Utility::createShaderProgram(vertexShaderSourceTexture, fragmentShaderSourceTexture);
    shaderProgramText = Utility::createShaderProgram(vertexShaderSourceText, fragmentShaderSourceText);
    
    //std::string baseDirectory = "../../models/";
    modelsAssimp = std::make_unique<AssimpLoader>(filePath1);
    bulletsAssimp = std::make_unique<AssimpLoader>(filePath4);
    starsAssimp = std::make_unique<AssimpLoader>(filePath5);
    skyboxAssimp = std::make_unique<AssimpLoader>(filePath6);
    backgroundObjectsAssimp = std::make_unique<AssimpLoader>(filePath7);
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath2));
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath3));

    //std::cout << "Attempting to load font from: " << fontPath << std::endl;
    Utility::LoadFontAtlas(fontPath);

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


//This is moved to Utility
/*
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
*/


void draw(const RenderData& data) {
    (void)data;

    //std::cout << "Draw called\n";
    Game& game = Game::instance();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    std::string textRed = "RED TEAM: " + std::to_string(game.getStars(1));
    std::string textGreen = "GREEN TEAM: " + std::to_string(game.getStars(2));

    //render Text
    Utility utilityInstance;
    //initialize positions for text
    Utility::CalculateScreenPositions();
    int timer = game.getEndTime();

    glEnable(GL_DEPTH_TEST);
    //render Background
    Utility::setupShaderForDrawing(shaderProgramTexture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0, 12);
    auto& meshesSkyBox = skyboxAssimp->getMeshes();
    for (unsigned int p = 0; p < meshesSkyBox.size(); p++) {
            meshesSkyBox[p].Draw(); // Draw each mesh
        }

    if (game.hasBGObjects()) { 
        for (const auto& object : game.getBGObjects()) {
            object->draw(backgroundObjectsAssimp, shaderProgram); 
        }
    }

    glDisable(GL_DEPTH_TEST);
     //dont draw players, stars and objects if game is at hold
    if(!game.isGameActive()){
    
        timer = game.getRestartTime();
        std::string textTime = "NEW GAME STARTS IN: " + std::to_string(timer);
        utilityInstance.RenderText(shaderProgramText, textTime, 2, 0.5f, glm::vec3(0.8f, 0.8f, 0.8f));
        utilityInstance.RenderText(shaderProgramText, textRed, 1, 0.5f, glm::vec3(0.8f, 0.8f, 0.8f));
        utilityInstance.RenderText(shaderProgramText, textGreen, 0, 0.5f, glm::vec3(0.8f, 0.8f, 0.8f));
        return;
    } 

    std::string textTime = "GAME ENDS IN: " + std::to_string(timer);

    utilityInstance.RenderText(shaderProgramText, textTime, 2, 0.5f, glm::vec3(0.8f, 0.8f, 0.8f));
    utilityInstance.RenderText(shaderProgramText, textRed, 1, 0.5f, glm::vec3(0.8f, 0.8f, 0.8f));
    utilityInstance.RenderText(shaderProgramText, textGreen, 0, 0.5f, glm::vec3(0.8f, 0.8f, 0.8f));


    glEnable(GL_DEPTH_TEST);
    if (game.hasPlayers()) {
    std::vector<int> bulletsToRemove; // This will store the IDs of bullets to remove
    auto& bullets = game.getBullets();

    for (const auto& player : game.getPlayers()) {
        int hitBulletId = player->update(bullets);
        if (hitBulletId != -1) {
            bulletsToRemove.push_back(hitBulletId); // Collect bullet IDs to remove
        }
        player->draw(modelsAssimp, shaderProgram);
    }

    // Now remove the bullets that were marked for removal
    if (!bulletsToRemove.empty()) {
        game.getBullets().erase(
            std::remove_if(
                game.getBullets().begin(),
                game.getBullets().end(),
                [&bulletsToRemove](const std::unique_ptr<Bullet>& bullet) {
                    return std::find(bulletsToRemove.begin(), bulletsToRemove.end(), bullet->getID()) != bulletsToRemove.end();
                }),
            game.getBullets().end()
        );
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
/*
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
*/
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

void globalKeyboardHandler(Key key, Modifier modifier, Action action, int, Window* window) {
    // Forward the event to your game's keyboard handler
    Game::instance().gameKeyboard(key, modifier, action, window);

    if (key == Key::Esc && action == Action::Press) {
        Engine::instance().terminate();
    }

    if (key == Key::P && action == Action::Press) {
    if(Game::instance().getPlayers().size() < 100) {
        int id = Game::instance().getLowestAvailablePlayerID();
        Game::instance().addPlayer(id, "testPlayer");
    }
}
    
    if (key == Key::O && action == Action::Press) {
        auto& players = Game::instance().getPlayers();
        if(players.size() > 2) {
            int lastPlayerId = players.back()->getID();
            Game::instance().removePlayer(lastPlayerId);
        }
    }
    
}

int main(int argc, char** argv) {
    
    Game::instance().addPlayer(0, "Viktor");
    Game::instance().addPlayer(1, "Alex");

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


    std::cout << "\n\n\nRed Team had: " << Game::instance().getWins(1) << " Wins. \n";
    std::cout << "Green Team had: " << Game::instance().getWins(2) << " Wins. \n\n";
    if(Game::instance().getWins(1) < Game::instance().getWins(2)){
        std::cout << "Team Green Won! \n\n\n";
    }else if(Game::instance().getWins(1) > Game::instance().getWins(2)){
        std::cout << "Team Red Won! \n\n\n";
    }else{
        std::cout << "The Game ended in a draw! \n\n\n";
    }


    return EXIT_SUCCESS;
}