#include "text.h"

TextRenderer::TextRenderer(GLuint shaderProgram, int width, int height)
    : shaderProgram(shaderProgram), width(width), height(height) {
    setupFramebuffer();
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after TextRenderer initialization: " << err << std::endl;
    }
}

TextRenderer::~TextRenderer() {
    glDeleteTextures(1, &textTexture);
    glDeleteFramebuffers(1, &textFramebuffer);
}

void TextRenderer::updateText(Game& game) {
    currentTextItems.clear();
    game.getTexts(currentTextItems);
}

void TextRenderer::initialize() {
    setupFramebuffer();
}

void TextRenderer::setupFramebuffer() {
    // Save the current viewport dimensions
    GLint prevViewport[4];
    glGetIntegerv(GL_VIEWPORT, prevViewport);

    GLint prevVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVAO);

    GLint prevProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prevProgram);

    GLint previousFramebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);

    // Set up the framebuffer
    glGenFramebuffers(1, &textFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, textFramebuffer);
    
    glGenTextures(1, &textTexture);
    glBindTexture(GL_TEXTURE_2D, textTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textTexture, 0);
    
    GLenum framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! Status: " << framebufferStatus << std::endl;
    }

    // Set the viewport to the size of the text framebuffer
    glViewport(0, 0, width, height);

    // Clear the framebuffer with a transparent background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Restore the previous framebuffer and viewport
    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);
    glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);

    glBindVertexArray(prevVAO);

    glUseProgram(prevProgram);

    // Reset OpenGL states explicitly
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    // Check for any errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after setting up framebuffer: " << err << std::endl;
    }
}


void TextRenderer::drawText() {
    for (const auto& item : currentTextItems) {
        Utility::getInstance().RenderText(shaderProgram, item.text, item.row, item.scale, item.color, width, height);
    }
}

void TextRenderer::renderTextToTexture(std::vector<std::tuple<std::string, float, float, float, glm::vec3>> printsPlayers) {

    //store prev framebuffer
    GLint prevViewport[4];
    glGetIntegerv(GL_VIEWPORT, prevViewport);

    GLint previousFramebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);


    glBindFramebuffer(GL_FRAMEBUFFER, textFramebuffer);
    glViewport(0, 0, width, height);

    // Set the clear color to transparent
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawText(); // Render the updated text

    Utility::getInstance().RenderTextPlayers(shaderProgram, printsPlayers, width, height);

    // Restore the previous framebuffer and viewport
    glViewport(0, 0, width, height);

    // Restore the previous framebuffer and viewport
    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);
    glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);

    // Reset states explicitly to avoid any side effects
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

GLuint TextRenderer::getTexture() const {
    return textTexture;
}
