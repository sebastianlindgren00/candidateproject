#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <tuple>
#include <sstream>
#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/stb_image.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "utility.h"
#include "AssimpLoader.h"
#include "objectValues.h"

class Utility
{
public:

	static unsigned int textureFromFile(const char* path, const std::string& directory/*bool gamma = false*/);
	static std::tuple<unsigned int, float> getTurnSpeed(std::istringstream& input);
	static void setupShaderForDrawing(const GLuint shaderProgram, const glm::vec3& position, const glm::vec3& color, float orientation, float scale);

private:
	
};