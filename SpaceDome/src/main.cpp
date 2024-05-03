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
#include <iostream>
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
//#include "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/ext/rapidjson/document.h"
//#include "/Users/sebastianlindgren/Documents/GitHub/candidateproject/SpaceDome/ext/rapidjson/error/en.h"


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

std::unique_ptr<AssimpLoader> greenBulletAssimp;
std::unique_ptr<AssimpLoader> redBulletAssimp;

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

std::vector<syncData> states; 


void initOGL(GLFWwindow*) {

    std::string filePath2 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[4] + ".fbx";
    std::string filePath3 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[5] + ".fbx";
    //std::string filePath4 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[7] + ".fbx";
    std::string filePath5 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[8] + ".fbx";
    std::string filePath6 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[6] + ".fbx";
    std::string filePath7 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[3] + ".fbx";
    std::string filePath8 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[9] + ".fbx";
    std::string filePath9 = std::string(MODELS_DIRECTORY) + "/" + allModelNames[10] + ".fbx";
    std::string fontPath = std::string(MODELS_DIRECTORY) + "/font/Michroma-Regular.ttf";

    //Utility utility;
    shaderProgram = Utility::createShaderProgram(vertexShaderSource, fragmentShaderSource);
    shaderProgramTexture = Utility::createShaderProgram(vertexShaderSourceTexture, fragmentShaderSourceTexture);
    shaderProgramMaterial = Utility::createShaderProgram(vertexShaderSourceMaterial, fragmentShaderSourceMaterial);
    shaderProgramText = Utility::createShaderProgram(vertexShaderSourceText, fragmentShaderSourceText);
    
    //std::string baseDirectory = "../../models/";
    //bulletsAssimp = std::make_unique<AssimpLoader>(filePath4);
    
    starsAssimp = std::make_unique<AssimpLoader>(filePath5);
    skyboxAssimp = std::make_unique<AssimpLoader>(filePath6);
    backgroundObjectsAssimp = std::make_unique<AssimpLoader>(filePath7);
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath2));
    objectsAssimp.push_back(std::make_unique<AssimpLoader>(filePath3));

    redBulletAssimp= std::make_unique<AssimpLoader>(filePath8);
    greenBulletAssimp = std::make_unique<AssimpLoader>(filePath9);


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
    
    std::vector<std::byte> data; // Store serialized data

    //we check if sgct is run on master machine 
    if (Engine::instance().isMaster() && wsHandler->isConnected() &&
        Engine::instance().currentFrameNumber() % 100 == 0){

            wsHandler->queueMessage("ping");
            //if game instance is active 
            if(Game::instance().isGameActive()){
                //send time through ws handler to

               std::string timeLeft = std::to_string(Game::instance().getEndTime());
                wsHandler->queueMessage("Time left: " + timeLeft);
            }

            if(!Game::instance().isGameActive()){
                std::string restartTime = to_string(Game::instance().getRestartTime());
                wsHandler->queueMessage("New round starts in" + restartTime);
            }
        
        wsHandler->tick();
    }

    if(Engine::instance().isMaster()){
        Game::instance().update();
    }
}

std::vector<std::byte> encode() {
    std::vector<std::byte> data;

    // Serialize exampleInt
    serializeObject(data, exampleInt);

    // Serialize exampleString
    serializeObject(data, exampleString);

    // Serialize sync data
    std::vector<syncData> gameStates = Game::instance().fetchSyncData();
    serializeObject(data, gameStates);

    return data;
}


void decode(const std::vector<std::byte>& data) {
    // These are just two examples;  remove them and replace them with the logic of your
    // application that you need to synchronize
    unsigned pos = 0;
    deserializeObject(data, pos, states);
}

