#include "player.h" 

Player::Player(const int id, const std::string& name, int team, int colorID, glm::vec3 color, glm::mat4 pMatrix, glm::mat4 vMatrix, int width, int height){
    mIsAlive = true;
    mName = name;
    mPlayerID = id;
    mColorID = colorID;
    mPlayerColor = color;
    int randx = rand() %50;
    int randy = rand() %50;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * 3.14);
    float random_angle = dist(gen);

    mOrientation = random_angle;
    if(team == 1) {
        //mPos = position of red spawn;
        mPosition = glm::vec3(-(height/300)+(float)randy/100, 0.25f-(float)randx/100, -1.5); // spawn position
        mTeam = 1;
    } else {
        //mPos = position of green spawn;
        mPosition = glm::vec3((height/300)-(float)randy/100, 0.25f-(float)randx/100, -1.5); // spawn position
        mTeam = 2;
    }

    textPosition = Utility::CalculateScreenPositionsPlayers( mPosition * glm::vec3(1,-1,1) - glm::vec3(0,-0.5f,0), pMatrix, vMatrix, width, height);

}


Player::~Player()
{
	//sgct::Log::Info("Player with name=\"%s\" removed", mName.c_str());
}

void Player::updatePlayerData(playerData& data) {
    if(data.ID != mPlayerID){
        std::cout << "Network ID: " << data.ID << "is trying to connect to the wrong player (" << mName << ") with ID: " << mPlayerID << ".\n";
        return;
    }
    chargeActive = false;
    shotBullet = false;
    if(data.useShot){
        if(bulletTimer >= shotAvailable){
            shotBullet = true;
        }
    }
    
    if(data.useSuperCharge){
        chargeActive = true;
    }
    mTurnSpeed = data.turnSpeed;
}

int Player::update(const std::vector<std::unique_ptr<Bullet>>& mBullets, float height) {
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
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist(0.0f, 2.0f * 3.14);
            float random_angle = dist(gen);
            mOrientation = random_angle;
            superCharge = 200;
            
            if(mTeam == 1){
                mPosition = glm::vec3(-(height/300)+(float)randy/100, 0.25f-(float)randx/100, -1.5);
            }else 
                mPosition = glm::vec3((height/300)+(float)randy/100, 0.25f-(float)randx/100, -1.5);
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
        delay = 300;
    }
    if(superCharge < 300 && chargeActive == false && delayForRefill == delay){
        fillSuperCharge();
        delayForRefill = 0;
        delay = (301-superCharge)/10;
    } else if(chargeActive == true){
        mSpeed = 0.02;
        useSuperCharge();
    }
    if(delayForRefill < delay){
        delayForRefill++;
    }

    setOrientation(mTurnSpeed);
    setPosition(glm::vec3( cos(getOrientation()) * mSpeed,sin(getOrientation()) * mSpeed, 0.0));

    if (mPosition.x > boundryX || mPosition.x < -boundryX){
        mPosition.x *= -1;
    } else if (mPosition.y > boundryY || mPosition.y < -boundryY)
    {
        mPosition.y *= -1;
    }
    

    setTurnSpeed(0);
    return -1;
}

void Player::draw(const std::vector<std::unique_ptr<AssimpLoader>>& modelsRed ,const std::vector<std::unique_ptr<AssimpLoader>>& modelsGreen, const GLuint shaderProgram, glm::mat4 pMatrix, glm::mat4 vMatrix) const {
	if (!mIsAlive)
		return;

    //setup shaderProgram
    Utility::setupShaderForDrawingMaterial(shaderProgram, mPosition, mOrientation, playerScale, 0, pMatrix, vMatrix);
    
    
    //draw
    if(mTeam == 1){
        auto& meshes = modelsRed[mColorID]->getMeshes();
        for (unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i].Draw(); // Draw each mesh
    }} else {
        auto& meshes = modelsGreen[mColorID]->getMeshes();
        for (unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i].Draw(); // Draw each mesh
    }
    }

    //check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after linking shader program: " << err << std::endl;
    }
}