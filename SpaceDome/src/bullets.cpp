#include "bullets.h"


Bullet::~Bullet() {
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Bullet::update() {
    lifeTime++;
   
    // Update position based on orientation
    float distToOrigo = glm::distance(glm::vec3(0.0,0.0,0.0), bPosition);
    if(distToOrigo > boundryX) {
        bPosition.y *= -1;
        bPosition.z *= -1;
    }

    
    bPosition += glm::vec3(0.0f, cos(bOrientation) * bSpeed, sin(bOrientation) * bSpeed);
/*
        if (bPosition.y > boundryX || bPosition.y < -boundryX){
        bPosition.y *= -1;
    } else if (bPosition.z > boundryY || bPosition.z < -boundryY)
    {
        bPosition.z *= -1;
    }
    */
}

void Bullet::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const {
    Utility::setupShaderForDrawing(shaderProgram, bPosition, bColor, bOrientation, 0.05, 0);

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