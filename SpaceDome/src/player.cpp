#include "player.h"

Player::Player(const int id, const std::string& name, int team){
    mIsAlive = true;
    mName = name;
    mPlayerID = id;

    if(team == 1) {
        mPlayerColor = {1.f, 0.2f, 0.2f};		// Red
        //mPos = position of red spawn;
        mPosition = glm::vec3(0.0f, 0.0f, -2.0f); // spawn position
        mTeam = 1;
    } else {
        mPlayerColor = {0.4f, 1.f, 0.2f};		// Green
        //mPos = position of green spawn;
        mPosition = glm::vec3(0.0f, 0.0f, 2.0f); // spawn position
        mTeam = 2;
    }
}

Player::~Player()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Player::update(const std::vector<std::unique_ptr<Bullet>>& mBullets)
{

    if(bulletTimer < shotAvailable){
        bulletTimer++;
    }
    //check if alive, if not, how long untill spawning? spawning at spawn points
    if (!mIsAlive) {
        if(respawnTimer == 500){
            mIsAlive = true;
            respawnTimer = 0;
            mOrientation = 0.0f;
            superCharge = 200;
            if(mTeam == 1){
                mPosition = glm::vec3(0.0f, 0.0f, -2.0f);
            }else 
                mPosition = glm::vec3(0.0f, 0.0f, 2.0f);
            }
            respawnTimer++;
        return; 
    }

    //check if hit by an enemy team bullet, if so temporary disable
    for (const auto& bullet : mBullets) {
        if (bullet->getTeam() != mTeam) {
            glm::vec3 bulletPos = bullet->getPosition();
            float distance = glm::distance(bulletPos, mPosition);

            if (distance <= hitRadius) {
                mIsAlive = false;
                dropStars = true; 
                return;
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

        //keep track of superCharge and see if its charging and stars
        //std::cout << "charge: " << superCharge << "\n";
        //std::cout << "delay: " << delayForRefill << "\n";
        //std::cout << "team: " << mTeam << "\n";
        //std::cout << "Holding stars: " << mStarsHolding << "\n";
        //std::cout << "Stars Handed in: " << mStars << "\n";


    setOrientation(mTurnSpeed);
    setPosition(glm::vec3(0.0f, cos(getOrientation()) * mSpeed, sin(getOrientation()) * mSpeed));
    setTurnSpeed(0);
}

void Player::draw(const std::unique_ptr<AssimpLoader>& assimpLoader, const GLuint shaderProgram) const
{
	if (!mIsAlive)
		return;

    //setup shaderProgram
    Utility::setupShaderForDrawing(shaderProgram, mPosition, mPlayerColor, mOrientation, 0.2);
    
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