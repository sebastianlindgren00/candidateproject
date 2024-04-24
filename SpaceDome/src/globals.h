#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <glad/glad.h> 
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

extern GLuint shaderProgram; // Define it exactly once in the whole project

const std::vector<std::string> allModelNames{ "planet1", "planet2", "SpaceShip", "asteroid1", "SpawnPlanetGreenTest", "SpawnPlanetRed", "backgroundFirstTest", "bullet", "star"};

const std::vector<std::string> allShipsRed{ "RedShip11","RedShip12","RedShip13","RedShip21","RedShip22","RedShip23", "RedShip31", "RedShip32","RedShip33"};

const std::vector<std::string> allShipsGreen{ "GreenShip11","GreenShip12","GreenShip13","GreenShip21","GreenShip22","GreenShip23", "GreenShip31", "GreenShip32","GreenShip33"};

const std::vector<std::string> allShaderNames{ "player", "text", "texture"};

const float playerScale = 0.15f;
const float fovScale = 50.0f;

//boundries for game field
const float boundryX = fovScale/19;
const float boundryY = fovScale/15;

#endif // GLOBALS_H