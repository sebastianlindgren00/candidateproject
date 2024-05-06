#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include <string>
#include <glm/glm.hpp>

struct TextItem {
    std::string text;
    int row;
    float scale;
    glm::vec3 color;
};

#endif