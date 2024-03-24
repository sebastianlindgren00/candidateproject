#include "bullets.h"


Bullet::~Bullet()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Bullet::update(float deltaTime)
{
    //dont have to check life here, its checked in game::update
   
    lifeTime++;
    if(lifeTime >= 300){
        return;
    }
    
    // Update position based on orientation
    bPosition += glm::vec3(0.0f, cos(bOrientation) * bSpeed, sin(bOrientation) * bSpeed);

}

void Bullet::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const
{
	if(lifeTime == 100){
        return;
    }

    Utility::setupShaderForDrawing(shaderProgram, bPosition, bColor, bOrientation, 0.05);

   
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