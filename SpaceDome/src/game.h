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

//Implemented as explicit singleton, handles pretty much everything
class Game
{
public:

static Game& instance() {
        static Game instance;
    return instance;
}

bool hasPlayers() const { return !mPlayers.empty(); }

bool hasBullets() const { return !mBullets.empty(); }

bool hasStars() const { return !mStars.empty(); }

const std::vector<std::unique_ptr<Player>>& getPlayers() const { return mPlayers; }

const std::vector<std::unique_ptr<Bullet>>& getBullets() const { return mBullets; }

const std::vector<std::unique_ptr<Star>>& getStars() const { return mStars; }

//Copying forbidden
Game(Game const&) = delete;
void operator=(Game const&) = delete;

void addPlayer(int id, const std::string& name);

void addBullet(int team, float speed, glm::vec3 position,float orientation);

void shotBullet(int id);

void handInStars(int id);

void removePlayer(int id);

void updateTurnSpeed(unsigned int id, float rotAngle);

void setChargeActive(unsigned int id, bool mode){
    mPlayers[id]->setChargeMode(mode);
}
void update();

void pickUpStars(int id);

void gameKeyboard(sgct::Key key, sgct::Modifier modifier, sgct::Action action, sgct::Window*);

int getRedStars() {return redTeamStars;}

int getGreenStars() { return greenTeamStars;}

bool isGameActive() { return mGameActive; }

void resetGameTime() { mTotalTime = 0; }

int getEndTime() {return (int)mMaxTime - mTotalTime;}
int getRestartTime() {return (int)mResetGame - mTotalTime;}

private:

//Constructor
Game()  {}

std::vector<std::unique_ptr<Player>> mPlayers;
std::vector<std::unique_ptr<Bullet>> mBullets;
std::vector<std::unique_ptr<Star>> mStars;

bool mGameActive = true;
std::unordered_map<sgct::Key, bool> keyStates;
float mLastFrameTime = sgct::time();
float mTotalTime = 0;
float mMaxTime = 20; //seconds
//float mLastTime = 0;
float mResetGame = 10;

int starDelayCounter = 0;
int starDelay = (rand() % 100) + 1;
int amountOfPlayers;
int teamRed = 0;
int teamGreen = 0;
int redTeamStars = 0;
int greenTeamStars = 0;
float handInRadius = 0.4f;
int maxStarsID = 0;
};