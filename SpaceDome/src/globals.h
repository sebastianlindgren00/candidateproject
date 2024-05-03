#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <glad/glad.h> 
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

extern GLuint shaderProgram; // Define it exactly once in the whole pro

const std::vector<std::string> allModelNames{ "planet1", "planet2", "SpaceShip", "asteroid1", "SpawnPlanetGreenTest", "SpawnPlanetRed", "backgroundFirstTest", "bullet", "star"};

const std::vector<std::string> allShipsRed{ "RedShip11","RedShip12","RedShip13","RedShip21","RedShip22","RedShip23", "RedShip31", "RedShip32","RedShip33", "RedShip41","RedShip42","RedShip43","RedShip51","RedShip52","RedShip53", "RedShip61", "RedShip62","RedShip63"};

const std::vector<std::string> allShipsGreen{ "GreenShip11","GreenShip12","GreenShip13","GreenShip21","GreenShip22","GreenShip23", "GreenShip31", "GreenShip32","GreenShip33", "GreenShip41","GreenShip42","GreenShip43","GreenShip51","GreenShip52","GreenShip53", "GreenShip61", "GreenShip62","GreenShip63"};

const std::vector<std::string> allShaderNames{ "player", "text", "texture"};

const float playerScale = 0.15f;
const float fovScale = 50.0f;

//boundries for game field
const float boundryX = 9;
const float boundryY = 6;

#endif // GLOBALS_H