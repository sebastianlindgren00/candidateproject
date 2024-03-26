#include "game.h"

void Game::addPlayer(int id, const std::string& name) {
    int team = 2;
    amountOfPlayers++;
    if(teamRed <= teamGreen){
        team = 1;
        teamRed++;
    }else {
        teamGreen++;
    }

    mPlayers.push_back(std::make_unique<Player>(id, name, team));
std::cout << "Player: " << name << " joined with ID: " << id << std::endl;
}
void Game::addBullet(int team, float speed, glm::vec3 position,float orientation){
    mBullets.push_back(std::make_unique<Bullet>(team, speed, position, orientation));
}
void Game::shotBullet(int id){
    if(mPlayers[id]->getBulletTimer() == 10){
        addBullet(mPlayers[id]->getTeam(),mPlayers[id]->getSpeed(),mPlayers[id]->getPosition(),mPlayers[id]->getOrientation());
        mPlayers[id]->restoreTimer();
    }else 
    mPlayers[id]->increaseTimer();
}

void Game::removePlayer(int id) {
    amountOfPlayers--;
    if(mPlayers[id]->getTeam() == 1){
        teamRed--;
    } else {
        teamGreen--;
    }

    auto it = std::remove_if(mPlayers.begin(), mPlayers.end(), [id](const std::unique_ptr<Player>& player) 
    {
    return player->getID() == id;
    });

    mPlayers.erase(it, mPlayers.end());
    std::cout << "Player with ID: " << id << " was removed.\n";
}

void Game::gameKeyboard(sgct::Key key, sgct::Modifier modifier, sgct::Action action, sgct::Window*) {
    if(action == sgct::Action::Press) {
        keyStates[key] = true;
    } else if(action == sgct::Action::Release) {
        keyStates[key] = false;
    }
}

void Game::pickUpStars(int id){
    for (auto it = mStars.begin(); it != mStars.end(); ) {
        int starId = (*it)->getID();
        float distance = glm::distance((*it)->getPosition(), mPlayers[id]->getPosition());
        if (distance <= 0.1) {
            mPlayers[id]->addStarHolding();
            it = mStars.erase(it); // Erase star and move iterator to next element
        } else {
            ++it; // Move to the next element
        }
    }
}

void Game::handInStars(int id){
    glm::vec3 spawn = glm::vec3(0.0f, 0.0f, -2.0f);
    if(mPlayers[id]->getTeam() == 2){
        spawn = glm::vec3(0.0f, 0.0f, 2.0f);
    }
    float distance = glm::distance(spawn, mPlayers[id]->getPosition());

    if (mPlayers[id]->hasStars() && distance <= handInRadius) {
        int stars = mPlayers[id]->getStars();
        mPlayers[id]->addHandedInStars(mPlayers[id]->getStars());
        mPlayers[id]->nullStars();

    if(mPlayers[id]->getTeam() == 1){
        redTeamStars += stars;
    }else {
        greenTeamStars += stars;
         }
    }
}


void Game::updateTurnSpeed(unsigned int id, float rotAngle)
{
    //is there a player with thid id?
	assert(id < mPlayers.size() && "Player update turn speed desync (id out of bounds mPlayers");
    //update rotation
	mPlayers[id]->setTurnSpeed(rotAngle);
}


void Game::update(){
    //First update?	
    if (mLastFrameTime == -1) {
			mLastFrameTime = sgct::time();
		return;
		}

    //may be wrong not sure yet
    //but something getting time from sgct engine
	float currentFrameTime = sgct::time();

	float deltaTime = currentFrameTime - mLastFrameTime;
	this->mTotalTime += deltaTime;

    setChargeActive(1, false);
    if(keyStates[sgct::Key::Right]) {
        // Turn right
        updateTurnSpeed(1, -0.01f);
    }
    if(keyStates[sgct::Key::L]) {
        // Turn right
        updateTurnSpeed(0, -0.01f);
    }
    if(keyStates[sgct::Key::Left]) {
        // Turn left
        updateTurnSpeed(1, 0.01f);
    }
    if(keyStates[sgct::Key::LeftShift]) {
        // Charge
        setChargeActive(1, true);
    }
    if(keyStates[sgct::Key::S]) {
        // Shoot
        shotBullet(1);
    }
    if(keyStates[sgct::Key::K]) {
        // Shoot
        shotBullet(0);
    }

    if(starDelayCounter < starDelay){
        starDelayCounter++;
    }
    if(mStars.size() < 25 && starDelayCounter >= starDelay){
        starDelay = (rand() % 100) + 1;
        starDelayCounter = 0;
        mStars.push_back(std::make_unique<Star>(maxStarsID));
        maxStarsID++;
    }


    //remove bullets that have expired
    mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(),
    [](const std::unique_ptr<Bullet>& bullet) -> bool {
        return bullet->getLifeTime() >= 150;
    }), mBullets.end());


    //pick up stars
    pickUpStars(0);
    pickUpStars(1);


    //hand in stars
    handInStars(0);
    handInStars(1);

    std::cout << "Red has: " << redTeamStars << " stars\n";
    std::cout << "Green had: " << greenTeamStars << " stars\n";
    std::cout << "numer of stars in the game: " << mStars.size() << "\n";

    //update the stars
    for (auto& star : mStars)
		star->update();

    //update the players
    for (auto& player : mPlayers) {
        if(player->getDropStars()){
            std::cout << "a player died\n";
            glm::vec3 dropPosition = player->getPosition();
            glm::vec3 newpos;
            player->setPosition(glm::vec3(-10.0, 0.0, 0.0));
            for(int j = 0; j < player->getStars(); j ++){
                int random = rand() % 10;
                newpos = dropPosition + glm::vec3(0.0, 0.05-(float)random/10, 0.05-(float)random/10);
                mStars.push_back(std::make_unique<Star>(newpos,maxStarsID));
                maxStarsID++;
            }
            player->nullStars();
            player->setDropStars();
        }
		player->update(mBullets);
}
    //update the bullets
    for (auto& bullet : mBullets)
        bullet->update();
}
