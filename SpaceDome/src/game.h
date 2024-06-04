#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <tuple>
#include <cmath>
#include <random>
#include <cstddef>
#include <chrono>
#include <sgct/sgct.h>
#include <set>
#include "TextItem.h"

#include "sgct/shareddata.h"
#include "sgct/log.h"
#include "sgct/profiling.h"
#include "sgct/shadermanager.h"
#include "sgct/shaderprogram.h"
#include "sgct/engine.h"
#include "glad/glad.h"
#include "glm/packing.hpp"
#include "glm/matrix.hpp"

#include "booster.h"
#include "player.h"
#include "utility.h"
#include "bullets.h"
#include "stars.h"
#include "backgroundObjects.h"


// Contains all necessary game object data that is used for the sync
struct syncData {
    std::vector<PlayerData> playerData;
    std::vector<ObjectData> objectData;
    std::vector<StarData> starData;
    std::vector<BulletData> bulletData;
    std::vector<PlayerName> playerName;
};


struct syncGameData {
    float gameTimeLast;
    float totalTime;
    int teamRed;
    int teamGreen;
    int redTeamStars;
    int greenTeamStars;
    int counterForBGObjects;
    float zPosBgObjects;
    int bulletID;
    int starDelayCounter;
    int starDelay;
    float handInRadius;
    int maxStarsID;
    int redWins;
    int greenWins;
    float spawnRotation;
    int64_t gameActive;
    /*
    float height;
    float row1;
    float row2;
    float row3;
    float row4;
    float row5;
    float row6;
    float row7;
    float row8;
    */
};

