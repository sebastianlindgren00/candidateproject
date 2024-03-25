#pragma once

#include <vector>
#include <string>

const std::vector<std::string> allModelNames{ "planet1", "planet2", "SpaceShip", "asteroid1", "SpawnPlanetGreen", "SpawnPlanetRed", "background", "bullet", "star"};

const std::vector<std::string> allShaderNames{ "player", "testing", "sceneobject", "background", "collectible"};

constexpr float COLLECTIBLESCALE = 0.2f;
constexpr float PLAYERSCALE = 0.5f;
constexpr float DOMERADIUS = 7.4f;