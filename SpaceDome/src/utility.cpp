#include "utility.h"
#include <ft2build.h>
#include FT_FREETYPE_H

//declaring a text character
struct Character {
    GLuint     TextureID;  // Texture ID
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

GLuint Utility::planeVAO = 0;
GLuint Utility::planeVBO = 0;
GLuint Utility::planeEBO = 0;
bool Utility::planeInitialized = false;

std::map<GLchar, Character> Characters;

void Utility::setupShaderForDrawingMaterial(const GLuint shaderProgram, const glm::vec3& position, float orientation, float scale, int rotAxis, glm::mat4 pMatrix, glm::mat4 vMatrix) {
    glUseProgram(shaderProgram);

    // Create transformation matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));

        float pi = 3.14;
        modelMatrix = glm::rotate(modelMatrix, -pi/2 , glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, -pi/2 , glm::vec3(1.0f, 0.0f, 0.0f));

    if(rotAxis == 0){
        modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(1.0f, 0.0f, 0.0f));
    } else if(rotAxis == 1){
        modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(0.0f, 0.0f, 1.0f));
    } else {
        modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(1.0f, 1.0f, 1.0f));
    }

    // Set model, view, projection matrices uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glm::mat4 projectionMatrix = pMatrix;
    glm::mat4 viewMatrix = vMatrix;

    // Lighting configuration
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    // Lighting configuration (if it's static, you can set these in initialization)
    glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Utility::setupShaderForDrawing(const GLuint shaderProgram, const glm::vec3& position, const glm::vec3& color, float orientation, float scale, int rotAxis, glm::mat4 pMatrix, glm::mat4 vMatrix) {
    glUseProgram(shaderProgram);

    // Create transformation matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
    
    if(rotAxis == 0){
        modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(1.0f, 0.0f, 0.0f));
    } else if(rotAxis == 1){
        modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
    } else {
        modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    glm::mat4 projectionMatrix = pMatrix;
    glm::mat4 viewMatrix = vMatrix;

    // Lighting configuration
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor = color;

    // Set uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));
}

//fixing paths for both mac and PC
std::string normalizePath(const std::string& path) {
    std::string normalizedPath = path;
    std::replace(normalizedPath.begin(), normalizedPath.end(), '\\', '/');
    return normalizedPath;
}

unsigned int Utility::textureFromFile(const char* path, const std::string& directory/* bool gamma*/)
{
	std::filesystem::path filename{ normalizePath(directory + "/" + std::string(path)) };

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.string().c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGBA;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Utility::LoadFontAtlas(const std::string& fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48); // Set size to load glyphs as

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    // Load first 128 characters of ASCII set
    for (unsigned char c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // Cleanup FreeType once you're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

float Utility::scale = 0.7f;

//initialise positions and matrixes for rendering text
const glm::vec3 Utility::worldPositions[8] = {
    glm::vec3(0, 2.5f *scale, 0),
    glm::vec3(0, 2.0f *scale, 0),
    glm::vec3(0, 1.5f *scale, 0),
    glm::vec3(0, 1.0f *scale, 0),
    glm::vec3(0, 0.0f, 0),
    glm::vec3(0, -0.5f *scale, 0),
    glm::vec3(0, -1.0f *scale, 0),
    glm::vec3(0, -2.0f *scale, 0)
};
glm::vec2 Utility::screenPositions[8];

void Utility::setupPlane() {
    // Check if already initialized
    if (planeInitialized) {
        return; // Skip setup if already initialized
    }

    std::vector<float> planeVertices = {
        -5.7f, -2.7f, -1.6f,  0.0f, 0.0f,
         5.7f, -2.7f, -1.6f,  1.0f, 0.0f,
         5.7f,  2.7f, -1.6f,  1.0f, 1.0f,
        -5.7f,  2.7f, -1.6f,  0.0f, 1.0f
    };

    std::vector<unsigned int> planeIndices = {0, 1, 2, 2, 3, 0};

    // Create and bind the VAO
    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);

    // Create and bind the VBO
    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), planeVertices.data(), GL_STATIC_DRAW);

    // Create and bind the EBO
    glGenBuffers(1, &planeEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, planeIndices.size() * sizeof(unsigned int), planeIndices.data(), GL_STATIC_DRAW);

    // Define vertex attributes (positions and texture coordinates)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO to avoid accidental modifications
    glBindVertexArray(0);

    planeInitialized = true; // Mark as initialized
}

