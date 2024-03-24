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

//Implemented as explicit singleton, handles pretty much everything
class Game
{
public:

static Game& instance() {
        static Game instance;
    return instance;
}

bool hasPlayers() const {
    return !mPlayers.empty();
}
bool hasBullets() const {
    return !mBullets.empty();
}

const std::vector<std::unique_ptr<Player>>& getPlayers() const {
    return mPlayers;
}

const std::vector<std::unique_ptr<Bullet>>& getBullets() const {
    return mBullets;
}

//Copying forbidden
Game(Game const&) = delete;
void operator=(Game const&) = delete;

void addPlayer(int id, const std::string& name);

void addBullet(int team, float speed, glm::vec3 position,float orientation);

void shotBullet(int id);

void removePlayer(int id);

void updateTurnSpeed(unsigned int id, float rotAngle);

void setChargeActive(unsigned int id, bool mode){
    mPlayers[id]->setChargeMode(mode);
}
void update();

private:

//Constructor
Game()  {}

std::vector<std::unique_ptr<Player>> mPlayers;
std::vector<std::unique_ptr<Bullet>> mBullets;

bool mGameActive = true;

float mLastFrameTime;
float mTotalTime = 0;
//float mMaxTime = 60; //seconds
float mLastTime = 0;
};