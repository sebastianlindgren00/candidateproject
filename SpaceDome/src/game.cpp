#include "game.h"

// Sync
std::vector<syncData> Game::fetchSyncData() {
    std::vector<syncData> tmp;
    
    
    for (const auto& player : mPlayers) {
        syncData data;
        data.playerData.mPositionX = player->getPositionX();
        data.playerData.mPositionY = player->getPositionY();
        data.playerData.mPositionZ = player->getPositionZ();
        data.playerData.mOrientation = player->getOrientation();
       
        tmp.push_back(data);
    }
    for (const auto& object : mBGObjects) {
       syncData data;
        data.objectData.bDirection = object->getOrientation();
        data.objectData.bPositionX = object->getPositionX();
        data.objectData.bPositionY = object->getPositionY();
        data.objectData.bPositionZ = object->getPositionZ();
       
        tmp.push_back(data);
    }
    for (const auto& bullet : mBullets) {
        syncData data;
        data.bulletData.bOrientation = bullet->getOrientation();
        data.bulletData.bPositionX = bullet->getPositionX();
        data.bulletData.bPositionY = bullet->getPositionY();
        data.bulletData.bPositionZ = bullet->getPositionZ();
        data.bulletData.bTeam = bullet->getTeam();
        data.bulletData.bID = bullet->getID();
       
        tmp.push_back(data);
    }
    for (const auto& star : mStars) {
        syncData data;
        data.starData.sPositionX = star->getPositionX();
        data.starData.sPositionY = star->getPositionY();
        data.starData.sPositionZ = star->getPositionZ();
        data.starData.sOrientation = star->getOrientation();
        
        tmp.push_back(data);
    }

    syncData data;
    data.gametime = mTotalTime;

    return tmp;
}

void Game::setSyncData(std::vector<syncData> data){
    glm::vec3 pos;
    for(size_t i = 0; i < mPlayers.size(); i++) {
        pos = glm::vec3(data[i].playerData.mPositionX, data[i].playerData.mPositionY, data[i].playerData.mPositionZ);
        mPlayers[i]->setPositionComplete(pos);
        mPlayers[i]->setOrientationComplete(data[i].playerData.mOrientation);
    }

    for (size_t i = 0; i < mBGObjects.size(); i++) {
        pos = glm::vec3(data[i].objectData.bPositionX, data[i].objectData.bPositionY, data[i].objectData.bPositionZ);
        mBGObjects[i]->setOrientation(data[i].objectData.bDirection);
        mBGObjects[i]->setPosition(pos);
    }
    for (size_t i = 0; i < mBullets.size(); i++) {
        pos = glm::vec3(data[i].bulletData.bPositionX, data[i].bulletData.bPositionY, data[i].bulletData.bPositionZ);
        mBullets[i]->setOrientation(data[i].bulletData.bOrientation);
        mBullets[i]->setPosition(pos);
        mBullets[i]->setTeam(data[i].bulletData.bTeam);
        mBullets[i]->setID(data[i].bulletData.bID);
    }

    for (size_t i = 0; i < mStars.size(); i++) {
        pos = glm::vec3(data[i].starData.sPositionX, data[i].starData.sPositionY, data[i].starData.sPositionZ);
        mStars[i]->setPosition(pos);
        mStars[i]->setOrientation(data[i].starData.sOrientation);
    }

   //mTotalTime = data.gametime;

}

void Game::addPlayer(int id, const std::string& name) {
if(mPlayers.size() == allShipsGreen.size() + allShipsRed.size()){
    std::cout << "Cant add this player. The server is full. \n";
    return;
}

    int team = teamRed <= teamGreen ? 1 : 2;
    if (team == 1) {
        teamRed++;
    } else {
        teamGreen++;
    }
    


    //get a unique color
    int colorID = findNextAvailableColorID(team);
    glm::vec3 color = (team == 1) ? redShades[colorID] : greenShades[colorID];

    mPlayers.push_back(std::make_unique<Player>(id, name, team, colorID, color, projectionMatrix, viewMatrix, windowWidth, windowHeight));
    std::cout << "Player: " << name << " joined with ID: " << id << " and color ID: " << colorID << std::endl;
}

//allowing new players to get the lowest available ID
int Game::getLowestAvailablePlayerID() {
    std::set<int> usedIDs;

    // Collect all used IDs
    for (const auto& player : mPlayers) {
        usedIDs.insert(player->getID());
    }

    // Find the lowest unused ID
    int id = 0;
    for (; id < (int)usedIDs.size(); ++id) {
        if (usedIDs.find(id) == usedIDs.end()) {
            break; // Found an unused ID
        }
    }

    return id; // Return the lowest unused ID
}

