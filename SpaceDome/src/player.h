#pragma once

#include "globals.h"
#include <unordered_map>
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
	//stars data
	int64_t dropStars;
	int mStars;
    int mStarsHolding;
	//for super Charge
	int superCharge;
	int64_t chargeActive;
	int delayForRefill;
	int delay;
	//movement / positioning / player data
	int mPlayerID;
	int mTeam;
    float mPositionX;
	float mPositionY;
	float mPositionZ;
    float mOrientation;
	float mTurnSpeed;
	float mSpeed;
	int mColorID;
	float hitRadius;
	//Alive and respawn timer
	int64_t mIsAlive;
	int respawnTimer;
	//info for bullets/shooting
	int64_t shotBullet;
	int shotAvailable;
	int bulletTimer;
};

struct PlayerName{
	unsigned long long playerName;
};



class Player
{
public:
	//Default constructor
	Player();

	//Constructor
	Player(const int id, const std::string& name, int team, int colorID, glm::vec3 color, glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height);

	//Constructor for sync
	Player(PlayerData data, PlayerName name, glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height){
    setData(data);
	setName(name.playerName);

    textPosition = Utility::CalculateScreenPositionsPlayers( mPosition * glm::vec3(1,-1,1) - glm::vec3(0,-0.5f,0), pMatrix, vMatrix, width, height);
	}

	//Constructor for sync
	Player(PlayerData data, glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height){
    setData(data);

    textPosition = Utility::CalculateScreenPositionsPlayers( mPosition * glm::vec3(1,-1,1) - glm::vec3(0,-0.5f,0), pMatrix, vMatrix, width, height);
	}
	//Destructor
	~Player();

	//Players should be unique
	Player(const Player&) = default;
	Player& operator=(const Player&) = delete;

	// Converts a single uppercase letter to a corresponding numeric value (1-based index)
	int charToNumber(char c) {
    return (c - 'A' + 1); // 'A' is 65 in ASCII
	}

	// Converts a numeric value back to the corresponding uppercase letter
	char numberToChar(int n) {
		return static_cast<char>(n + 'A' - 1);
	}

	// Encodes an uppercase string into a numeric representation using unsigned long long
	unsigned long long encodeULL(const std::string& input) {
		std::string encodedString;
		for (char c : input) {
			int number = charToNumber(c);
			if (number < 10) {
				encodedString += "0"; // Add leading zero to maintain two-digit formatting
			}
			encodedString += std::to_string(number);
		}
		return std::stoull(encodedString);
	}

	// Decodes a numeric representation back to an uppercase string
	std::string decodeULL(unsigned long long value) {
		std::string encodedString = std::to_string(value);
		std::string result;

		// Process the digits two at a time
		for (size_t i = 0; i < encodedString.length(); i += 2) {
			int number = std::stoi(encodedString.substr(i, 2));
			result += numberToChar(number);
		}
		return result;
	}

	void getName(unsigned long long& n){
		n = encodeULL(mName);
	}
	void setName(unsigned long long n){
		mName = decodeULL(n);
	}

	void setNameData(PlayerName data){
		mName = decodeULL(data.playerName);
	}

	void getData(PlayerData& data){
		//stars data
		if(dropStars){
			data.dropStars = 1;
		} else{
			data.dropStars = 0;
		}
	
	data.mStars = mStars;
    data.mStarsHolding = mStarsHolding;
	//for super Charge
	data.superCharge = superCharge;
	if(chargeActive){
		data.chargeActive = 1;
	} else{
		data.chargeActive = 0;
	}
	
	data.delayForRefill = delayForRefill;
	data.delay = delay;
	//movement / positioning / player data
	data.mPlayerID = mPlayerID;
	data.mTeam = mTeam;
    data.mPositionX = (float)mPosition.x;
	data.mPositionY = (float)mPosition.y;
	data.mPositionZ = (float)mPosition.z;
	
    data.mOrientation = mOrientation;
	data.mTurnSpeed = mTurnSpeed;
	data.mSpeed = mSpeed;
	data.mColorID = mColorID;
	data.hitRadius = hitRadius;
	//Alive and respawn timer
	if(mIsAlive){
		data.mIsAlive = 1;
	} else {
		data.mIsAlive = 0;
	}
	
	data.respawnTimer = respawnTimer;
	//info for bullets/shooting
	if(shotBullet){
		data.shotBullet = 1;
	} else {
		data.shotBullet = 0;
	}
	
	data.shotAvailable = shotAvailable;
	data.bulletTimer = bulletTimer;

	}

	void setData(PlayerData data){
		//stars data
		if(data.dropStars == 1){
			dropStars = true;
		} else{
			dropStars = false;
		}
	
	mStars = data.mStars;
    mStarsHolding = data.mStarsHolding;
	//for super Charge
	superCharge = data.superCharge;
	if(data.chargeActive == 1){
		chargeActive = true;
	} else{
		chargeActive = false;
	}
	
	delayForRefill = data.delayForRefill;
	delay = data.delay;
	//movement / positioning / player data
	mPlayerID = data.mPlayerID;
	mTeam = data.mTeam;
    mPosition.x = data.mPositionX;
	mPosition.y = data.mPositionY;
	mPosition.z = data.mPositionZ;
	
    mOrientation = data.mOrientation;
	mTurnSpeed = data.mTurnSpeed;
	mSpeed = data.mSpeed;
	mColorID = data.mColorID;
	hitRadius = data.hitRadius;
	//Alive and respawn timer
	if(data.mIsAlive == 1){
		mIsAlive = true;
	} else {
		mIsAlive = false;
	}
	
	respawnTimer = data.respawnTimer;
	//info for bullets/shooting
	if(data.shotBullet == 1){
		shotBullet = true;
	} else {
		shotBullet = false;
	}
	
	shotAvailable = data.shotAvailable;
	bulletTimer = data.bulletTimer;
	}

	void setTurnSpeed(float turnSpeed) { mTurnSpeed = turnSpeed; };

	//Update position
	int update(const std::vector<std::unique_ptr<Bullet>>& mBullets, float height);

	//Draw the player
	void draw(const std::vector<std::unique_ptr<AssimpLoader>>& modelsRed ,const std::vector<std::unique_ptr<AssimpLoader>>& modelsGreen, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const;

	void updatePlayerData(playerData& data);

	//Accessors
	float getSpeed() const { return mSpeed; };
	float getTurnSpeed() const { return mTurnSpeed; }
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

	void setPositionComplete(const glm::vec3& positionChange){ mPosition = positionChange;}

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

	void setOrientationComplete(float angle) { mOrientation = angle; }

    float getOrientation(){return mOrientation; }

	int getBulletTimer() { return bulletTimer; }

    void increaseTimer() {bulletTimer++;}

    void restoreTimer() {bulletTimer = 0;}

	std::string getName() {return mName;}

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
	float mTurnSpeed = 0.0f;
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