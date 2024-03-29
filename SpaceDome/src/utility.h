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
#include "globals.h"

class Utility
{
public:

	//constructor
	Utility(){
	glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
	}

	static void LoadFontAtlas(const std::string& fontPath);
	void RenderText(GLuint shaderProgram, std::string text, int row, float scale, glm::vec3 color);
	static unsigned int textureFromFile(const char* path, const std::string& directory/*bool gamma = false*/);
	static std::tuple<unsigned int, float> getTurnSpeed(std::istringstream& input);
	static void setupShaderForDrawing(const GLuint shaderProgram, const glm::vec3& position, const glm::vec3& color, float orientation, float scale);

	static GLuint compileShader(GLenum type, const char* source);
	static GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);


	static glm::vec2 screenPositions[3];

	static const glm::vec3 worldPositions[3];

	static void CalculateScreenPositions();



private:

	GLuint textVAO, textVBO;

};