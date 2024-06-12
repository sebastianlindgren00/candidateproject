#include "booster.h"

void Booster::rotate() {
    float framesPerSecond = 60.0f;
    float deltaTime = 1/framesPerSecond; // Frame time assuming 60 FPS
    orientation += 0.2f * deltaTime;
}

glm::vec3 Booster::generateBoosterPos() const {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> x_dist(-boundryX, boundryX);
    std::uniform_real_distribution<float> y_dist(-boundryY, boundryY);


    float x = x_dist(gen);
    float y = y_dist(gen);

    return glm::vec3(x, y, -1.5);
}