//function to generate unique colors that players can have
//based on a base color, red == 1 or green == 2, and amount of shades (count)
std::vector<glm::vec3> Game::generateColorShades(glm::vec3 baseColor, int count, int team) {
    std::vector<glm::vec3> shades;
    for (int i = 0; i < count; ++i) {
        float randx = static_cast<float>(rand() % 100) / 300.0f; // Range from 0.0 to 0.5
        float randy = static_cast<float>(rand() % 100) / 300.0f; // Same here

        float factor = static_cast<float>(i) / (count - 1);
        glm::vec3 shade = baseColor * (0.5f + 0.5f * factor); // Vibrant color
        if(team == 1){
        shade += glm::vec3(0.0, randx, randy);
        } else{ //assuming the correct input of teams, 1 or 2 is sent in
        shade += glm::vec3(randx, 0.0, randy);
        }
        shades.push_back(shade);
    }
    return shades;
}

//function to apply a unique color to a player joining the game
//50 different colors/Team
int Game::findNextAvailableColorID(int team) {
    std::vector<bool> usedIDs(50, false);

    for (const auto& player : mPlayers) {
        if (player->getTeam() == team) {
            int colorID = player->getColorID();
            if (colorID < (int)usedIDs.size()) {
                usedIDs[colorID] = true;
            }
        }
    }

    int colorID = std::distance(usedIDs.begin(), std::find(usedIDs.begin(), usedIDs.end(), false));
    return colorID;
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
        if ((*it)->getTeam() == 1) {
            if(id )
            teamRed--;
        } else {
            teamGreen--;
        }
        mPlayers.erase(it);
        std::cout << "Player with ID: " << id << " was removed.\n";
    } else {
        std::cerr << "Player with ID: " << id << " not found.\n";
    }
}

//managing inputs from keyboard, will change when website is connected
void Game::gameKeyboard(sgct::Key key, sgct::Modifier modifier, sgct::Action action, sgct::Window*) {
    (void)modifier;
    if(action == sgct::Action::Press) {
        keyStates[key] = true;
    } else if(action == sgct::Action::Release) {
        keyStates[key] = false;
    }
}

//is a player over a star?
//pick it up
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

