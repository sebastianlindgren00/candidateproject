#include "bullets.h"


Bullet::~Bullet() {
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Bullet::update() {
    lifeTime++;
   
    // Update position based on orientation
    //float distToOrigo = glm::distance(glm::vec3(0.0,0.0,0.0), bPosition);
    /*
    if(distToOrigo > boundryX) {
        bPosition.y *= -1;
        bPosition.z *= -1;
    }
*/
    
    bPosition += glm::vec3( cos(bOrientation) * bSpeed,sin(bOrientation) * bSpeed, 0.0);

        if (bPosition.x > 8 || bPosition.x < -8){
        bPosition.x *= -1;
    } else if (bPosition.y > 3 || bPosition.y < -3)
    {
        bPosition.y *= -1;
    }
    
}

void Bullet::draw(const std::unique_ptr<AssimpLoader>& bulletsGreen,const std::unique_ptr<AssimpLoader>& bulletsRed, GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const {

    Utility::setupShaderForDrawingMaterial(shaderProgram, bPosition, bOrientation, 0.05, 0, pMatrix, vMatrix);

    //draw
    if(bTeam == 2){
        auto& meshes = bulletsRed->getMeshes(); // Using getMeshes() method to access the meshes
        for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(); // Draw each mesh
    }}else{

        auto& meshes = bulletsGreen->getMeshes(); // Using getMeshes() method to access the meshes
        for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(); // Draw each mesh
    }

    }
    
   
    //check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
}