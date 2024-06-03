#pragma once

#include <vector>

#include "mesh.h"
#include "utility.h"
#include "player.h"

class Player;


class Booster {

    public:

        Booster(glm::vec3 pos) : position(pos) {}
    
        virtual void draw(const std::unique_ptr<AssimpLoader>& shieldModel, const std::unique_ptr<AssimpLoader>& speedBoosterModel, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const = 0;
        void updateBooster();

        //virtual void activate(Player& player) = 0;
        virtual void deActivate(Player& player) = 0;
        virtual void activate(Player& player) = 0;
        //virtual bool isActive() = 0;

        glm::vec3 getPosition() {return position;}


protected:

    glm::vec3 position;
    float orientation = 1.0f;

};

class ShieldBooster : public Booster {
public:
    ShieldBooster(glm::vec3 pos)
        : Booster(pos), hitByBulletCounter(0), hasShield(true) {}

    void activate(Player& player);
    void deActivate(Player& player) override;

    void hitByBullet(Player& player); 
    bool isActive(){
        return hasShield;
    };
    void draw(const std::unique_ptr<AssimpLoader>& shieldModel, const std::unique_ptr<AssimpLoader>& speedBoosterModel, GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const override;


private:
    int hitByBulletCounter;
    bool hasShield = false;
};



class SpeedBooster : public Booster {
public:
    SpeedBooster(glm::vec3 pos) : Booster(pos), boosterSpeed(0.025f), hasSpeedBooster(false), startSpeedBooster(0.0f) {}


    void activate(Player& player);
    void deActivate(Player& player) override;
    bool isActive(){
        return hasSpeedBooster;
    }
    void draw(const std::unique_ptr<AssimpLoader>& shieldModel, const std::unique_ptr<AssimpLoader>& speedBoosterModel, GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const override;

private:

    float boosterSpeed;
    float startSpeedBooster;
    float maxSpeedBoosterTime = 3;
    bool hasSpeedBooster;
};






// class Booster {

//     public:

//         Booster(int sType) {
//             int random = rand() % 100;  
// /*
//             double rand_angle = 2 * M_PI * rand() / (double)RAND_MAX; // Random angle
//             double rand_radius = rand() / (double)RAND_MAX + rand() / (double)RAND_MAX; // Random radius
//             double r = (rand_radius > 1) ? 2 - rand_radius : rand_radius;
//             r *= (boundryX);
//     */
//             std::random_device rd;
//             std::mt19937 gen(rd());

//             //Define the range for x and y
//             std::uniform_real_distribution<float> x_dist(-boundryX, boundryX);
//             std::uniform_real_distribution<float> y_dist(-boundryY, boundryY);

//             //Generate random x and y positions
//             float x = x_dist(gen);
//             float y = y_dist(gen);

//             orientation = (float)random/10;
//             pos = glm::vec3(x, y, -1.5);

//             type = sType;

//         }

//         void draw(const std::unique_ptr<AssimpLoader>& shieldModel, const std::unique_ptr<AssimpLoader>& speedBoosterModel, const GLuint shaderProgram ,glm::mat4 pMatrix, glm::mat4 vMatrix) const;
//         void update();

//         glm::vec3 getPosition() {return pos;}
//         int getType() {return type;}

//         void setOrientation(float newOrientation){orientation = newOrientation;}

//         Booster(const Booster&) = default;
//         Booster& operator=(const Booster&) = delete;
        

//     private:

//         int type; 
//         glm::vec3 pos = glm::vec3(1.0f, 0.3f, 0.8f);

//         float orientation;


//         int hitCounter;

// };