#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <tuple>
#include <cmath>
#include <random>
#include <cstddef>
#include <chrono>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "mesh.h"
#include "utility.h"

//Implemented as explicit singleton, handles pretty much everything
class Star
{

public:
    //defaul constructor
	Star(int id){
        int random = rand() % 100;  
        int yRand = rand() % 200;
        int zRand = rand() % 200;
        sId = id;

        sOrientation = (float)random/10;
        sPosition = glm::vec3(0.0, (1 - (float)yRand/100),(1 - (float)zRand/100));
    }

	//constructor
	Star(glm::vec3 position, int id){
        sPosition = position;
        int random = rand() % 100;  
        sOrientation = (float)random/10;
        sId = id;
    }

	//Destructor
	~Star();

	//Players should be unique
	Star(const Star&) = default;
	Star& operator=(const Star&) = delete;

    void update();

    glm::vec3 getPosition(){ return sPosition; }

    int getID(){ return sId; }

    void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

private:

int sId;
glm::vec3 sPosition;
float sOrientation;
glm::vec3 sColor = {1.0f, 0.3f, 0.3f};	
//GLint sColLoc = -1;
};