#include "utility.h"


std::tuple<unsigned int, float> Utility::getTurnSpeed(std::istringstream& input)
{
	unsigned int id;
	float rotation;

	input >> id;
	input >> rotation;

	return std::make_tuple(id, rotation);
}
void Utility::setupShaderForDrawing(const GLuint shaderProgram, const glm::vec3& position, const glm::vec3& color, float orientation, float scale) {
    glUseProgram(shaderProgram);

    // Create transformation matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
    modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 500.0f, 0.1f, 100.0f);
    glm::vec3 viewPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 viewMatrix = glm::lookAt(viewPos, cameraTarget, upDirection);

    // Lighting configuration
    glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor = color;

    // Set uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));
}
void Utility::setupShaderForDrawingTexture(const GLuint shaderProgram, const glm::vec3& position, const glm::vec3& color, float orientation, float scale, GLuint textureID) {
    glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    // Create transformation matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
    modelMatrix = glm::rotate(modelMatrix, orientation, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 500.0f, 0.1f, 100.0f);
    glm::vec3 viewPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 viewMatrix = glm::lookAt(viewPos, cameraTarget, upDirection);

    // Lighting configuration
    glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor = color;

    // Set uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));
}


unsigned int Utility::textureFromFile(const char* path, const std::string& directory/* bool gamma*/)
{
	std::filesystem::path filename{ directory + '/' + std::string(path) };

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