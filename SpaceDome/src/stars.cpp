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

    Utility::setupShaderForDrawing(shaderProgram, sPosition, sColor, sOrientation, 0.1);

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