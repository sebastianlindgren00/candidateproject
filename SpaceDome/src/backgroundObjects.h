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
class BackgroundObject
{

public:
    //defaul constructor
	BackgroundObject(float x){
        int random = rand() % 100;  
        int yRand = rand() % 400;
        int zRand = rand() % 600;
        xPos = x;
        bSpeed *= (float)random/10;
        bOrientationSpeed = (float)random/10000;
        bOrientation = (float)random/10;
        bDirection = bOrientation;
        bPosition = glm::vec3(xPos, (2 - (float)yRand/100),(3 - (float)zRand/100));
    }

	//constructor

	//Destructor
	~BackgroundObject();

	//Players should be unique
	BackgroundObject(const BackgroundObject&) = default;
	BackgroundObject& operator=(const BackgroundObject&) = delete;

    void setPosition(const glm::vec3& positionChange) { bPosition += positionChange; }

    void update();

    void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

private:
float bOrientationSpeed;
float xPos;
float bSpeed = 0.001f;
glm::vec3 bPosition;
float bDirection;
float bOrientation;
glm::vec3 bColor = {0.3f, 0.3f, 0.3f};	
//GLint sColLoc = -1;
};