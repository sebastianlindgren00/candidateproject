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


#include "AssimpLoader.h"
#include "objectValues.h"

class Utility
{
public:

	static unsigned int textureFromFile(const char* path, const std::string& directory/*bool gamma = false*/);

private:
	
};