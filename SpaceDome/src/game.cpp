#include "game.h"

void Game::addPlayer(int id, const std::string& name) {
    int team = teamRed <= teamGreen ? 1 : 2;
    if (team == 1) {
        teamRed++;
    } else {
        teamGreen++;
    }

    int colorID = findNextAvailableColorID(team);
    glm::vec3 color = (team == 1) ? redShades[colorID] : greenShades[colorID];

    mPlayers.push_back(std::make_unique<Player>(id, name, team, colorID, color));
    std::cout << "Player: " << name << " joined with ID: " << id << " and color ID: " << colorID << std::endl;
}

int Game::getLowestAvailablePlayerID() {
    std::set<int> usedIDs;

    // Collect all used IDs
    for (const auto& player : mPlayers) {
        usedIDs.insert(player->getID());
    }

    // Find the lowest unused ID
    int id = 0;
    for (; id < usedIDs.size(); ++id) {
        if (usedIDs.find(id) == usedIDs.end()) {
            break; // Found an unused ID
        }
    }

    return id; // Return the lowest unused ID
}

std::vector<glm::vec3> Game::generateColorShadesRed(glm::vec3 baseColor, int count) {
    std::vector<glm::vec3> shades;
    for (int i = 0; i < count; ++i) {
        float randx = static_cast<float>(rand() % 100) / 300.0f; // Range from 0.0 to 0.5
        float randy = static_cast<float>(rand() % 100) / 300.0f; // Same here

        float factor = static_cast<float>(i) / (count - 1);
        glm::vec3 shade = baseColor * (0.5f + 0.5f * factor); // Vibrant color
        shade += glm::vec3(0.0, randx, randy);
        shades.push_back(shade);
    }
    return shades;
}

std::vector<glm::vec3> Game::generateColorShadesGreen(glm::vec3 baseColor, int count) {
    std::vector<glm::vec3> shades;
    for (int i = 0; i < count; ++i) {
        float randx = static_cast<float>(rand() % 100) / 200.0f; // Range from 0.0 to 0.5
        float randy = static_cast<float>(rand() % 100) / 200.0f; // Same here

        float factor = static_cast<float>(i) / (count - 1);
        glm::vec3 shade = baseColor * (0.5f + 0.5f * factor); // Vibrant color
        shade += glm::vec3(randx, 0.0, randy);
        shades.push_back(shade);
    }
    return shades;
}


void Game::addBullet(int team, float speed, glm::vec3 position,float orientation, int id){
    mBullets.push_back(std::make_unique<Bullet>(team, speed, position, orientation, id));
}
void Game::shotBullet(int id){
    if(mPlayers[id]->getBulletTimer() == 75){
        addBullet(mPlayers[id]->getTeam(),mPlayers[id]->getSpeed(),mPlayers[id]->getPosition(),mPlayers[id]->getOrientation(), bulletID);
        mPlayers[id]->restoreTimer();
        bulletID++;
    }
}

void Game::removePlayer(int id) {
    if (mPlayers.empty()) {
        std::cerr << "No players to remove.\n";
        return;
    }

    auto it = std::find_if(mPlayers.begin(), mPlayers.end(), [id](const std::unique_ptr<Player>& player) {
        return player->getID() == id;
    });

    if (it != mPlayers.end()) {
        //int team = (*it)->getTeam();
        if ((*it)->getTeam() == 1) {
            if(id )
            teamRed--;
        } else {
            teamGreen--;
        }

        //updateLowestUnusedColorID(team);
        //std::cout << "Red ColorID:" << redColorID << "\n";
        //std::cout << "Green ColorID:" << greenColorID << "\n";
        mPlayers.erase(it);
        std::cout << "Player with ID: " << id << " was removed.\n";
    } else {
        std::cerr << "Player with ID: " << id << " not found.\n";
    }
}

