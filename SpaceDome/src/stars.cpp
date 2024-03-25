#include "stars.h"

Star::~Star()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Star::update()
{
    // Update position based on orientation
    sOrientation += 0.02;
}

void Star::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const
{

    //Utility::setupShaderForDrawing(shaderProgram, sPosition, sColor, sOrientation, 0.1);
    glUseProgram(shaderProgram);

    // Create transformation matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), sPosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1));
    modelMatrix = glm::rotate(modelMatrix, sOrientation, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 500.0f, 0.1f, 100.0f);
    glm::vec3 viewPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 viewMatrix = glm::lookAt(viewPos, cameraTarget, upDirection);

    // Lighting configuration
    glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor = sColor;

    // Set uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));


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