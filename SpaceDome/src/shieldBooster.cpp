#include "shieldBooster.h"

void ShieldBooster::draw(glm::mat4 pMatrix, glm::mat4 vMatrix) const {
    Utility::setupShaderForDrawingMaterial(shaderProgramTexture, position, orientation, 0.25, 1, pMatrix, vMatrix);

    auto& meshes = shieldModel->getMeshes();
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw();
    }
}

void ShieldBooster::activate(Player& player){
    player.setHasShield(true);
}

void ShieldBooster::update(Player& player) {
    
    if (shieldHitCount > 0) {
        deActviated = true;
        player.setHasShield(false);
        shieldHitCount = 0;
    }
}

void ShieldBooster::shieldHit() {
    shieldHitCount++;
}


