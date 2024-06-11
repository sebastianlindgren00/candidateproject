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

/**
 * @class Booster 
 * 
 * @brief This class provides two booster, one speed booster which makes the player go faster and a shield booster that makes the player
 * not die if hit by a bullet. The different boosters are subclasses derived from the abstract class Booster. There are three virtual functions:
 * activate, deactivate and draw.  
 */
class Booster {

public:
    /**
     * @brief Constructor for Booster class. New boosters generate every third second and the maximum amount of boosters on the 
     * field at the same time is 15. 
     */
    Booster() { position = generateBoosterPos(); }
    /**
     * @brief Activates booster and is implenteted in the derived classes. The booster is activated by modifying the properties of the 
     * player provided as input. 
     * 
     * @param Player Player object
     */

    virtual void activate(Player& player) = 0;

    /**
     * @brief Dectivates booster and is implented in the derived classes, is called by in players update function. 
     * 
     * @param Player Player object
     */

    virtual void deactivate(Player& player) = 0;

    /**
     * @brief Virtual function to draw the booster. The meshes are loaded in the subclasses and shaderProgramTexture is used, which is a global
     * variable.
     * 
     * @param pMatrix The projection matrix.
     * @param vMatrix The view matrix.
     */
    virtual void draw(glm::mat4 pMatrix, glm::mat4 vMatrix) const = 0;

    /**
     * @brief Rotates the booster. 
     */
    void rotate();

    /**
     * @brief Generate random position for new booster, limited to the boundry of the game field.
     * 
     * @return The position of the booster.
     */
    glm::vec3 generateBoosterPos() const;

    /**
     * @brief Gets the position of the booster.
     * 
     * @return The position of the booster.
     */
    glm::vec3 getPosition() const { return position; }

    /**
     * @brief Checks if the booster is deactivated. The purpose of this function is to be able to remove deactivated boosters from the booster 
     * vector in player. deActivated is set to true in derived classes when it's deactivation function has been called. 
     * 
     * @return Is set to true if the deactive function has been called for a booster. 
     * 
     */
    bool isDeactivated() { return deActviated; }

protected:

    glm::vec3 position; /**< The position of the booster. */
    float orientation = 1.0f; /**< The orientation of the booster. */
    bool deActviated = false; /**< Whether the booster has been deactivated. */
    std::string path = std::string(MODELS_DIRECTORY); /** Path to the models for the boosters */
};