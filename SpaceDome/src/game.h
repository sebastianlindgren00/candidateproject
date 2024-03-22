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
const std::vector<std::unique_ptr<Player>>& getPlayers() const {
    return mPlayers;
}

//Copying forbidden
Game(Game const&) = delete;
void operator=(Game const&) = delete;

void addPlayer(int id, const std::string& name);

void removePlayer(int id);

void updateTurnSpeed(std::tuple<unsigned int, float>&& input);

void update();

private:

//Constructor
Game()  {}

std::vector<std::unique_ptr<Player>> mPlayers;

bool mGameActive = true;

float mLastFrameTime;
float mTotalTime = 0;
//float mMaxTime = 60; //seconds
float mLastTime = 0;
};