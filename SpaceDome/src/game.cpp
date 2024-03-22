#include "game.h"

void Game::addPlayer(int id, const std::string& name) {
    mPlayers.push_back(std::make_unique<Player>(id, name));
std::cout << "Player: " << name << " joined with ID: " << id << std::endl;
}

void Game::removePlayer(int id) {
    auto it = std::remove_if(mPlayers.begin(), mPlayers.end(), [id](const std::unique_ptr<Player>& player) 
    {
    return player->getID() == id;
    });

    mPlayers.erase(it, mPlayers.end());
    std::cout << "Player with ID: " << id << " was removed.\n";
}
void Game::updateTurnSpeed(std::tuple<unsigned int, float>&& input)
{
	unsigned id = std::get<0>(input);
	float rotAngle = std::get<1>(input);

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

    for (auto& player : mPlayers)
		player->update(deltaTime);

}
