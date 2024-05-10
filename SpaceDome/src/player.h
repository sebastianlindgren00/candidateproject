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

//#define M_PI 3.14159265358979323846

struct playerData {
	int ID;
    bool useSuperCharge;
	bool useShot;
	bool turnSpeed;
};

struct PlayerData
{
	//bool mIsAlive;
	//std::string mName;
	int mPlayerID;
	int mColorID;
	float mOrientation;
	float mPositionX;
	float mPositionY;
	float mPositionZ;
	int mTeam;
	int mStars;
	int mStarsHolding;
	int mSuperCharge;
	int shotAvailable;
	double mTurnSpeed;
	int mBulletTimer;
	float mSpeed;
};

class Player
{
public:
	//Default constructor
	Player();

	//Constructor
	Player(const int id, const std::string& name, int team, int colorID, glm::vec3 color, glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height);

	//Destructor
	~Player();

	//Players should be unique
	Player(const Player&) = default;
	Player& operator=(const Player&) = delete;

	void setTurnSpeed(double turnSpeed) { mTurnSpeed = turnSpeed; };

	//Update position
	int update(const std::vector<std::unique_ptr<Bullet>>& mBullets, float height);

	//Draw the player
	void draw(const std::vector<std::unique_ptr<AssimpLoader>>& modelsRed ,const std::vector<std::unique_ptr<AssimpLoader>>& modelsGreen, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const;

	void updatePlayerData(playerData& data);

	//Accessors
	float getSpeed() const { return mSpeed; };
	double getTurnSpeed() const { return mTurnSpeed; }
    int getID() const { return mPlayerID; }
	const std::string& getName() const { return mName; };
    
    glm::vec3 getColours() const { return mPlayerColor; };

	void addStarHolding() { mStarsHolding += 1; }

	bool hasStars(){ return mStarsHolding > 0; }

	void nullStars() {mStarsHolding = 0;}

	int getStars() { return mStarsHolding; }

	int getHandedInStars() { return mStars; }

	void addHandedInStars(int addStars) { mStars += addStars; };

    void setIsAlive(bool isAlive) { mIsAlive = isAlive; };

    void setPosition(const glm::vec3& positionChange) { mPosition += positionChange; }

	void setChargeMode(bool mode){ chargeActive = mode; }

	int getSuperCharge(){ return superCharge; }

	void useSuperCharge(){ superCharge -= 1; }

	void fillSuperCharge(){ superCharge += 1; }

	glm::vec3 getPosition(){ return mPosition; }

	float getPositionX(){ return mPosition.x; }

	float getPositionY(){ return mPosition.y; }
	
	float getPositionZ(){ return mPosition.z; }

	int getTeam(){ return mTeam; }

	void resetAllStars() { mStars = 0; mStarsHolding = 0;}

	void setSpawnTimerFull() { respawnTimer = 500;}

    void setOrientation(float angleSpeed) { mOrientation += angleSpeed; }

    float getOrientation(){return mOrientation; }

	int getBulletTimer() { return bulletTimer; }

    void increaseTimer() {bulletTimer++;}

    void restoreTimer() {bulletTimer = 0;}

	bool getDropStars() {return dropStars;}

	void setDropStars() {dropStars = false;}
	
	bool isAlive() {return mIsAlive;}

	int getShotAvailable() {return shotAvailable;}

	int getColorID() { return mColorID;}

	bool canShot(){ return bulletTimer == shotAvailable;}

	float getTextX() { return textPosition.x; }
	float getTextY() { return textPosition.y; }

	void setTextPos(glm::vec2 pos) { textPosition = pos; }

	bool getShotBullet() { return shotBullet;}


private:
	//Player information/data

	//stars data
	bool dropStars = false;
	int   mStars    = 0;
    int mStarsHolding = 0;

	//for super Charge
	int superCharge = 300;
	bool chargeActive = false;
	int delayForRefill = 0;
	int delay = 5;

	//movement / positioning / player data
	int mPlayerID;
	std::string mName;
	int mTeam = 0;

    glm::vec3 mPosition;
    float mOrientation = 0.0f;
	double mTurnSpeed = 0.0f;
	float mSpeed     = 0.0001f;
	glm::vec3 mPlayerColor;	
	int mColorID;
	float hitRadius = 0.2f;

	//Alive and respawn timer
	bool mIsAlive = false;
	int respawnTimer = 0;

	//info for bullets/shooting
	bool shotBullet = false;
	int shotAvailable = 75;
	int bulletTimer = 0;

	glm::vec2 textPosition;
	GLint mColLoc = -1;
	
};