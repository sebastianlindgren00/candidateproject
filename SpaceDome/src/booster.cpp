#include "booster.h"

void Booster::updateBooster() {
    float framesPerSecond = 60.0f;
    float deltaTime = 1/framesPerSecond; // Frame time assuming 60 FPS
    orientation += 0.2f * deltaTime;
}

void ShieldBooster::draw(const GLuint shaderBooster, glm::mat4 pMatrix, glm::mat4 vMatrix) const {
    Utility::setupShaderForDrawingMaterial(shaderBooster, position, orientation, 0.25, 1, pMatrix, vMatrix);

    auto& meshes = shieldModel->getMeshes();
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw();
    }
}

void SpeedBooster::draw(const GLuint shaderBooster, glm::mat4 pMatrix, glm::mat4 vMatrix) const{
    Utility::setupShaderForDrawingMaterial(shaderBooster, position, orientation, 0.25, 1, pMatrix, vMatrix);

    auto& meshes = speedModel->getMeshes();
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw();
    }
}

glm::vec3 Booster::generateBoosterPos() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> x_dist(-boundryX, boundryX);
    std::uniform_real_distribution<float> y_dist(-boundryY, boundryY);


    float x = x_dist(gen);
    float y = y_dist(gen);

    return glm::vec3(x, y, -1.5);
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