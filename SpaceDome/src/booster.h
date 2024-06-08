#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <AssimpLoader.h>
#include "assimp/Importer.hpp"


#include "mesh.h"
#include "utility.h"
#include "player.h"

class Player;


class Booster {

    public:

        Booster(){position = generateBoosterPos();}
    
        virtual void draw(const GLuint shaderBooster, glm::mat4 pMatrix, glm::mat4 vMatrix) const = 0;
        virtual void deActivate(Player& player) = 0;
        virtual void activate(Player& player) = 0;

        void updateBooster();
        glm::vec3 generateBoosterPos();
        glm::vec3 getPosition() {return position;}
        bool getIsDeactived(){ return isDeactived;}

    protected:

        glm::vec3 position;
        float orientation = 1.0f;
        bool isDeactived = false;

};

class ShieldBooster : public Booster {
public:
    ShieldBooster() : Booster(){
        std::string shieldModelPath = std::string("C:/Users/corne/Kanditatprojekt/candidateproject/SpaceDome/src/models") + "/" + allModelNames[12] + ".fbx";
        shieldModel = std::make_unique<AssimpLoader>(shieldModelPath);
    }

    void hitByBullet(Player& player); 

    void activate(Player& player);
    void deActivate(Player& player) override;
    void draw(GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const override;

    private:
        std::unique_ptr<AssimpLoader> shieldModel;
};

class SpeedBooster : public Booster {
public:
    SpeedBooster() : Booster(), boosterSpeed(0.025f), hasSpeedBooster(false), startSpeedBooster(0.0f) {
        std::string speedModelPath = std::string("C:/Users/corne/Kanditatprojekt/candidateproject/SpaceDome/src/models") + "/" + allModelNames[11] + ".fbx";
        speedModel = std::make_unique<AssimpLoader>(speedModelPath);
    }

    void activate(Player& player);
    void deActivate(Player& player) override;
    void draw(GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const override;

private:

    float boosterSpeed;
    float startSpeedBooster;
    float maxSpeedBoosterTime = 3;
    bool hasSpeedBooster;
    std::unique_ptr<AssimpLoader> speedModel;
};