//is a player at spawn and holding stars?
//hand them in to the teams total stars
void Game::handInStars(int id){
    glm::vec3 spawn = glm::vec3(-windowHeight/300, 0.0f, -1.5f);
    if(mPlayers[id]->getTeam() == 2){
        spawn = glm::vec3(windowHeight/300, 0.0f, -1.5f);
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


void Game::updateTurnSpeed(unsigned int id, float rotAngle) {
    //is there a player with thid id?
	assert(id < mPlayers.size() && "Player update turn speed desync (id out of bounds mPlayers");
    //update rotation
	mPlayers[id]->setTurnSpeed(rotAngle);
}

glm::mat4 Game::projectionMatrix;
glm::mat4 Game::viewMatrix;
int Game::windowHeight;
int Game::windowWidth;

void Game::update() {
    //First update?	
    if (mLastFrameTime == -1) {
		mLastFrameTime = sgct::time();
	return;
	}

    if(mBGObjects.size() < windowHeight/(size_t)100) {
        mBGObjects.push_back(std::make_unique<BackgroundObject>(zPosBgObjects));
        if(counterForBGObjects == 3)
        {
        zPosBgObjects += -1;
        counterForBGObjects = 0;
        }else 
        counterForBGObjects++;
    }

    //may be wrong not sure yet
    //but something getting time from sgct engine
	float currentFrameTime = sgct::time();

	float deltaTime = currentFrameTime - mLastFrameTime;
	this->mTotalTime = deltaTime;

    for(auto& bgObject : mBGObjects)
        bgObject->update(mBGObjects);

    for (auto& player : mPlayers) {
        if (player->isAlive()) {
            player->setTextPos(Utility::CalculateScreenPositionsPlayers(player->getPosition()* glm::vec3(1,-1,1) - glm::vec3(0,-0.5f,0), projectionMatrix, viewMatrix, windowWidth, windowHeight));
        }
    }
    
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


    if(mPlayers.size() > 1){
    setChargeActive(1, false);
    if(keyStates[sgct::Key::Right]) {
        // Turn right
        updateTurnSpeed(1, -0.03f);
    }
    if(keyStates[sgct::Key::S]) {
        // Turn right
        updateTurnSpeed(0, -0.03f);
    }
    if(keyStates[sgct::Key::Left]) {
        // Turn left
        updateTurnSpeed(1, 0.03f);
    }
    if(keyStates[sgct::Key::A]) {
        // Turn left
        updateTurnSpeed(0, 0.03f);
    }
    if(keyStates[sgct::Key::LeftShift]) {
        // Charge
        setChargeActive(1, true);
    }
    if(keyStates[sgct::Key::L]) {
        // Get id
        
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
    }

    if(starDelayCounter < starDelay){
        starDelayCounter++;
    }

    int totalStars = (int)(25 + 1.5*(teamRed + teamGreen))*(windowHeight/(windowHeight*0.6));
    if((int)mStars.size() < totalStars && starDelayCounter >= starDelay){
        starDelay = (rand() % 50) + 1;
        starDelayCounter = 0;
        mStars.push_back(std::make_unique<Star>(maxStarsID));
        maxStarsID++;
    }

    //remove bullets that have expired - Move to Bullets class instead?
    mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(),
    [](const std::unique_ptr<Bullet>& bullet) -> bool {
        return bullet->getLifeTime() >= 150;
    }), mBullets.end());

    // Commented out 26/03 for testing
    //std::cout << "Red has: " << redTeamStars << " stars\n";
    //std::cout << "Green had: " << greenTeamStars << " stars\n";

    //update the stars
    for (auto& star : mStars)
		star->update(mStars);

    //update the players
    for (auto& player : mPlayers) {
        if(player->getDropStars()){
            for(int j = 0; j < player->getStars(); j ++){
                mStars.push_back(std::make_unique<Star>(player->getPosition(),maxStarsID));
                maxStarsID++;
            }
            player->setPosition(glm::vec3(0.0, 0.0, -10.0));
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


std::vector<std::string> Game::getHiscoreList(const std::vector<std::unique_ptr<Player>>& players) {

    int first = 0, second = 0, third = 0;
    std::vector<std::string> hiscoreList(3);

    for (const auto& player : players) {
        int stars = player->getHandedInStars();
        std::string nameAndStars = player->getName() + " " + std::to_string(stars);

        if (stars >= first) {
            hiscoreList[2] = hiscoreList[1];
            hiscoreList[1] = hiscoreList[0];
            hiscoreList[0] = nameAndStars;
            third = second;
            second = first;
            first = stars;
        } else if (stars >= second) {
            hiscoreList[2] = hiscoreList[1];
            hiscoreList[1] = nameAndStars;
            third = second;
            second = stars;
        } else if (stars >= third) {
            hiscoreList[2] = nameAndStars;
            third = stars;
        }
    }
    return hiscoreList;
}

void Game::getTexts(std::vector<TextItem>& texts){

    float scale = 1.0f;

    std::string textRed = "RED TEAM: " + std::to_string(getStars(1));
    std::string textGreen = "GREEN TEAM: " + std::to_string(getStars(2));

    int timer = getEndTime();
    std::string textTime = "GAME ENDS IN: " + std::to_string(timer);

    if(!isGameActive()){
        int timer = getRestartTime();
        textTime = "NEW GAME STARTS IN: " + std::to_string(timer);

        texts.push_back({ textTime, 7, scale, glm::vec3(0.8f, 0.8f, 0.8f) });

        if(getStars(1) > getStars(2)){
            texts.push_back({ "Red Team Won!", 6, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        } else if(getStars(1) < getStars(2)){
            texts.push_back({ "Green Team Won!", 6, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        } else {
            texts.push_back({ "The Game Ended In A Draw!", 6, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        }

        std::vector<std::string> hiscoreList = getHiscoreList(getPlayers());

        texts.push_back({ textRed, 5, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        texts.push_back({ textGreen, 4, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        texts.push_back({ "Player Hiscore:", 3, scale, glm::vec3(0.8f, 0.8f, 0.8f) });

        if(getPlayers().size() > 0){
            texts.push_back({ hiscoreList[0], 2, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        }
        if(getPlayers().size() > 1){
            texts.push_back({ hiscoreList[1], 1, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        }if(getPlayers().size() > 2){
            texts.push_back({ hiscoreList[2], 0, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
        }

    }else {
    
    texts.push_back({ textTime, 6, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
    texts.push_back({ textRed, 5, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
    texts.push_back({ textGreen, 4, scale, glm::vec3(0.8f, 0.8f, 0.8f) });
    }
}

void Game::renderText(GLuint shaderProgramText,float scale, float width, float height, Utility utilityInstance){

    std::string textRed = "RED TEAM: " + std::to_string(getStars(1));
    std::string textGreen = "GREEN TEAM: " + std::to_string(getStars(2));

    int timer = getEndTime();
    std::string textTime = "GAME ENDS IN: " + std::to_string(timer);

    if(!isGameActive()){
        int timer = getRestartTime();
        textTime = "NEW GAME STARTS IN: " + std::to_string(timer);
        utilityInstance.RenderText(shaderProgramText, textTime, 7, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        if(getStars(1) > getStars(2)){
            utilityInstance.RenderText(shaderProgramText, "Red Team Won!", 6, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        } else if(getStars(1) < getStars(2)){
            utilityInstance.RenderText(shaderProgramText, "Green Team Won!", 6, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        } else {
            utilityInstance.RenderText(shaderProgramText, "The Game Ended In A Draw!", 6, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        }

        std::vector<std::string> hiscoreList = getHiscoreList(getPlayers());

        utilityInstance.RenderText(shaderProgramText, textRed, 5, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        utilityInstance.RenderText(shaderProgramText, textGreen, 4, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        utilityInstance.RenderText(shaderProgramText, "Player Hiscore:", 3, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        if(getPlayers().size() > 0){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[0], 2, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        }
        if(getPlayers().size() > 1){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[1], 1, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        }if(getPlayers().size() > 2){
        utilityInstance.RenderText(shaderProgramText, hiscoreList[2], 0, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
        }
    }else 

    utilityInstance.RenderText(shaderProgramText, textTime, 6, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
    utilityInstance.RenderText(shaderProgramText, textRed, 5, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);
    utilityInstance.RenderText(shaderProgramText, textGreen, 4, scale, glm::vec3(0.8f, 0.8f, 0.8f), width, height);        
}

