#pragma once
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "shader.h"
#include "globals.h"

//https://learnopengl.com/Model-Loading/Mesh

#include <glm/gtc/matrix_transform.hpp>
using namespace std;
//GLuint shaderProgram;


#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 mPosition;
    // normal
    glm::vec3 mNormal;
    // texCoords
    glm::vec2 mTexCoords;
    // tangent
    glm::vec3 mTangent;
    // bitangent
    glm::vec3 mBitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int mId;
    string mType;
    string mPath;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    unsigned int VAO;

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    // render the mesh
    void Draw() const;

private:
    // render data 
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};