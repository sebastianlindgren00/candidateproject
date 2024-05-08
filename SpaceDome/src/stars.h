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

//#define M_PI 3.14159265358979323846


struct StarData
{
	float sPositionX;
    float sPositionY;
    float sPositionZ;
    float sOrientation;
};

//Implemented as explicit singleton, handles pretty much everything
class Star
{

public:
    //defaul constructor
	Star(int id){
        int random = rand() % 100;  
        sId = id;
/*
        double rand_angle = 2 * M_PI * rand() / (double)RAND_MAX; // Random angle
        double rand_radius = rand() / (double)RAND_MAX + rand() / (double)RAND_MAX; // Random radius
        double r = (rand_radius > 1) ? 2 - rand_radius : rand_radius;
        r *= (boundryX);
*/
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define the range for x and y
        std::uniform_real_distribution<float> x_dist(-boundryX, boundryX);
        std::uniform_real_distribution<float> y_dist(-boundryY, boundryY);

        // Generate random x and y positions
        float x = x_dist(gen);
        float y = y_dist(gen);

        sOrientation = (float)random/10;
        sPosition = glm::vec3(x, y, -1.5);
    }

	//constructor for when players drop stars (needs a position)
	Star(glm::vec3 position, int id) {
        sPosition = position;
        int random = rand() % 100;  
        sOrientation = (float)random/10;
        sId = id;
    }

	//Destructor
	~Star();

	//Stars should be unique
	Star(const Star&) = default;
	Star& operator=(const Star&) = delete;

    void update(std::vector<std::unique_ptr<Star>>& stars);

    void setPosition(glm::vec3 pos) { sPosition = pos;}
    void setOrientation(float o) {sOrientation = o;}

    float getOrientation() {return sOrientation;}

    glm::vec3 getPosition(){ return sPosition; }

    int getID(){ return sId; }

    void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const;

private:

int sId;
glm::vec3 sPosition;
float sOrientation;
//yellow color
glm::vec3 sColor = {0.5f, 0.5f, 0.0f};
};