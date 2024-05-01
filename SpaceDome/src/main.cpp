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
std::vector<std::string> hiscoreList(3);
std::vector<std::unique_ptr<AssimpLoader>> playerModelsRed;
std::vector<std::unique_ptr<AssimpLoader>> playerModelsGreen;

GLuint shaderProgram;
GLuint shaderProgramTexture;
GLuint shaderProgramMaterial;
GLuint shaderProgramText;
GLuint shaderProgramFisheye;

GLuint framebuffer = 0;
GLuint textureColorbuffer = 0;

//For Fisheye:
//---------------------------------
GLuint quadVAO = 0;
GLuint quadVBO = 0;

void initFullScreenQuad() {
    float quadVertices[] = {
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    // Setup screen VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO first (not the VBO or EBO), then unbind the VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void renderFullScreenQuad() {
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

//---------------------------------

void initOGL(GLFWwindow*) {

    

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
    shaderProgramMaterial = Utility::createShaderProgram(vertexShaderSourceMaterial, fragmentShaderSourceMaterial);
    shaderProgramText = Utility::createShaderProgram(vertexShaderSourceText, fragmentShaderSourceText);

    //for fisheye?
 /*
    initFullScreenQuad();
     // Framebuffer configuration
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // Use your desired dimensions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // Load shaders and get a shader program for fisheye effect
    shaderProgramFisheye = Utility::createShaderProgram(vertexShaderSourceFisheye, fragmentShaderSourceFisheye);
*/
    
    //std::string baseDirectory = "../../models/";
    bulletsAssimp = std::make_unique<AssimpLoader>(filePath4);
    starsAssimp = std::make_unique<AssimpLoader>(filePath5);
    skyboxAssimp = std::make_unique<AssimpLoader>(filePath6);
    backgroundObjectsAssimp = std::make_unique<AssimpLoader>(filePath7);
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath2));
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath3));


    //load all models for team Red and than team Green
    for( int i = 0; i < 18; i++){
        std::string path = std::string(MODELS_DIRECTORY) + "/red/" + allShipsRed[i] + ".fbx";
        playerModelsRed.push_back(std::make_unique<AssimpLoader>(path));
    }

    for( int i = 0; i < 18; i++){
        std::string path = std::string(MODELS_DIRECTORY) + "/green/" + allShipsGreen[i] + ".fbx";
        playerModelsGreen.push_back(std::make_unique<AssimpLoader>(path));
    }

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

std::vector<std::string> getHiscoreList(const std::vector<std::unique_ptr<Player>>& players) {

    int first = 0, second = 0, third = 0;

    for (const auto& player : players) {
        int stars = player->getHandedInStars();
        std::string nameAndStars = player->getName() + " " + std::to_string(stars);

        if (stars >= first) {
            hiscoreList[2] = hiscoreList[1];
            hiscoreList[1] = hiscoreList[0];
            hiscoreList[0] = nameAndStars;
            third = second;
            second = first;
            first = stars;
        } else if (stars >= second) {
            hiscoreList[2] = hiscoreList[1];
            hiscoreList[1] = nameAndStars;
            third = second;
            second = stars;
        } else if (stars >= third) {
            hiscoreList[2] = nameAndStars;
            third = stars;
        }
    }
    return hiscoreList;
}