void Utility::renderPlane(GLuint shaderProgram, GLuint texture, const glm::mat4& projection, const glm::mat4& view) {

    // Use the given shader program
    glUseProgram(shaderProgram);

    // Bind the plane VAO
    glBindVertexArray(planeVAO);

    // Create a model matrix with translation in the y-axis (moving up by 3 units)
    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Move up by 3 units

    // Combine the model matrix with the view matrix
    //glm::mat4 modelView = view * model;

    // Set the texture uniform if a texture is provided
    if (texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        GLint texLocation = glGetUniformLocation(shaderProgram, "text");
        if (texLocation != -1) {
            glUniform1i(texLocation, 0);
        } else {
            std::cerr << "Failed to find sampler uniform 'text' in shader program!" << std::endl;
        }
    }

    // Set the projection and view matrix uniforms
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    //std::cout << "Projection Matrix Location: " << projLoc << std::endl;
    GLint modelViewLoc = glGetUniformLocation(shaderProgram, "modelView");
    //std::cout << "ModelView Matrix Location: " << modelViewLoc << std::endl;

    if (projLoc != -1) {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
    if (modelViewLoc != -1) {
        glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }

    // Draw the plane (6 indices for two triangles)
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind VAO and texture after drawing
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Utility::setupText() {
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec2 Utility::CalculateScreenPositionsPlayers(glm::vec3 playerpos, glm::mat4 pMatrix, glm::mat4 vMatrix, float width, float height) {
    glm::vec4 clipSpacePos = pMatrix * vMatrix * glm::vec4(playerpos, 1.0);
    glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos) / clipSpacePos.w;
    return glm::vec2((ndcSpacePos.x + 1.0f) / 2.0f * width, (1.1f - ndcSpacePos.y) / 2.0f * height);
}

void Utility::CalculateScreenPositions(glm::mat4 pMatrix, glm::mat4 vMatrix, float width, float height) {
    
    for(size_t i = 0; i < 8; i++){
    glm::vec4 clipSpacePos = pMatrix * vMatrix * glm::vec4(worldPositions[i], 1.0f);
    glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos) / clipSpacePos.w;
    screenPositions[i].x = (ndcSpacePos.x + 1.0f) / 2.0f * (float)width;
    screenPositions[i].y = (1.0f - ndcSpacePos.y) / 2.5f * (float)height;
     }
}

void Utility::RenderSingleText(GLuint shaderProgram, const std::string& text, float x, float y, float scale, const glm::vec3& color) {
    float textWidth = 0;
    for (auto c : text) {
        if (Characters.find(c) == Characters.end()) continue; // Character not found
        Character ch = Characters[c];
        textWidth += (ch.Advance >> 6) * scale;
    }

    x -= textWidth / 2; // Center text horizontally

    glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);

    // Iterate over each character
    for (auto c : text) {
        if (Characters.find(c) == Characters.end()) continue; // Character not found
        Character ch = Characters[c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 }, // Top left
            { xpos,     ypos,       0.0, 1.0 }, // Bottom left
            { xpos + w, ypos,       1.0, 1.0 }, // Bottom right
            { xpos,     ypos + h,   0.0, 0.0 }, // Top left
            { xpos + w, ypos,       1.0, 1.0 }, // Bottom right
            { xpos + w, ypos + h,   1.0, 0.0 }  // Top right
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Update content of VBO memory

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (advance is typically in 1/64 pixels)
    }
}

void Utility::RenderText(GLuint shaderProgram, std::string text, int row, float scale, glm::vec3 color,  float width, float height) {
    // CalculateScreenPositions must have been called beforehand to populate screenPositions
    float x = Utility::screenPositions[row].x; 
	float y = Utility::screenPositions[row].y;

    // Prepare text rendering once
    glUseProgram(shaderProgram);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);
    glUniform1i(glGetUniformLocation(shaderProgram, "text"), 0);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    RenderSingleText(shaderProgram, text, x, y, scale, color); // Optimized function for rendering a single text element
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void Utility::RenderTextPlayers(GLuint shaderProgram, const std::vector<std::tuple<std::string, float, float, float, glm::vec3>>& texts, int width, int height) {
    GLint prevVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVAO);

    GLint prevProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prevProgram);
  
    glUseProgram(shaderProgram);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    for (const auto& [text, x, y, scale, color] : texts) {
        RenderSingleText(shaderProgram, text, x, y, scale, color); // Optimized function for rendering a single text element
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);

    glBindVertexArray(prevVAO);

    glUseProgram(prevProgram);
}

GLuint Utility::compileShader(GLenum type, const char* source) {
    GLint success;
    GLchar infoLog[512];

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compile errors...
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
}
    return shader;
}

GLuint Utility::createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLint success;
    GLchar infoLog[512];
    
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors...
    glGetProgramiv(program, GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
