#include "booster.h"

/**
 * @class SpeedBooster
 * @brief The player will go faster for 5 seconds if activated.
 */
class SpeedBooster : public Booster {
public:
    /**
     * @brief Constructor for SpeedBooster class.
     */
    SpeedBooster() : Booster(), boosterSpeed(0.025f), startTime(0.0f) {
        speedModel = std::make_unique<AssimpLoader>(path + "/speedBooster.fbx");
    }
    /**
     * @brief Activiates speed booster by setting the speed of the player to 0.025f.
     * 
     * @param Player Player object.
     * 
     */
    void activate(Player& player) override;

    /**
     * @brief Checks for every frame if the time passed since the booster was first activated exceeds the maximum duration. If true, it modifies the 
     * player's speed to the base speed.
     * @param Player Player object.
     * 
     */
    void update(Player& player) override;

    /**
     * @brief Draws the speed booster.
     * 
     * @param pMatrix The projection matrix.
     * @param vMatrix The view matrix.
     */
    void draw(glm::mat4 pMatrix, glm::mat4 vMatrix) const override;

private:
    float boosterSpeed; /**< The speed of player while having the booster. */
    float boosterBaseSpeed = 0.01f;/** < The normal speed of the player */
    double startTime; /**< The start time of the booster. */
    double maxDuration = 5; /**< The maximum duration of the speed booster. */
    std::unique_ptr<AssimpLoader> speedModel; /**< The mesh for the speed booster model */
};