int Game::findNextAvailableColorID(int team) {
    std::vector<bool> usedIDs(50, false); // Assuming 50 is the number of shades

    for (const auto& player : mPlayers) {
        if (player->getTeam() == team) {
            int colorID = player->getColorID();
            if (colorID < usedIDs.size()) {
                usedIDs[colorID] = true;
            }
        }
    }

    int colorID = std::distance(usedIDs.begin(), std::find(usedIDs.begin(), usedIDs.end(), false));
    return colorID;
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
        //int starId = (*it)->getID();
        float distance = glm::distance((*it)->getPosition(), mPlayers[id]->getPosition());
        if (distance <= 0.15) {
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

    if(mBGObjects.size() < 7) {
        mBGObjects.push_back(std::make_unique<BackgroundObject>(xPosBgObjects));
        if(counterForBGObjects == 1)
        {
        xPosBgObjects += -0.5;
        counterForBGObjects = 0;
        }else 
        counterForBGObjects++;
    }

    //may be wrong not sure yet
    //but something getting time from sgct engine
	float currentFrameTime = sgct::time();

	float deltaTime = currentFrameTime - mLastFrameTime;
	this->mTotalTime = deltaTime;

    //std::cout << (int)mTotalTime << "\n";
    for(auto& bgObject : mBGObjects)
        bgObject->update(mBGObjects);
    
    // Max antal stjärnor?  greenTeamStars == 150 || redTeamStars == 150 || 
    if(mTotalTime >= mMaxTime && mGameActive == true){
        mGameActive = false;
        mTotalTime = 0;
        mLastFrameTime = sgct::time();

        if(redTeamStars > greenTeamStars){
            redWins++;
        }else {
            greenWins++;
        }

        for (auto& player : mPlayers) {
            player->setIsAlive(false);
        }
        return;
    }
    if (mTotalTime >= mResetGame && mGameActive == false){
        mGameActive = true;
        mTotalTime = 0;
        mLastFrameTime = sgct::time();
        redTeamStars = 0;
        greenTeamStars = 0;
        maxStarsID = 0;
        bulletID = 0;

    //delete all stars and reset 
    for (auto it = mStars.begin(); it != mStars.end(); ) {
        it = mStars.erase(it); 
    }
    //delete all bullets leftovers from last game
    for(auto it = mBullets.begin(); it != mBullets.end();) {
        it = mBullets.erase(it);
    }

    for (auto& player : mPlayers) {
        player->resetAllStars();
        player->setSpawnTimerFull();
        }
        return;
    }
    if(mGameActive == false){
        return;
    } else

    setChargeActive(1, false);
    if(keyStates[sgct::Key::Right]) {
        // Turn right
        updateTurnSpeed(1, -0.01f);
    }
    if(keyStates[sgct::Key::S]) {
        // Turn right
        updateTurnSpeed(0, -0.01f);
    }
    if(keyStates[sgct::Key::Left]) {
        // Turn left
        updateTurnSpeed(1, 0.01f);
    }
    if(keyStates[sgct::Key::A]) {
        // Turn left
        updateTurnSpeed(0, 0.01f);
    }
    if(keyStates[sgct::Key::LeftShift]) {
        // Charge
        setChargeActive(1, true);
    }
    if(keyStates[sgct::Key::L]) {
        // Shoot
        if(mPlayers[1]->isAlive()){
        shotBullet(1);
        }
    }
    if(keyStates[sgct::Key::D]) {
        // Shoot
        if(mPlayers[0]->isAlive()){
        shotBullet(0);
        }
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

    //std::cout << "Red has: " << redTeamStars << " stars\n";
    //std::cout << "Green had: " << greenTeamStars << " stars\n";
    //std::cout << "numer of stars in the game: " << mStars.size() << "\n";

    //update the stars
    for (auto& star : mStars)
		star->update();

    //update the players
    for (auto& player : mPlayers) {
        if(player->getDropStars()){
            //std::cout << "a player died\n";
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

        //pick up stars
        pickUpStars(player->getID());
        //hand in stars
        handInStars(player->getID());
		//player->update(mBullets);
    }
    //update the bullets
    for (auto& bullet : mBullets)
        bullet->update();
}
