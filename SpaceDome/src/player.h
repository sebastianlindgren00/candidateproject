#pragma once

#include "globals.h"
#include <string>
#include <vector>
#include <iostream>
#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "mesh.h"
#include "utility.h"
#include "shader.h"
#include "bullets.h"

class Player
{
public:
	//Default constructor
	Player();

	//Constructor
	Player(const int id, const std::string& name, int team);

	//Destructor
	~Player();

	//Players should be unique
	Player(const Player&) = default;
	Player& operator=(const Player&) = delete;

	void setTurnSpeed(float turnSpeed) { mTurnSpeed = turnSpeed; };

	//Update position
	void update(float deltaTime,const std::vector<std::unique_ptr<Bullet>>& mBullets);

	//Draw the player
	void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

	//Accessors
	float getSpeed() const { return mSpeed; };
	float getTurnSpeed() const { return mTurnSpeed; }
    int getID() const { return mPlayerID; }
	//const int getStars() const { return mStars; };
    //const int getHoldingStars() {return mStarsHolding; }
	const std::string& getName() const { return mName; };
    //const bool isAlive() const { return mIsAlive; };
    
    glm::vec3 getColours() const { return mPlayerColor; };

	void addStarHolding() { mStarsHolding += 1; }

	bool hasStars(){ return mStars > 0; }

	void nullStars() {mStars = 0;}

	int getStars() { return mStars; }

	void addHandedInStars(int addStars) { mStars += addStars; };

    void setIsAlive(bool isAlive) { mIsAlive = isAlive; };

    void setPosition(const glm::vec3& positionChange) { mPosition += positionChange; }

	void setChargeMode(bool mode){ chargeActive = mode; }

	int getSuperCharge(){ return superCharge; }

	void useSuperCharge(){ superCharge -= 1; }

	void fillSuperCharge(){ superCharge += 1; }

	glm::vec3 getPosition(){ return mPosition; }

	int getTeam(){ return mTeam; }

    void setOrientation(float angleSpeed) { mOrientation += angleSpeed; }
    float getOrientation(){return mOrientation; }

	int getBulletTimer() { return bulletTimer; }

    void increaseTimer() {bulletTimer++;}

    void restoreTimer() {bulletTimer = 0;}

private:
	//Player information/data
	int bulletTimer = 10;
	float mTurnSpeed = 0.0f;
	int   mStars    = 0;
    int mStarsHolding = 0;
	float mSpeed     = 0.0001f;
    int mPlayerID;
    bool mIsAlive = false;
	int superCharge = 300;
	std::string mName;
	bool chargeActive = false;
	int delayForRefill = 0;
	int wait = 5;
    glm::vec3 mPosition;
    float mOrientation = 0.0f;
	int respawnTimer = 0;
	int mTeam = 0;
	// frans; Trying something with colors
	glm::vec3 mPlayerColor;	
    GLint mColLoc = -1;
	float hitRadius = 0.4f;
};