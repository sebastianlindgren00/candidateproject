#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <glad/glad.h>
#include "AssimpLoader.h"

class SkyBox {
public:
    //constructor
    SkyBox(glm::vec3 position, int id) : sPosition(position), dId(id) {}

    //destructor
    ~SkyBox() = default;

    void draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const;

private:
    int dId;
    glm::vec3 sPosition;
};