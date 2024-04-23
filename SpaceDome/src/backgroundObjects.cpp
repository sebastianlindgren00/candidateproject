#include "backgroundObjects.h"

BackgroundObject::~BackgroundObject()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void BackgroundObject::update(std::vector<std::unique_ptr<BackgroundObject>>& mBGObjects)
{
    for (const auto& object : mBGObjects) {

        if (this != object.get() && this->bPosition.x == object->bPosition.x) {
            glm::vec3 objectPos = object->getPosition();
            float distance = glm::distance(objectPos, bPosition);
            if (distance <= 0.9 + bPosition.x/20) {
                float speed1 = bSpeed;
                float speed2 = object->getSpeed();

                float direction1 = bDirection;
                float direction2 = object->getOrientation();

                bDirection = direction2;
                object->setOrientation(direction1);

                bSpeed = speed2;
                object->setSpeed(speed1);
            }
        }
    }
    
    
    // Update position based on orientation
    bOrientation += bOrientationSpeed;
    setPosition(glm::vec3(0.0, cos(bDirection) * bSpeed, sin(bDirection) * bSpeed));


    float distToOrigo = glm::distance(glm::vec3(0.0,0.0,0.0), bPosition);
    if(distToOrigo > boundryX*4) {
        bPosition.y *= -1;
        bPosition.z *= -1;
    }

/*
    //So background Objects dont go out of bounds
    int random = rand() % 10;
    if (bPosition.y > boundryX*2 || bPosition.y < -boundryX*2){
        bPosition.y *= -1;
        bOrientation = (float)random;
    } else if (bPosition.z > boundryY*2 || bPosition.z < -boundryY*2)
    {
        bPosition.z *= -1;
        bOrientation = (float)random;
    }
    */
}

void BackgroundObject::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const {
    Utility::setupShaderForDrawing(shaderProgram, bPosition, bColor, bOrientation, size, axis);

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