void postSyncPreDraw() {
    // Apply the (now synchronized) application state before the rendering will start

    //Sync gameobjects' state on clients only
	if (!Engine::instance().isMaster() && Game::instance().isGameActive())
	{
		//Engine::instance().setStatsGraphVisibility(areStatsVisible);

		if (!Game::instance().isGameActive())
			return;
		else if(states.size() > 0 && !Game::instance().isGameActive()) {
			Game::instance().fetchSyncData();
		}
	}
	else
	{
		//if (Game::instance().isGameActive())
		//	Game::instance().sendPointsToServer(wsHandler);
	}
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

    glm::mat4 modelMatrix;
    std::memcpy(
        glm::value_ptr(modelMatrix),
        data.modelMatrix.values,
        sizeof(mat4)
    );

    //const sgct::RenderData &data;
    const sgct::Window &sgctWindowRef = data.window; // Assume data.window is a reference to sgct::Window
    const sgct::Window *sgctWindowPtr = &sgctWindowRef;

    GLFWwindow* glfwWindow = sgctWindowPtr->windowHandle();
    int windowWidthOut = 2560;
    int windowHeightOut = 1440;
    glfwGetFramebufferSize(glfwWindow, &windowWidthOut, &windowHeightOut);

    if (!glfwWindow) {
        std::cerr << "Failed to get GLFWwindow pointer from sgct::Window." << std::endl;
        return;
    }

    //glm::vec3 translation(0.0f, 0.0f, -4.0f); 
    //viewMatrix = glm::translate(viewMatrix, translation);

    //std::cout << "Draw called\n";
    Game& game = Game::instance();


    game.setMatrixes(projectionMatrix, modelMatrix*viewMatrix, windowWidthOut, windowHeightOut);
    game.addSpawnRot();

    float textScaleX = windowWidthOut/1500;
    //float textScaleY = windowWidthOut/1500;
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    std::string textRed = "RED TEAM: " + std::to_string(game.getStars(1));
    std::string textGreen = "GREEN TEAM: " + std::to_string(game.getStars(2));

    //render Text
    Utility utilityInstance;
    utilityInstance.setScaleConst((float)windowHeightOut/1440);
   
    int timer = game.getEndTime();

    glEnable(GL_DEPTH_TEST);
    //render Background
    Utility::setupShaderForDrawing(shaderProgramTexture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0, 20, 1, projectionMatrix, viewMatrix);
    auto& meshesSkyBox = skyboxAssimp->getMeshes();
    for (unsigned int p = 0; p < meshesSkyBox.size(); p++) {
            meshesSkyBox[p].Draw(); // Draw each mesh
        }

    if (game.hasBGObjects()) { 
        for (const auto& object : game.getBGObjects()) {
            object->draw(backgroundObjectsAssimp, shaderProgram, projectionMatrix, modelMatrix*viewMatrix); 
        }
    }
    Utility::CalculateScreenPositions(projectionMatrix, modelMatrix*viewMatrix, windowWidthOut, windowHeightOut);

    glDisable(GL_DEPTH_TEST);
     //dont draw players, stars and objects if game is at hold
    if(!game.isGameActive()){
    
        timer = game.getRestartTime();
        std::string textTime = "NEW GAME STARTS IN: " + std::to_string(timer);
        utilityInstance.RenderText(shaderProgramText, textTime, 7, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        if(game.getStars(1) > game.getStars(2)){
            utilityInstance.RenderText(shaderProgramText, "Red Team Won!", 6, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        } else if(game.getStars(1) < game.getStars(2)){
            utilityInstance.RenderText(shaderProgramText, "Green Team Won!", 6, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        } else {
            utilityInstance.RenderText(shaderProgramText, "The Game Ended In A Draw!", 6, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        }

        hiscoreList = getHiscoreList(game.getPlayers());

        utilityInstance.RenderText(shaderProgramText, textRed, 5, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        utilityInstance.RenderText(shaderProgramText, textGreen, 4, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        utilityInstance.RenderText(shaderProgramText, "Player Hiscore:", 3, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        if(game.getPlayers().size() > 0){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[0], 2, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        }
        if(game.getPlayers().size() > 1){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[1], 1, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        }if(game.getPlayers().size() > 2){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[2], 0, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
        }
        return;
    } 

    std::string textTime = "GAME ENDS IN: " + std::to_string(timer);

    utilityInstance.RenderText(shaderProgramText, textTime, 6, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
    utilityInstance.RenderText(shaderProgramText, textRed, 5, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);
    utilityInstance.RenderText(shaderProgramText, textGreen, 4, textScaleX, glm::vec3(0.8f, 0.8f, 0.8f), glfwWindow);

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

        int hitBulletId = player->update(bullets, windowHeightOut);
        if (hitBulletId != -1) {
            bulletsToRemove.push_back(hitBulletId); // Collect bullet IDs to remove
        }
        player->draw(playerModelsRed, playerModelsGreen, shaderProgramTexture, projectionMatrix, modelMatrix*viewMatrix);
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
            bullet->draw(greenBulletAssimp,redBulletAssimp, shaderProgramTexture, projectionMatrix, modelMatrix*viewMatrix); 
        }
    }

    if(game.hasStars()) {
        for (const auto& stars : game.getStars()){
            stars->draw(starsAssimp, shaderProgram, projectionMatrix, modelMatrix*viewMatrix);
        }
    }

    for(size_t i = 0; i < objectsAssimp.size(); i++ ){

        glm::vec3 objectColor = glm::vec3(0.4f, 1.f, 0.2f);
        glm::vec3 pos = glm::vec3(windowHeightOut/300, 0.0f, -3.0);
    
        if(i == 0){
            objectColor = glm::vec3(1.f, 0.2f, 0.2f);
            pos = glm::vec3(-windowHeightOut/300, 0.0f, -3.0);
        }

        Utility::setupShaderForDrawing(shaderProgram, pos, objectColor, game.getSpawnRot(), 0.7, 1, projectionMatrix, modelMatrix*viewMatrix);
    
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
        printsPlayers.push_back(std::make_tuple(player->getName(), player->getTextX(), player->getTextY(),textScaleX/1.5, glm::vec3(0.8f, 0.8f, 0.8f)));
    }
    utilityInstance.RenderTextPlayers(shaderProgramText, printsPlayers, glfwWindow);

}

void draw2D(const RenderData& data)
{
    
}

void cleanup() {
    // Cleanup all of your state, particularly the OpenGL state in here.  This function
    // should behave symmetrically to the initOGL function
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &textureColorbuffer);

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


void globalKeyboardHandler(Key key, Modifier modifier, Action action, int, Window* window) {
    // Forward the event to your game's keyboard handler
    Game::instance().gameKeyboard(key, modifier, action, window);

    if (key == Key::Esc && action == Action::Press) {
        Engine::instance().terminate();
    }

    if (key == Key::P && action == Action::Press) {
    if(Game::instance().getPlayers().size() < 100) {
        int id = Game::instance().getLowestAvailablePlayerID();
        Game::instance().addPlayer(id, "o"); // TODO: Add a name from user input, should not be "o"
    }
}
    
    if (key == Key::O && action == Action::Press) {
        auto& players = Game::instance().getPlayers();
        if(players.size() > 2) {
            int lastPlayerId = players.back()->getID();
            Game::instance().removePlayer(lastPlayerId); // Can only remove the last player
        }
    } 
}

void connectionEstablished() {
    Log::Info("Connection established");
}

void connectionClosed() {
    Log::Info("Connection closed");
}


// Define your message handling functions
void handleServerJoin(const std::string& userData) {
    // Handle server join message
    // Example: Log the user data
    std::cout << "User joined: " << userData << std::endl;
}

void messageReceived(const void* data, size_t length) {
    // Message received from WebSocket server
    std::string msg(reinterpret_cast<const char*>(data), length);
    
    // Parse the JSON message and handle it accordingly
    // For simplicity, let's assume it's a JSON message containing 'type' and 'user'
    // Example: {"type": "server_join", "user": "random_user_id"}
    // Parse the message and extract 'type' and 'user'
    // You can use your preferred JSON parsing library for this
    // Here, we'll just demonstrate with simple string manipulation
    size_t typePos = msg.find("type");
    if (typePos != std::string::npos) {
        // Extract the message type
        size_t userPos = msg.find("user");
        if (userPos != std::string::npos) {
            std::string type = msg.substr(typePos + 7, userPos - typePos - 10);
            std::string userData = msg.substr(userPos + 7);
            
            // Handle the message based on its type
            if (type == "server_join") {
                // Call the corresponding message handling function
                handleServerJoin(userData);
            }
            // Add other message types as needed
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

        wsHandler = std::make_unique<WebSocketHandler>("localhost", 4685, connectionEstablished, connectionClosed, messageReceived);
        constexpr const int MessageSize = 1024;

        if (wsHandler->connect("wss", MessageSize)) {
            Log::Info("WebSocket connection initiated!");
            /* TESTS
            wsHandler->queueMessage("test test1");
            wsHandler->queueMessage("test test2");
            Log::Info(fmt::format("Messages in queue: {} ", wsHandler->queueSize()));
            wsHandler->tick();
            */
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