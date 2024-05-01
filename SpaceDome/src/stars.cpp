#include "stars.h"
#include <random>
#include <cmath>

Star::~Star()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

#include <random>
#include <cmath> // For sin and cos functions

void Star::update(std::vector<std::unique_ptr<Star>>& stars) {
    glm::vec3 tempPosition = glm::vec3(0.0, 0.0, 0.0);
    float deltaTime = 0.016; // Frame time assuming 60 FPS


    //got this fro chatGPT, generating random numbers
    // -----------------------------------------------
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.01, 0.01);
    std::uniform_real_distribution<> angleDis(0, 2 * M_PI); // Full circle
    //------------------------------------------------

    for (auto& other_star : stars) {
        if (this != other_star.get()) {
            glm::vec3 diff = sPosition - other_star->getPosition();
            float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

            if (distance == 0) {
                // Apply a random directional impulse when distance is zero
                float angle = angleDis(gen);
                glm::vec3 randomImpulse(sin(angle) * 0.01, cos(angle) * 0.01, 0);
                tempPosition += randomImpulse;
                continue;
            }

            if (distance < 0.1) {
                float forceMagnitude = (0.1 - distance) / 0.2;
                glm::vec3 diffYz(diff.x, diff.y, 0);

                if (glm::length(diffYz) != 0) {
                    glm::vec3 repulsionForce = glm::normalize(diffYz) * forceMagnitude;
                    // Add a small random component to the direction of the repulsion force
                    glm::vec3 randomComponent(dis(gen)/10, dis(gen)/10, 0);
                    repulsionForce += randomComponent; // Adjust strength of randomness
                    tempPosition += repulsionForce;
                }
            }
        }
    }

    sPosition += tempPosition * deltaTime;
    sOrientation += 0.02;  // Adjust as needed
}


void Star::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const
{
    glm::mat4 projection = pMatrix;
    glm::mat4 view = vMatrix;
    
    Utility::setupShaderForDrawing(shaderProgram, sPosition, sColor, sOrientation, 0.1, 1, projection, view);

    //draw
    auto& meshes = assimpLoader->getMeshes(); // Using getMeshes() method to access the meshes
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(); // Draw each mesh
    }
    //check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
}