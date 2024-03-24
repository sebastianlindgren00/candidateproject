#include "game.h"

void Game::addPlayer(int id, const std::string& name) {
    mPlayers.push_back(std::make_unique<Player>(id, name));
std::cout << "Player: " << name << " joined with ID: " << id << std::endl;
}
void Game::addBullet(int team, float speed, glm::vec3 position,float orientation){
    mBullets.push_back(std::make_unique<Bullet>(team, speed, position, orientation));
}
void Game::shotBullet(int id){
    addBullet(mPlayers[id]->getTeam(),mPlayers[id]->getSpeed(),mPlayers[id]->getPosition(),mPlayers[id]->getOrientation());
}

void Game::removePlayer(int id) {
    auto it = std::remove_if(mPlayers.begin(), mPlayers.end(), [id](const std::unique_ptr<Player>& player) 
    {
    return player->getID() == id;
    });

    mPlayers.erase(it, mPlayers.end());
    std::cout << "Player with ID: " << id << " was removed.\n";
}
void Game::updateTurnSpeed(unsigned int id, float rotAngle)
{
	assert(id < mPlayers.size() && "Player update turn speed desync (id out of bounds mPlayers");

	mPlayers[id]->setTurnSpeed(rotAngle);
}


void Game::update(){
    //First update?	
    if (mLastFrameTime == -1) {
			mLastFrameTime = sgct::time();
		return;
		}

    //ger current time 
    //may be wrong not sure yet
	float currentFrameTime = sgct::time();

	float deltaTime = currentFrameTime - mLastFrameTime;
	this->mTotalTime += deltaTime;

    mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(),
    [](const std::unique_ptr<Bullet>& bullet) -> bool {
        return bullet->getLifeTime() >= 150;
    }), mBullets.end());

    for (auto& player : mPlayers)
		player->update(deltaTime, mBullets);


    for (auto& bullet : mBullets)
        bullet->update(deltaTime);

}
