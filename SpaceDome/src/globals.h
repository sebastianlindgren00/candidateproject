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

#endif // GLOBALS_H