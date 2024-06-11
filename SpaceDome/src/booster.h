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
#include "bullets.h"

class Player;

/**
 * @class Booster 
 */
class Booster {

public:
    /**
     * @brief Constructor for Booster class. 
     */
    Booster() { position = generateBoosterPos(); 
        
    }
    /**
     * @brief Activates booster, is done in game.cpp when a player is close enough to a booster. 
     * 
     * @param Player Player object
     */

    virtual void activate(Player& player) = 0;

    /**
     * @brief Dectivates booster, is called by in player.cpp. 
     * 
     * @param Player Player object
     */

    virtual void deactivate(Player& player) = 0;

    /**
     * @brief Virtual function to draw the booster.
     * 
     * @param pMatrix The projection matrix.
     * @param vMatrix The view matrix.
     */
    virtual void draw(glm::mat4 pMatrix, glm::mat4 vMatrix) const = 0;

    /**
     * @brief Rotates the booster.
     */
    void updateBooster();

    /**
     * @brief Generate random position for the booster.
     * 
     * @return The position of the booster.
     */
    glm::vec3 generateBoosterPos() const;

    /**
     * @brief Gets the position of the booster. Is used in game.cpp to see if the player is close enough to get the booster.
     * 
     * @return The position of the booster.
     */
    glm::vec3 getPosition() const { return position; }

    /**
     * @brief Checks if the booster is deactivated. The purpose of this function is to be able to remove deactivated boosters from the booster 
     * vector in player.
     * 
     * @return Is set to true if the deactive function has been called for a booster. 
     * 
     */
    bool isDeactivated() { return deActviated; }

protected:

    glm::vec3 position; /**< The position of the booster. */
    float orientation = 1.0f; /**< The orientation of the booster. */
    bool deActviated = false; /**< Whether the booster has been deactivated. */
    // annan gruppmedlem hade gjort en path i cmakelist för dem andra modellerna så använde den
    std::string path = std::string(MODELS_DIRECTORY); /** Path to the models for the boosters */
};