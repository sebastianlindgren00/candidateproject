#include "speedBooster.h"

void SpeedBooster::draw(glm::mat4 pMatrix, glm::mat4 vMatrix) const{
    Utility::setupShaderForDrawingMaterial(shaderProgramTexture, position, orientation, 0.25, 1, pMatrix, vMatrix);

    auto& meshes = speedModel->getMeshes();
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw();
    }
}

void SpeedBooster::activate(Player& player){
    startTime = sgct::time();
    player.setSpeed(boosterSpeed);
}


void SpeedBooster::deactivate(Player& player){
    if(sgct::time() - startTime > maxDuration){
        player.setSpeed(boosterBaseSpeed);
        deActviated = true;
    }
}