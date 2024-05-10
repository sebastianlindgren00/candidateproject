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

class Game;

class Utility
{
public:

	//constructor
	Utility(){
		setupPlane();
    	setupText();
	}

	static Utility& getInstance() {
        static Utility instance;
        return instance;
    }

	//load fonts
	static void LoadFontAtlas(const std::string& fontPath);
	//rendering text
	void RenderText(GLuint shaderProgram, std::string text, int row, float scale, glm::vec3 color,  float width, float height);
	void RenderTextPlayers(GLuint shaderProgram, const std::vector<std::tuple<std::string, float, float, float, glm::vec3>>& texts, int width, int height);
	void RenderSingleText(GLuint shaderProgram, const std::string& text, float x, float y, float scale, const glm::vec3& color);
	void renderPlane(GLuint shaderProgram, GLuint textureId, const glm::mat4& projection, const glm::mat4& view);
	
	void setScaleConst(float s) {scale = s;}

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
	static glm::vec2 CalculateScreenPositionsPlayers(glm::vec3 playerpos, glm::mat4 pMatrix, glm::mat4 vMatrix, float width, float height);
	static void CalculateScreenPositions(glm::mat4 pMatrix, glm::mat4 vMatrix, float width, float height);

	static float scale;

private:

	Utility(const Utility&) = delete; // Prevent copying
    void operator=(const Utility&) = delete;

	std::vector<float> planeVertices;   // Using vector to handle dynamic size
    std::vector<unsigned int> planeIndices;
    GLuint textVAO, textVBO;

	static GLuint planeVAO;
    static GLuint planeVBO;
    static GLuint planeEBO;
    static bool planeInitialized;

    static void setupPlane();
    void setupText();
};