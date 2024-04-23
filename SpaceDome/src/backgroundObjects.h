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
    //Constructor
	BackgroundObject(float x){

        //spawn at random locations with random velocitys and orientations
        int random = rand() % 100;  
      
        xPos = x;
        bSpeed *= (float)random/10;
        bOrientationSpeed = (float)random/10000;
        bOrientation = (float)random/10;
        bDirection = bOrientation;


        double rand_angle = 2 * M_PI * rand() / (double)RAND_MAX; // Random angle
        double rand_radius = rand() / (double)RAND_MAX + rand() / (double)RAND_MAX; // Random radius
        double r = (rand_radius > 1) ? 2 - rand_radius : rand_radius;
        r *= (boundryX*2);
        bPosition = glm::vec3(xPos, r*sin(rand_angle),r*cos(rand_angle));
    }
	//Destructor
	~BackgroundObject();

	//Objects should be unique
	BackgroundObject(const BackgroundObject&) = default;
	BackgroundObject& operator=(const BackgroundObject&) = delete;

    void setPosition(const glm::vec3& positionChange) { bPosition += positionChange; }

    glm::vec3 getPosition() {return bPosition;}

    void setOrientation(float newOrientation) { bDirection = newOrientation;}

    float getOrientation() { return bDirection;}

    void setSpeed(float newSpeed) { bSpeed = newSpeed;}

    float getSpeed() {return bSpeed;}

    void update(std::vector<std::unique_ptr<BackgroundObject>>& mBGObjects);

    void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

private:
float size = 0.4;
int axis = rand() % 3;
float bOrientationSpeed;
float xPos;
float bSpeed = 0.001f;
glm::vec3 bPosition;
float bDirection;
float bOrientation;
glm::vec3 bColor = {0.3f, 0.3f, 0.3f};	
//GLint sColLoc = -1;
};