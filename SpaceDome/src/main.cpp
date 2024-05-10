//
//  Main.cpp provided under CC0 license
//
//#include "websockethandler.h"
#include "sgct/sgct.h"
#include <sgct/freetype.h>
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
#include "text.h"
#include "tcpsocket.h" // For TCPSocket (New testing)
#include <filesystem> // For Models dir
#include <nlohmann/json.hpp> // For JSON nlohmann - Why is it in sgct though??
#include <fstream> // For file reading
std::filesystem::path baseDir;

namespace {
    //std::unique_ptr<WebSocketHandler> wsHandler;
    //int64_t gameOn = 0;
    //sint64_t gameEnded = 0;
    std::string exampleString;
    
} // namespace

using namespace sgct;
using json = nlohmann::json;

//different model-containers
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

//ShaderPrograms
GLuint shaderProgram;
GLuint shaderProgramTexture;
GLuint shaderProgramMaterial;
GLuint shaderProgramText;
GLuint shaderProgramFisheye;
GLuint plainShaderProgram;
GLuint ShaderProgramTextTexture;

//buffers and textures
GLuint framebuffer = 0;
GLuint textureColorbuffer = 0;
syncData states;
syncGameData gameSyncStates;

size_t playersize;
GLuint textureText;

//float for camera movement
float cameraZ = -4.0f;
const int Port = 4685;
const std::string Address = "localhost";

bool isGameStarted = false;

std::unique_ptr<tcpsocket::io::TcpSocket> tcpSocket = std::make_unique<tcpsocket::io::TcpSocket>(Address, Port);

void verifyFontPath(const std::string& fontPath) {
    std::ifstream file(fontPath);
    if (file.good()) {
        std::cout << "Font file is accessible at: " << fontPath << std::endl;
    } else {
        std::cerr << "Font file not found or inaccessible at: " << fontPath << std::endl;
    }
}

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

    //verifyFontPath(fontPath);

    //Utility utility;
    shaderProgram = Utility::createShaderProgram(vertexShaderSource, fragmentShaderSource);
    shaderProgramTexture = Utility::createShaderProgram(vertexShaderSourceTexture, fragmentShaderSourceTexture);
    shaderProgramMaterial = Utility::createShaderProgram(vertexShaderSourceMaterial, fragmentShaderSourceMaterial);
    shaderProgramText = Utility::createShaderProgram(vertexShaderSourceText, fragmentShaderSourceText);
    plainShaderProgram = Utility::createShaderProgram(vertexShaderSourcePlain, fragmentShaderSourcePlain);
    ShaderProgramTextTexture = Utility::createShaderProgram(vertexShaderSourceTextTexture, fragmentShaderSourceTextTexture);

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
    text::FontManager::instance().addFont("CustomFont", fontPath);

    std::cout << "after assimpLoader \n";
}

void initializeText(Game& game, TextRenderer& text, std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers) {
    // Assume `game` is the Game object with the latest text data
    text.updateText(game);
    text.renderTextToTexture(printsPlayers);
}

void preSync() {
    // Do the application simulation step on the server node in here and make sure that
    // the computed state is serialized and deserialized in the encode/decode calls

    std::vector<std::byte> data; // Store serialized data

    //we check if sgct is run on master machine 
    if (Engine::instance().isMaster() && //wsHandler->isConnected() &&
        Engine::instance().currentFrameNumber() % 100 == 0){
    }
    Game::instance().update();
    
}

std::vector<std::byte> encode() {
    std::vector<std::byte> data;

    syncData gameStates = Game::instance().fetchSyncData();
    syncGameData gameData = Game::instance().fetchSyncGameData();
    
    serializeObject(data, gameData);
    serializeObject(data, gameStates.playerData);
    serializeObject(data, gameStates.objectData);
    serializeObject(data, gameStates.bulletData);
    serializeObject(data, gameStates.starData);
    serializeObject(data, gameStates.playerName);
    
    return data;
}

void decode(const std::vector<std::byte>& data) {
    unsigned int pos = 0;

    states.playerData.clear();
    states.playerName.clear();
    states.objectData.clear();
    states.bulletData.clear();
    states.starData.clear();

    deserializeObject(data, pos, gameSyncStates);
    deserializeObject(data, pos, states.playerData);
    deserializeObject(data, pos, states.objectData);
    deserializeObject(data, pos, states.bulletData);
    deserializeObject(data, pos, states.starData);
    deserializeObject(data, pos, states.playerName);


}

void postSyncPreDraw() {
	if (!Engine::instance().isMaster()) {
        Game::instance().setSyncGameData(gameSyncStates);
		Game::instance().setSyncData(states);
    }
}

