#include "booster.h"

/**
 * @class SpeedBooster
 * @brief Class representing a speed booster.
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
     * @brief Handles the logic for the speedBooster. Will increase the speed for the player, with players setSpeed function, 
     * and will then reset the speed to the the base speed when timer is up.
     * 
     * @param Player Player object.
     * 
     */
    void deactivate(Player& player) override;

    void activate(Player& player) override;

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
    bool activated = false; /**< A bool to check if already activated */
    std::unique_ptr<AssimpLoader> speedModel; /**< The mesh for the speed booster model */
};