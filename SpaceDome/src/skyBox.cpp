#include "SkyBox.h"

void SkyBox::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const {
    
    glUseProgram(shaderProgram);

    // Create transformation matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), sPosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0, 10.0, 10.0)); // Scale the dome to cover the scene

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, assimpLoader->getTextureID()); 

    // Draw the dome object
    auto& meshes = assimpLoader->getMeshes();
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw();
    }

    // Check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
}