void draw(const RenderData& data) {
    
    
    glm::mat4 projectionMatrix;
    std::memcpy(glm::value_ptr(projectionMatrix),data.projectionMatrix.values,sizeof(mat4));

    glm::mat4 viewMatrix;
    std::memcpy( glm::value_ptr(viewMatrix),data.viewMatrix.values,sizeof(mat4));

    glm::mat4 modelMatrix;
    std::memcpy(glm::value_ptr(modelMatrix),data.modelMatrix.values,sizeof(mat4));

    const sgct::Window &sgctWindowRef = data.window;
    const sgct::Window *sgctWindowPtr = &sgctWindowRef;

    GLFWwindow* glfwWindow = sgctWindowPtr->windowHandle();
    int windowWidthOut = 2560;
    int windowHeightOut = 1440;

    glfwGetFramebufferSize(glfwWindow, &windowWidthOut, &windowHeightOut);
    if (!glfwWindow) {
        std::cerr << "Failed to get GLFWwindow pointer from sgct::Window." << std::endl;
        return;
    }

    glm::vec3 translation(0.0f, 0.0f, cameraZ); 
    viewMatrix = glm::translate(viewMatrix, translation);

    //std::cout << "Draw called\n";
    Game& game = Game::instance();
    game.setMatrixes(projectionMatrix, modelMatrix*viewMatrix, windowWidthOut, windowHeightOut);
    game.addSpawnRot();

    viewMatrix = modelMatrix * viewMatrix;
    float textScaleX = windowWidthOut/1500;
    
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Utility utilityInstance;
    utilityInstance.setScaleConst((float)windowHeightOut/1440);

    Utility::CalculateScreenPositions(projectionMatrix, viewMatrix, windowWidthOut, windowHeightOut);
    
    glEnable(GL_DEPTH_TEST);

    //render Background
    Utility::setupShaderForDrawing(shaderProgramTexture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0, 20, 1, projectionMatrix, viewMatrix);
    auto& meshesSkyBox = skyboxAssimp->getMeshes();
    for (unsigned int p = 0; p < meshesSkyBox.size(); p++) {
            meshesSkyBox[p].Draw(); // Draw each mesh
        }


    //Render the background objects
    if (game.hasBGObjects()) { 
        for (const auto& object : game.getBGObjects()) {
            object->draw(backgroundObjectsAssimp, shaderProgram, projectionMatrix, modelMatrix*viewMatrix); 
        }
    }
    
    //dont render the rest if game is not active
    if(!game.isGameActive()){
        return;
    } 

    //Render Players
    //And controll/check bullets if any are to be removed
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

    //Render bullets
    if (game.hasBullets()) { 
        for (const auto& bullet : game.getBullets()) {
            bullet->draw(greenBulletAssimp,redBulletAssimp, shaderProgramTexture, projectionMatrix, modelMatrix*viewMatrix); 
        }
    }

    //Render Stars
    if(game.hasStars()) {
        for (const auto& stars : game.getStars()){
            stars->draw(starsAssimp, shaderProgram, projectionMatrix, modelMatrix*viewMatrix);
        }
    }

    //Render spawn planets
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

    std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers;
    for(auto& player : game.getPlayers()){
            if(player->isAlive())
            printsPlayers.push_back(std::make_tuple(player->getName(), player->getTextX(), player->getTextY(),textScaleX/1.5, glm::vec3(0.8f, 0.8f, 0.8f)));
        }

    const sgct::vec4 color1 = sgct::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    for (auto& [text, x, y, scale, color] : printsPlayers){
    text::print( 
        data.window,
        data.viewport,
        *text::FontManager::instance().font("CustomFont",20),
        text::Alignment::TopCenter,
        x,
        y,
        color1,
        text
        );
    }
   
    /*
    std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers;
    for(auto& player : game.getPlayers()){
            if(player->isAlive())
            printsPlayers.push_back(std::make_tuple(player->getName(), player->getTextX(), player->getTextY(),textScaleX/1.5, glm::vec3(0.8f, 0.8f, 0.8f)));
        }

    // Initialize TextRenderer
    //TextRenderer textRenderer(shaderProgramText, windowWidthOut, windowHeightOut);

    // Clear any existing errors
    while (glGetError() != GL_NO_ERROR) {}
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after TextRenderer initialization: " << err << std::endl;
    }
    //initializeText(game, textRenderer, printsPlayers);
    //textureText = textRenderer.getTexture();
       
    //Prints for frameBuffer checks
    
    GLint currentFramebuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFramebuffer);
    
    
    utilityInstance.renderPlane(plainShaderProgram, 0, projectionMatrix,viewMatrix);
    //utilityInstance.renderPlane(ShaderProgramTextTexture, textRenderer.getTexture(), projectionMatrix,viewMatrix);
*/
}

