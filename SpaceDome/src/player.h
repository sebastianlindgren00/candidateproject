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

struct PlayerData
{
public:

	//Game state data
    int mPlayerID;
	int mStarsCollected;
    int mStarsHolding;
	float mSpeed;
    glm::vec3 mPosition;

	char mPlayerName;
    char mTeam;
	//glm::vec3 mPlayerColour;
};

class Player
{
public:
	//Default ctor used for debugging
	Player();

	//Used for creating from tuple (server requested)
	Player(const int id, const std::string& name);

	//Dtor
	~Player();

	//Players should be unique
	Player(const Player&) = default;
	Player& operator=(const Player&) = delete;

	//Get/set playerdata during synchronisation
	void setPlayerData(const PlayerData& newPlayerData);

	//Update position
	void update(float deltaTime, int turn);

	//Draw objects
	void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

	//Accessors
	float getSpeed() const { return mSpeed; };
	float getTurnSpeed() const { return mTurnSpeed; }
    int getID() const { return mPlayerID; }
	//const int getStars() const { return mStars; };
    //const int getHoldingStars() {return mStarsHolding; }
	const std::string& getName() const { return mName; };
    //const bool isAlive() const { return mIsAlive; };
    
    // Iris: trying to send colours
    glm::vec3 getColours() const { return mPlayerColour; };

	//Mutators
	void addStarHolding() { mStarsHolding += 1; }
	//void setSpeed(float speed) override { mSpeed = speed; };
	void addHandedInStars(int mStarsHolding) { mStars += mStarsHolding; };
	//void setTurnSpeed(float turnSpeed) override { mTurnSpeed = turnSpeed; 
    void setIsAlive(bool isAlive) { mIsAlive = isAlive; };

    void setPosition(const glm::vec3& positionChange) {
        mPosition += positionChange;
    }
    
    // Method to adjust orientation
    void setOrientation(float angleSpeed) {
        mOrientation += angleSpeed;
    }
    float getOrientation(){return mOrientation; }

private:
	//Player information/data
	float mTurnSpeed = 0.2f;
	int   mStars    = 0;
    int mStarsHolding = 0;
	float mSpeed     = 0.1f;
    int mPlayerID;
    bool mIsAlive = false;
	std::string mName;

    glm::vec3 mPosition;
    float mOrientation = 0.0f;

	// frans; Trying something with colors
	glm::vec3 mPlayerColour;	
    GLint mColLoc = -1;
};