#include <string>
//#include <GL/glew.h>
#include "utility.h"
#include "game.h"

class TextRenderer {
public:
    
    TextRenderer(GLuint shaderProgram, float width, float height);
    ~TextRenderer();
    
    void initialize();

    void updateText(Game& game); // Updates the text to be rendered
    void renderTextToTexture(std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers);
    GLuint getTexture() const;

private:

    GLuint shaderProgram;

    GLuint textFramebuffer;
    GLuint textTexture;
    int width;
    int height;
    std::vector<TextItem> currentTextItems;

    void setupFramebuffer();
    void drawText();
};
