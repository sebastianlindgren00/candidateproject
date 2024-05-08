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

struct BulletData
{
	float bPositionX;
    float bPositionY;
    float bPositionZ;
    float bOrientation;
    int bTeam;
    int bID;	
};

//Implemented as explicit singleton, handles pretty much everything
class Bullet
{


public:
    //default constructor
	Bullet();

	//constructor
	Bullet(int team, float speed, glm::vec3 position,float orientation, int id){
        bSpeed = speed*3;
        bTeam = team;
        if(bTeam == 1){
            bColor = {1.0f, 0.2f, 0.2f};	
        } else {
            bColor = {0.4f, 1.f, 0.2f};
        };
        bPosition = position;
        bOrientation = orientation;
        bID = id;
    }

	//Destructor
	~Bullet();

	//Players should be unique
	Bullet(const Bullet&) = default;
	Bullet& operator=(const Bullet&) = delete;

    int getTeam(){ return bTeam; }
    
    glm::vec3 getPosition(){ return bPosition; }

    void setPosition(glm::vec3 pos) { bPosition = pos; }
    void setOrientation(float o) { bOrientation = o;}
    void setTeam(int t) {bTeam = t;}
    void setID(int i) {bID = i;}

    float getOrientation() {return bOrientation;}

    int getLifeTime(){ return lifeTime; }

    void update();

    int getID() {return bID;}

    void draw(const std::unique_ptr<AssimpLoader>& bulletsGreen,const std::unique_ptr<AssimpLoader>& bulletsRed, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const;

private:

int lifeTime = 0;
float bSpeed;
int bTeam;
int bID;
glm::vec3 bPosition;
float bOrientation;
glm::vec3 bColor = {1.0f, 0.3f, 0.3f};	
GLint bColLoc = -1;
};