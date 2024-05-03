#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <tuple>
#include <sstream>
#include <map>

#include "sgct/sgct.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "AssimpLoader.h"
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

	//load fonts
	static void LoadFontAtlas(const std::string& fontPath);
	//rendering text
	void RenderText(GLuint shaderProgram, std::string text, int row, float scale, glm::vec3 color, GLFWwindow* glfwWindow);
	//void RenderTextPlayers(GLuint shaderProgram, std::string text, float x, float y, float scale, glm::vec3 color);
	void RenderTextPlayers(GLuint shaderProgram, const std::vector<std::tuple<std::string, float, float, float, glm::vec3>>& texts, GLFWwindow* glfwWindow);
	void RenderSingleText(GLuint shaderProgram, const std::string& text, float x, float y, float scale, const glm::vec3& color);
	
	//getting textures
	static unsigned int textureFromFile(const char* path, const std::string& directory/*bool gamma = false*/);
	
	//setting up shaders before drawing
	static void setupShaderForDrawing(const GLuint shaderProgram, const glm::vec3& position, const glm::vec3& color, float orientation, float scale, int rotAxis, glm::mat4 pMatrix, glm::mat4 vMatrix);
	static void setupShaderForDrawingMaterial(const GLuint shaderProgram, const glm::vec3& position, float orientation, float scale, int rotAxis, glm::mat4 pMatrix, glm::mat4 vMatrix);
	static GLuint compileShader(GLenum type, const char* source);
	static GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);

	//calculate positions for texts
	static glm::vec2 screenPositions[8];
	static const glm::vec3 worldPositions[8];
	static glm::vec2 CalculateScreenPositionsPlayers(glm::vec3 playerpos, glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height);
	static void CalculateScreenPositions(glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height);

private:


	GLuint textVAO, textVBO;
};