void draw2D(const RenderData& data) {
    /*
    glm::mat4 projectionMatrix;
    std::memcpy(glm::value_ptr(projectionMatrix),data.projectionMatrix.values,sizeof(mat4));

    glm::mat4 viewMatrix;
    std::memcpy( glm::value_ptr(viewMatrix),data.viewMatrix.values,sizeof(mat4));

    glm::mat4 modelMatrix;
    std::memcpy(glm::value_ptr(modelMatrix),data.modelMatrix.values,sizeof(mat4));
*/

    const sgct::Window &sgctWindowRef = data.window;
    const sgct::Window *sgctWindowPtr = &sgctWindowRef;

    GLFWwindow* glfwWindow = sgctWindowPtr->windowHandle();
    int windowWidthOut = 2560;
    int windowHeightOut = 1440;


    glfwGetFramebufferSize(glfwWindow, &windowWidthOut, &windowHeightOut);
    if (!glfwWindow) {
        std::cerr << "Failed to get GLFWwindow pointer from sgct::Window." << std::endl;
        return;
    }
    float textScaleX = windowWidthOut/1500;
    const sgct::vec4 color = sgct::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    float line = windowHeightOut/1.5;
    float count = 0;

    Game& game = Game::instance();
    
    
    std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers;
    for(auto& player : game.getPlayers()){
            if(player->isAlive())
            printsPlayers.push_back(std::make_tuple(player->getName(), player->getTextX(), player->getTextY(),textScaleX/2, glm::vec3(0.8f, 0.8f, 0.8f)));
        }

    std::vector<TextItem> texts;
    game.getTexts(texts);
    std::vector<float> rows = game.getRows();
    //float xVal = game.getHeight();
    
    for (auto& text : texts){
    text::print( 
        data.window,
        data.viewport,
        *text::FontManager::instance().font("CustomFont",50),
        text::Alignment::TopCenter,
        windowWidthOut/2,
        line - count*100,
        color,
        text.text
    );
    count++;
    if(count == 1){
        count += 0.5;
        }
    }
}

void cleanup() {
    // Cleanup all of your state, particularly the OpenGL state in here.  This function
    // should behave symmetrically to the initOGL function
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &textureColorbuffer);

}

void globalKeyboardHandler(Key key, Modifier modifier, Action action, int, Window* window) {
    // Forward the event to your game's keyboard handler
    Game::instance().gameKeyboard(key, modifier, action, window);

    if (key == Key::Esc && action == Action::Press) {
        Engine::instance().terminate();
    }

    if (key == Key::P && action == Action::Press) {
        if (Game::instance().getPlayers().size() < 100) {
            int id = Game::instance().getLowestAvailablePlayerID();
            /*
            std::string playerName; // Prompt the user to enter a name
            std::cout << "Enter player name: ";
            std::cin >> playerName;

            // Serialize player data into JSON
            nlohmann::json playerData;
            playerData["id"] = id;
            playerData["name"] = playerName;

            // Convert JSON to string
            std::string jsonStr = playerData.dump();

            // Send JSON string over TCP socket
            bool success = tcpSocket->putMessage(jsonStr);
            if (!success) {
                std::cout << "Failed to send player data over TCP socket\n";
            }
            */
            Game::instance().addPlayer(id, "ZZZZZZZZZ");
        }
    }
    
    if (key == Key::O && action == Action::Press) {
        auto& players = Game::instance().getPlayers();
        if(players.size() > 0) {
            int lastPlayerId = players.back()->getID();
            Game::instance().removePlayer(lastPlayerId); // Can only remove the last player
        } else{
            std::cout << "Server is empty. Unable to remove any player. \n";
        }
    } 
    
}

int main(int argc, char** argv) {

    states.playerData.reserve(99); 
    states.objectData.reserve(99); 
    states.bulletData.reserve(99); 
    states.starData.reserve(99); 
    states.playerData.reserve(99);

    Game::instance().addPlayer(0, "TIM");
    Game::instance().addPlayer(1, "VIKTOR");
    Game::instance().addPlayer(2, "BAS");

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
    callbacks.draw2D = draw2D;
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
    /*
    if (Engine::instance().isMaster()) {

        if (!tcpSocket) {
            std::cout << "Error creating tcp socket";
            return -1;
        }

        tcpSocket->connect();

        if (tcpSocket->isConnected()) {
            std::cout << "Tcp socket connected";
        }
        else if (tcpSocket->isConnecting()) {
            std::cout << "Tcp socket connecting...";
        }
        else {
            std::cout << "Tcp socket could not connect";
            return -1;
        }

        std::string messageString;
        messageString.reserve(256);
        while (tcpSocket->getMessage(messageString)) {
            std::cout << messageString << '\n';
        }

        return 0;

    }
*/
    Engine::instance().exec();

    Engine::destroy();

    std::cout << "\n\n\nRed Team had: " << Game::instance().getWins(1) << " Wins. \n";
    std::cout << "Green Team had: " << Game::instance().getWins(2) << " Wins. \n\n";
    if (Game::instance().getWins(1) < Game::instance().getWins(2)) {
        std::cout << "Team Green Won! \n\n\n";
    }
    else if (Game::instance().getWins(1) > Game::instance().getWins(2)) {
        std::cout << "Team Red Won! \n\n\n";
    }
    else {
        std::cout << "The Game ended in a draw! \n\n\n";
    }

    return EXIT_SUCCESS;
}