void draw(const RenderData& data) {
    
    glm::mat4 projectionMatrix;
    std::memcpy(
        glm::value_ptr(projectionMatrix),
        data.projectionMatrix.values,
        sizeof(mat4)
    );

    glm::mat4 viewMatrix;
    std::memcpy(
        glm::value_ptr(viewMatrix),
        data.viewMatrix.values,
        sizeof(mat4)
    );

    glm::vec3 translation(0.0f, 0.0f, -5.0f); 
    viewMatrix = glm::translate(viewMatrix, translation);


    //test with old matrixes
    /*
    projectionMatrix = glm::perspective(glm::radians(fovScale), 800.0f / 500.0f, 0.1f, 100.0f); 
    const glm::vec3 viewPos = glm::vec3(5.0f, 0.0f, 0.0f); 
    const glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); 
    const glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f); 
    viewMatrix = glm::lookAt(viewPos, cameraTarget, upDirection);
    */



    //std::cout << "Draw called\n";
    Game& game = Game::instance();
    game.setMatrixes(projectionMatrix, viewMatrix);
    game.addSpawnRot();

    //fisheye
    // Bind framebuffer for offscreen rendering
    //glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    //glViewport(0, 0, 800, 600); // Match the framebuffer size
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);

    //annars
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    

    std::string textRed = "RED TEAM: " + std::to_string(game.getStars(1));
    std::string textGreen = "GREEN TEAM: " + std::to_string(game.getStars(2));

    //render Text
    Utility utilityInstance;
    Utility::CalculateScreenPositions(projectionMatrix, viewMatrix);
   
    int timer = game.getEndTime();

    glEnable(GL_DEPTH_TEST);
    //render Background
    Utility::setupShaderForDrawing(shaderProgramTexture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0, 12, 1, projectionMatrix, viewMatrix);
    auto& meshesSkyBox = skyboxAssimp->getMeshes();
    for (unsigned int p = 0; p < meshesSkyBox.size(); p++) {
            meshesSkyBox[p].Draw(); // Draw each mesh
        }

    if (game.hasBGObjects()) { 
        for (const auto& object : game.getBGObjects()) {
            object->draw(backgroundObjectsAssimp, shaderProgram, projectionMatrix, viewMatrix); 
        }
    }

    glDisable(GL_DEPTH_TEST);
     //dont draw players, stars and objects if game is at hold
    if(!game.isGameActive()){
    
        timer = game.getRestartTime();
        std::string textTime = "NEW GAME STARTS IN: " + std::to_string(timer);
        utilityInstance.RenderText(shaderProgramText, textTime, 7, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        if(game.getStars(1) > game.getStars(2)){
            utilityInstance.RenderText(shaderProgramText, "Red Team Won!", 6, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        } else if(game.getStars(1) < game.getStars(2)){
            utilityInstance.RenderText(shaderProgramText, "Green Team Won!", 6, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        } else {
            utilityInstance.RenderText(shaderProgramText, "The Game Ended In A Draw!", 6, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        }

        hiscoreList = getHiscoreList(game.getPlayers());

        utilityInstance.RenderText(shaderProgramText, textRed, 5, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        utilityInstance.RenderText(shaderProgramText, textGreen, 4, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        utilityInstance.RenderText(shaderProgramText, "Player Hiscore:", 3, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        if(game.getPlayers().size() > 0){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[0], 2, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        }
        if(game.getPlayers().size() > 1){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[1], 1, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        }if(game.getPlayers().size() > 2){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[2], 0, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
        }
        return;
    } 

    std::string textTime = "GAME ENDS IN: " + std::to_string(timer);

    utilityInstance.RenderText(shaderProgramText, textTime, 6, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
    utilityInstance.RenderText(shaderProgramText, textRed, 5, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));
    utilityInstance.RenderText(shaderProgramText, textGreen, 4, 0.5f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f));

    glEnable(GL_DEPTH_TEST);
    if (game.hasPlayers()) {
    std::vector<int> bulletsToRemove; // This will store the IDs of bullets to remove
    auto& bullets = game.getBullets();

    for (const auto& player : game.getPlayers()) {

        //if player shold shot a bullet, add a bullet
        if(player->getShotBullet()){
                game.addBullet(player->getTeam(),player->getSpeed(),player->getPosition(),player->getOrientation(), game.getBulletID());
                player->restoreTimer();
                game.addBulletID();
            }

        int hitBulletId = player->update(bullets);
        if (hitBulletId != -1) {
            bulletsToRemove.push_back(hitBulletId); // Collect bullet IDs to remove
        }
        player->draw(playerModelsRed, playerModelsGreen, shaderProgramTexture, projectionMatrix, viewMatrix);
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
            bullet->draw(bulletsAssimp, shaderProgram, projectionMatrix, viewMatrix); 
        }
    }

    if(game.hasStars()) {
        for (const auto& stars : game.getStars()){
            stars->draw(starsAssimp, shaderProgram, projectionMatrix, viewMatrix);
        }
    }

    for(size_t i = 0; i < objectsAssimp.size(); i++ ){

        glm::vec3 objectColor = glm::vec3(0.4f, 1.f, 0.2f);
        glm::vec3 pos = glm::vec3(fovScale/21, 0.0f, -1.0);
    
        if(i == 0){
            objectColor = glm::vec3(1.f, 0.2f, 0.2f);
            pos = glm::vec3(-fovScale/21, 0.0f, -1.0);
        }

        Utility::setupShaderForDrawing(shaderProgram, pos, objectColor, game.getSpawnRot(), 0.4, 1, projectionMatrix, viewMatrix);
    
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
    //Player names should be above all else
    glDisable(GL_DEPTH_TEST);

    std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers;
    for(auto& player : game.getPlayers()){
        if(player->isAlive())
        printsPlayers.push_back(std::make_tuple(player->getName(), player->getTextX(), player->getTextY(), 0.3f+((45-fovScale)/1000), glm::vec3(0.8f, 0.8f, 0.8f)));
    }
    utilityInstance.RenderTextPlayers(shaderProgramText, printsPlayers);

    /*
    //For fisheye
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600); // Replace with actual window size
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramFisheye);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glUniform1i(glGetUniformLocation(shaderProgramFisheye, "screenTexture"), 0);

    renderFullScreenQuad();

    // Clean up
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    */
}

void cleanup() {
    // Cleanup all of your state, particularly the OpenGL state in here.  This function
    // should behave symmetrically to the initOGL function
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &textureColorbuffer);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);

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
    Log::Info("Why is it closing");
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

    if (key == Key::Esc && action == Action::Press) {
        Engine::instance().terminate();
    }

    if (key == Key::P && action == Action::Press) {
    if(Game::instance().getPlayers().size() < 100) {
        int id = Game::instance().getLowestAvailablePlayerID();
        Game::instance().addPlayer(id, "o");
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
    
    Game::instance().addPlayer(0,"Tim");
    Game::instance().addPlayer(1,"Viktor");
    Game::instance().addPlayer(2,"Bas");

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
    //new Keyboard function
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
    if (Engine::instance().isMaster()) {

        wsHandler = std::make_unique<WebSocketHandler>(
            "wss://omni.itn.liu.se/ws/", // Server address
            443,                // Server port
            connectionEstablished,
            connectionClosed,
            messageReceived
        );

        constexpr const int MessageSize = 1024;
        if (wsHandler->connect("wss", MessageSize)) {
            Log::Info("WebSocket connection initiated!");
        } else {
            Log::Error("Failed to initiate WebSocket connection!");
        }
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