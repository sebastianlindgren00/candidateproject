#include "booster.h"

void Booster::update() {
    float deltaTime = 0.016f; // Frame time assuming 60 FPS

    orientation += 0.2f * deltaTime;
    setOrientation(orientation);


}


void Booster::draw(const std::unique_ptr<AssimpLoader>& shieldModel, const std::unique_ptr<AssimpLoader>& speedBoosterModel, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const{
   
    double scale = type % 2 == 0 ? 0.18 : 0.23;
    Utility::setupShaderForDrawingMaterial(shaderProgram, pos, orientation, scale, 1, pMatrix, vMatrix);
 
     
    //draw
    if(type % 2 == 0){
         auto& meshes = shieldModel->getMeshes();

    for (unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i].Draw(); // Draw each mesh
    }}else {
         auto& meshes = speedBoosterModel->getMeshes();
          for (unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i].Draw(); // Draw each mesh
    }

    }


    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
}