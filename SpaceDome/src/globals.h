#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <glad/glad.h> 
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

extern GLuint shaderProgram; // Define it exactly once in the whole project

const std::vector<std::string> allModelNames{ "planet1", "planet2", "SpaceShip", "asteroid1", "SpawnPlanetGreenTest", "SpawnPlanetRed", "backgroundFirstTest", "bullet", "star"};

const std::vector<std::string> allShaderNames{ "player", "text", "texture"};

const float playerScale = 0.15f;
const float fovScale = 100.0f;

//boundries for game field
const float boundryX = fovScale/19;
const float boundryY = fovScale/15;

#endif // GLOBALS_H