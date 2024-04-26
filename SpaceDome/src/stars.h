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

#define M_PI 3.14159265358979323846

//Implemented as explicit singleton, handles pretty much everything
class Star
{

public:
    //defaul constructor
	Star(int id){
        int random = rand() % 100;  
        sId = id;

        double rand_angle = 2 * M_PI * rand() / (double)RAND_MAX; // Random angle
        double rand_radius = rand() / (double)RAND_MAX + rand() / (double)RAND_MAX; // Random radius
        double r = (rand_radius > 1) ? 2 - rand_radius : rand_radius;
        r *= (boundryX);

        sOrientation = (float)random/10;
        sPosition = glm::vec3(0.0, r*sin(rand_angle),r*cos(rand_angle));
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

    glm::vec3 getPosition(){ return sPosition; }

    int getID(){ return sId; }

    void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

private:

int sId;
glm::vec3 sPosition;
float sOrientation;
//yellow color
glm::vec3 sColor = {0.5f, 0.5f, 0.0f};
};