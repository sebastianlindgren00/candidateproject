#pragma once
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glad/glad.h"

struct Vertex
{
	glm::vec3 mPosition;
	glm::vec3 mNormal;
	glm::vec2 mTexCoords;
};

struct Texture
{
	unsigned mId = 0;
	std::string mType;
	std::string mPath;
};

//https://learnopengl.com/Model-Loading/Mesh

class Mesh
{
public:

    //Mesh data
	std::vector<Vertex> mVertices;
	std::vector<unsigned> mIndices;
	std::vector<Texture> mTextures;

	//Ctor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures);

	//draw
	void Draw() const;
private:

	//Render handles
	unsigned VAO, VBO, EBO;

	//setting up mesh
	void finaliseMesh();
};