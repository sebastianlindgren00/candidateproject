#include "player.h"

Player::Player(const int id, const std::string& name, int team, int colorID, glm::vec3 color){
    mIsAlive = true;
    mName = name;
    mPlayerID = id;
    mColorID = colorID;
    mPlayerColor = color;
    int randx = rand() %50;
    int randy = rand() %50;
    mOrientation = 0.25 - (float)randx/100;
    if(team == 1) {
        //mPos = position of red spawn;
        mPosition = glm::vec3(0.0f, 0.25f-(float)randx/100, -(fovScale/21)+(float)randy/100); // spawn position
        mTeam = 1;
    } else {
        //mPos = position of green spawn;
        mPosition = glm::vec3(0.0f, 0.25f-(float)randx/100, (fovScale/21)-(float)randy/100); // spawn position
        mTeam = 2;
    }

    textPosition = Utility::CalculateScreenPositionsPlayers( mPosition * glm::vec3(1,-1,1) - glm::vec3(0,-0.5f,0));

}

Player::~Player()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}



int Player::update(const std::vector<std::unique_ptr<Bullet>>& mBullets)
{
    // TODO: Move to Bullet class instead
    if(bulletTimer < shotAvailable){
        bulletTimer++;
    }

    //check if alive, if not, how long untill spawning? spawning at spawn points
    if (!mIsAlive) {
        if(respawnTimer == 500){
            mIsAlive = true;
            respawnTimer = 0;
            int randx = rand() %100;
            int randy = rand() %100;
            mOrientation = 0.5 - (float)randx/100;
            superCharge = 200;
            
            if(mTeam == 1){
                mPosition = glm::vec3(0.0f, 0.25f-(float)randx/100, -(fovScale/21)+(float)randy/100);
            }else 
                mPosition = glm::vec3(0.0f, 0.25f-(float)randx/100, (fovScale/21)-(float)randy/100);
            }
            respawnTimer++;
        return -1; 
    }

    //check if hit by an enemy team bullet, if so temporary disable
    for (const auto& bullet : mBullets) {
        if (bullet->getTeam() != mTeam) {
            glm::vec3 bulletPos = bullet->getPosition();
            float distance = glm::distance(bulletPos, mPosition);

            if (distance <= hitRadius) {
                mIsAlive = false;
                dropStars = true; 
                std::cout << "Player with ID: " << mPlayerID << " Was Eliminated. \n";
                return bullet->getID();
            }
        }
    }
		 
    //handeling super charge, using? empty? filling? full?
    mSpeed = 0.01;

    if(superCharge <= 0){
        chargeActive = false;
        wait = 300;
    }
    if(superCharge < 300 && chargeActive == false && delayForRefill == wait){
        fillSuperCharge();
        delayForRefill = 0;
        wait = (301-superCharge)/10;
    } else if(chargeActive == true){
        mSpeed = 0.02;
        useSuperCharge();
    }
    if(delayForRefill < wait){
        delayForRefill++;
    }
    setOrientation(mTurnSpeed);
    setPosition(glm::vec3(0.0f, cos(getOrientation()) * mSpeed, sin(getOrientation()) * mSpeed));
    //textPosition = Utility::CalculateScreenPositionsPlayers( mPosition * glm::vec3(1,-1,1) - glm::vec3(0,-0.5f,0));


    //so players dont go out of bounds
    if (mPosition.y > boundryX*1.1 || mPosition.y < -boundryX*1.1){
        mPosition.y *= -1;
    } else if (mPosition.z > boundryY*1.2 || mPosition.z < -boundryY*1.2)
    {
        mPosition.z *= -1;
    }
    

    setTurnSpeed(0);
    return -1;
}

void Player::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const
{
	if (!mIsAlive)
		return;

    //setup shaderProgram
    Utility::setupShaderForDrawing(shaderProgram, mPosition, mPlayerColor, mOrientation, playerScale, 0);
    
    //draw
    auto& meshes = assimpLoader->getMeshes();
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(); // Draw each mesh
    }

    //check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
}