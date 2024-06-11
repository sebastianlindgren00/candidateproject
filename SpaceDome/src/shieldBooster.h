#pragma once

#include <iostream>
#include <memory>
#include <AssimpLoader.h>

#include "booster.h"
#include "player.h"

class Player;

/**
 * @class ShieldBooster
 * @brief Class representing a shield booster. When active, the players rocket ship will blink. If hit by a bullet while having an active shield,
 * the player will not die but the shield will deactivate. 
 */
class ShieldBooster : public Booster {
public:
    /**
     * @brief Constructor for ShieldBooster class.
     */
    ShieldBooster() : Booster() {
        shieldModel = std::make_unique<AssimpLoader>(path +"/shieldBooster.fbx");
    }

     /**
     * @brief Acitvates shield booster by setting the mHasShield variable for player to true
     * 
     * @param Player Player object
     */

    void activate(Player& player) override;

    /**
     * @brief Decitvates shield booster by setting the mHasShield variable for player to false. Is done if shieldHitCount is bigger than 0,
     * i.e if the player is hit by a bullet one time while having a shield.
     * 
     * @param Player Player object
     */

    void deactivate(Player& player) override;

    /**
     * @brief Is called if the player has a shield and has been hit by a bullet. Will then increment shieldHitCount which is then used to 
     * deactivate the shield.
     */

    void shieldHit();
    /**
     * @brief Draws the shield booster.
     * 
     * @param pMatrix The projection matrix.
     * @param vMatrix The view matrix.
     */
    void draw(glm::mat4 pMatrix, glm::mat4 vMatrix) const override;

private:
    std::unique_ptr<AssimpLoader> shieldModel; /**< The mesh for the shield model */
    int shieldHitCount = 0; /**< Counter for hits by bullet while having a shield. */
};

