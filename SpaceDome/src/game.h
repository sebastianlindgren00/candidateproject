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

#include "sgct/shareddata.h"
#include "sgct/log.h"
#include "sgct/profiling.h"
#include "sgct/shadermanager.h"
#include "sgct/shaderprogram.h"
#include "sgct/engine.h"
#include "glad/glad.h"
#include "glm/packing.hpp"
#include "glm/matrix.hpp"

#include "player.h"
#include "utility.h"
#include "bullets.h"
#include "stars.h"
#include "backgroundObjects.h"

// Contains all necessary game object data that is used for the sync
struct syncData {
    PlayerData playerData;
    //ObjectData objectData:
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

void setMatrixes(glm::mat4 pMatrix, glm::mat4 vMatrix) { 
    projectionMatrix = pMatrix;
    viewMatrix = vMatrix;
    } 

bool hasPlayers() const { return !mPlayers.empty(); }

bool hasBullets() const { return !mBullets.empty(); }

bool hasStars() const { return !mStars.empty(); }

bool hasBGObjects () const { return !mBGObjects.empty(); }

const std::vector<std::unique_ptr<Player>>& getPlayers() const { return mPlayers; }

std::vector<std::unique_ptr<Bullet>>& getBullets() { return mBullets; }

const std::vector<std::unique_ptr<Star>>& getStars() const { return mStars; }

const std::vector<std::unique_ptr<BackgroundObject>>& getBGObjects() const { return mBGObjects; }

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

void resetGameTime() { mTotalTime = 0; }

int getEndTime() { return (int)mMaxTime - mTotalTime; }

int getRestartTime() { return (int)mResetGame - mTotalTime; }

float getSpawnRot() {return spawnRotation;}

void addSpawnRot() {spawnRotation += 0.001;}

int getBulletID() {return bulletID;}

void addBulletID() {bulletID++;}


static glm::mat4 projectionMatrix;
static glm::mat4 viewMatrix;

void update();
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

bool mGameActive = true;
std::unordered_map<sgct::Key, bool> keyStates;
float mLastFrameTime = sgct::time();
float mTotalTime = 0;
float mMaxTime = 60; //seconds
//float mLastTime = 0;
float mResetGame = 10;

float zPosBgObjects = -2;
int starDelayCounter = 0;
int starDelay = (rand() % 100) + 1;
//int amountOfPlayers;
int teamRed = 0;
int teamGreen = 0;
int redTeamStars = 0;
int greenTeamStars = 0;
float handInRadius = 0.4f;
int maxStarsID = 0;
int redWins = 0;
int greenWins = 0;

float spawnRotation = 0;

int bulletID = 0;

int counterForBGObjects = 0;

//int redColorID = 0;
//int greenColorID = 0;
};