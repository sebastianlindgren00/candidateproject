#include "player.h"


int amountOfPlayers;

Player::Player(const int id, const std::string& name){
    amountOfPlayers += 1;

    mIsAlive = true;
    mName = name;
    mPlayerID = id;

    if(amountOfPlayers % 2 == 0) {
        mPlayerColour = {1.f, 0.2f, 0.2f};		// Red
        //mPos = position of red spawn;
        mPosition = glm::vec3(0.0f, 0.0f, -2.0f); // Add default position
    } else {
        mPlayerColour = {0.4f, 1.f, 0.2f};		// Green
        //mPos = position of green spawn;
        mPosition = glm::vec3(0.0f, 0.0f, 2.0f); // Add default position
    }
	


}

Player::~Player()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Player::Player::setPlayerData(const PlayerData& newPlayerData)
{
}

void Player::update(float deltaTime, int turn)
{
  if (!mIsAlive)
		return;  
    float forwardMovement = mSpeed * deltaTime;

    if (turn == 1) { // Assuming 'isKeyPressed' is a function that checks if a key is pressed
        setOrientation(getOrientation() - mTurnSpeed * deltaTime);
    }
    if (turn == 2) {
        setOrientation(getOrientation() + mTurnSpeed * deltaTime);
    }

    // Update position based on orientation
    setPosition(glm::vec3(0.0f, cos(getOrientation()) * forwardMovement, sin(getOrientation()) * -forwardMovement));

}

void Player::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const
{
	if (!mIsAlive)
		return;

    glUseProgram(shaderProgram);
	// frans; Even more color things!
	glUniform3fv(mColLoc, 1, glm::value_ptr(mPlayerColour));

	//glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 500.0f, 0.1f, 100.0f);

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), mPosition);
    modelMatrix = glm::rotate(modelMatrix, mOrientation, glm::vec3(1.0f, 0.0f, 0.0f));


    // Convert glm matrices to OpenGL format and set uniforms
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 viewPos = glm::vec3(5.0f, 0.0f, 3.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor = glm::vec3(mPlayerColour);

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Assuming you want to look at the origin
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f); //
    glm::mat4 viewMatrix = glm::lookAt(viewPos, cameraTarget, upDirection);

    
    // Set the matrices
    // And check so there are no problems
    if (modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        else std::cerr << "Uniform 'model' not found in shader program\n";

    if (viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        else std::cerr << "Uniform 'view' not found in shader program\n";

    if (projectionLoc != -1) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        else std::cerr << "Uniform 'projection' not found in shader program\n";

    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));

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