//Implemented as explicit singleton, handles pretty much everything
class Game
{
public:

// Creates one instance of a Game. There should only be one active instance of Game at a time
static Game& instance() {
        static Game instance;

    return instance;
}

syncData fetchSyncData();
syncGameData fetchSyncGameData();
void setSyncGameData(const syncGameData data);
void setSyncData(const syncData data);

std::string charVectorToString(std::vector<char32_t> charVector) {
		// Create a string from the vector of characters
		return std::string(charVector.begin(), charVector.end());
	}

void setMatrixes(glm::mat4 pMatrix, glm::mat4 vMatrix, int inwidth, int inheight) { 
    projectionMatrix = pMatrix;
    viewMatrix = vMatrix;
    windowHeight = inheight;
    windowWidth = inwidth;

    } 

bool hasPlayers() const { return !mPlayers.empty(); }

void getTexts(std::vector<TextItem>& texts);

std::vector<std::string> hiscoreList[3];

std::vector<std::string> getHiscoreList(const std::vector<std::unique_ptr<Player>>& players);

void renderAllTextOnce(GLuint shaderProgramText, GLuint textFramebuffer,float textWidth, float textHeight, GLFWwindow* glfwWindow, Utility utilityInstance );

void renderText(GLuint shaderProgram, float scale, float width, float height, Utility utilityInstance);

bool hasBullets() const { return !mBullets.empty(); }

bool hasStars() const { return !mStars.empty(); }

bool hasBGObjects () const { return !mBGObjects.empty(); }

const std::vector<std::unique_ptr<Player>>& getPlayers() const { return mPlayers; }

std::vector<std::unique_ptr<Bullet>>& getBullets() { return mBullets; }

const std::vector<std::unique_ptr<Star>>& getStars() const { return mStars; }

const std::vector<std::unique_ptr<BackgroundObject>>& getBGObjects() const { return mBGObjects; }

float getHeight(){return height;}

std::vector<float> getRows(){
    std::vector<float> rows;
    rows.push_back(row1);
    rows.push_back(row2);
    rows.push_back(row3);
    rows.push_back(row4);
    rows.push_back(row5);
    rows.push_back(row6);
    rows.push_back(row7);
    rows.push_back(row8);
    return rows;
}

//Copying forbidden
Game(Game const&) = delete;
void operator=(Game const&) = delete;

void addPlayer(int id, const std::string& name);

int getLowestAvailablePlayerID();

static std::vector<glm::vec3> generateColorShades(glm::vec3 baseColor, int count, int team);

int findNextAvailableColorID(int team);

void addBullet(int team, float speed, glm::vec3 position,float orientation, int id);

void shotBullet(int id);

void removePlayer(int id);

void gameKeyboard(sgct::Key key, sgct::Modifier modifier, sgct::Action action, sgct::Window*);

void pickUpStars(int id);

void handInStars(int id);

void updateTurnSpeed(unsigned int id, float rotAngle);

void setChargeActive(unsigned int id, bool mode){ mPlayers[id]->setChargeMode(mode); }

int getStars(int team) {
    if(team == 1) {
        return redTeamStars;
        }else if(team == 2){
            return greenTeamStars;
        }
        else 
        std::cout << " Invalid team\n";
        return -1;
}
int getWins(int team) {
    if(team == 1) {
        return redWins;
        }else if(team == 2){
            return greenWins;
        }
        else 
        std::cout << " Invalid team\n";
        return -1;
}


bool isGameActive() { return mGameActive; }

bool shouldReturnTime(){
    if(mTotalTime - mLastFrameTime > 1){
        mLastFrameTime = mTotalTime;
        return true;
    }
    return false;
}

void resetGameTime() { mTotalTime = 0; }

int getEndTime() { return (int)mMaxTime - mTotalTime; }

int getRestartTime() { return (int)mResetGame - mTotalTime; }

float getSpawnRot() {return spawnRotation;}

void addSpawnRot() {spawnRotation += 0.001;}

int getBulletID() {return bulletID;}

void addBulletID() {bulletID++;}


static glm::mat4 projectionMatrix;
static glm::mat4 viewMatrix;
static int windowHeight, windowWidth;

void update();

// booster stuff

std::vector<std::unique_ptr<Booster>> boosters;
const std::vector<std::unique_ptr<Booster>>& getBoosters() const { return boosters; }
void pickUpBoosters(int playerId);
void generateBoosters();

private:
//Constructor
Game()  {
    redShades = generateColorShades(baseRed, 50, 1);
    greenShades = generateColorShades(baseGreen, 50, 2);
}



std::vector<glm::vec3> redShades;
std::vector<glm::vec3> greenShades;

glm::vec3 baseRed = glm::vec3(1.0f, 0.0f, 0.0f); // Pure red
glm::vec3 baseGreen = glm::vec3(0.0f, 1.0f, 0.0f); // Pure green

std::vector<std::unique_ptr<Player>> mPlayers;
std::vector<std::unique_ptr<Bullet>> mBullets;
std::vector<std::unique_ptr<Star>> mStars;
std::vector<std::unique_ptr<BackgroundObject>> mBGObjects;

bool mGameActive = false;
std::unordered_map<sgct::Key, bool> keyStates;
float mLastFrameTime = -1;
float mTotalTime = 0;
float mMaxTime = 200; //seconds
//float mLastTime = 0;
float mResetGame = 3;

float zPosBgObjects = -4.5;
int starDelayCounter = 0;
int starDelay = (rand() % 100) + 1;
//int amountOfPlayers;
int teamRed = 0;
int teamGreen = 0;
int redTeamStars = 0;
int greenTeamStars = 0;
float handInRadius = 0.7f;
int maxStarsID = 0;
int redWins = 0;
int greenWins = 0;

float spawnRotation = 0;

int bulletID = 0;

int counterForBGObjects = 0;

float height = 1280;
float row1 = 900;
float row2 = 800;
float row3 = 720;
float row4 = 640;
float row5 = 540;
float row6 = 460;
float row7 = 380;
float row8 = 300;

// boosters

double currentFrameTime;
double lastBoosterSpawnTime;
double boosterSpawnInterval = 3;
int maxAmountOfBoosters = 15;
int boosterID;

};