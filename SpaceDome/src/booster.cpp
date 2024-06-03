#include "booster.h"

void Booster::updateBooster() {
    float framesPerSecond = 60.0f;
    float deltaTime = 1/framesPerSecond; // Frame time assuming 60 FPS
    orientation += 0.2f * deltaTime;

}

void ShieldBooster::draw(const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const {
    Utility::setupShaderForDrawingMaterial(shaderProgram, position, orientation, 0.25, 1, pMatrix, vMatrix);

    auto& meshes = shieldModel->getMeshes(); // Using getMeshes() method to access the meshes
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(); // Draw each mesh
    }
}


void SpeedBooster::draw(const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const{
    Utility::setupShaderForDrawingMaterial(shaderProgram, position, orientation, 0.25, 1, pMatrix, vMatrix);

    auto& meshes = speedModel->getMeshes(); // Using getMeshes() method to access the meshes
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(); // Draw each mesh
    }
}



void ShieldBooster::activate(Player& player){
        player.setHasShield(true);
}

void SpeedBooster::activate(Player& player){

    if(!hasSpeedBooster){
        startSpeedBooster = sgct::time();
    }

    player.setSpeed(0.025f);
    hasSpeedBooster = true;
}

void ShieldBooster::hitByBullet(Player& player) {
    player.increaseBulletCounter();
}

void ShieldBooster::deActivate(Player& player){
    if(player.getBulletCounter() > 0) {
        player.resetBulletCounter();
        player.setHasShield(false);
        player.emptyActiveBoosters();
    }
}

void SpeedBooster::deActivate(Player& player){
    float currentTime = sgct::time();
    if(currentTime - startSpeedBooster >= maxSpeedBoosterTime){
        player.setSpeed(0.01f);
        player.emptyActiveBoosters();
    }
}