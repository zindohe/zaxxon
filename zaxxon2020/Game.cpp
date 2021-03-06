#include "pch.h"
#include "Game.h"

#include "EntityManager.h"
#include "EntityFactory.h"
#include "Action2.h"
#include "HandleManager2.h"
#include "ScoreRegister.h"
#include "Spawner.h"

const float Game::PlayerSpeed = 10.f;
sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
const float Game::EnemiesSpeed = 100.f;

Game::Game() : mainWindow(sf::VideoMode(1200, 800), "ZAXXON 2020 HD", sf::Style::Close),
                isUpPressed(false),
                isDownPressed(false),
                isLeftPressed(false),
                isRightPressed(false),
                isSpacePressed(false),
                mStatisticsNumFrames(0),
                sansationFont(),
                fpsText(),
                updateTime()
{
    if (sansationFont.loadFromFile("Media/Sansation.ttf")) {
        printf("Font loaded !\n");
    }
    else {
        printf("Failed to load font\n");
    }

    if (!mainMusic.openFromFile("music/main.ogg")) {
        cout << "Error while loading music file" << endl;
    }

    EntityFactory::loadTextures();
    initSprite();
    initSounds();
}

Game::~Game() {
}

void Game::initSprite() {

    gameOver = false;
    isEnnemyFiring = false;
    shared_ptr<Entity> stage1 = EntityFactory::createEntity(EntityType::Stage1, sf::Vector2f(0.f, 0.f), true);
    float pos_x_stage2 = stage1->position.x + stage1->size.x;
    shared_ptr<Entity> stage2 = EntityFactory::createEntity(EntityType::Stage2, sf::Vector2f(pos_x_stage2, 0.f), true);

    EntityManager::entities.push_back(stage1);
    EntityManager::entities.push_back(stage2);

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(50.f, 200.f), true);

    EntityManager::entities.push_back(player);

    HandleManager::EnnemiesStage1(mainWindow.getSize());
    pLives = 3;
    pScore = 0;

    // FPS

    fpsText.setFont(sansationFont);
    fpsText.setCharacterSize(10);
    fpsText.setPosition(5.f, 5.f);
    fpsText.setFillColor(sf::Color::Red);


    // Lives
    playerLivesText.setFillColor(sf::Color::Green);
    playerLivesText.setFont(sansationFont);
    playerLivesText.setPosition(10.f, 750.f);
    playerLivesText.setCharacterSize(20);
    playerLivesText.setString(std::to_string(pLives));


    // Score

    playerScoreText.setFillColor(sf::Color::Green);
    playerScoreText.setFont(sansationFont);
    playerScoreText.setPosition(85.f, 750.f);
    playerScoreText.setCharacterSize(20);
    playerScoreText.setString(std::to_string(pScore));

    // Bonuses Visuals Effects

    shared_ptr<Entity> greenVisual = EntityFactory::createEntity(EntityType::GreenVisualEffect, sf::Vector2f(player->position.x+10.f, player->position.y-5.f), true);
    greenVisual->enabled = false;

    EntityManager::entities.push_back(greenVisual);

}

void Game::initSounds()
{
    mainMusic.play();
    mainMusic.setVolume(50.f);
}


void Game::run() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mainWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();

        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate.asSeconds() > TimePerFrame.asSeconds())
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
            
        }
        updateHandleManagement(elapsedTime);
        render();
    }
}

void Game::processEvents() {

    sf::Event event;
    while (mainWindow.pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerActions(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerActions(event.key.code, false);
                break;
            case sf::Event::Closed:
                mainWindow.close();
                break;
        }
    }
}

void Game::render() {

    mainWindow.clear();

    for (shared_ptr<Entity> entity : EntityManager::entities) 
    {
        if (!entity->enabled)
        {
            continue;
        }

        mainWindow.draw(entity->sprite);
    }

    mainWindow.draw(fpsText);
    mainWindow.draw(playerLivesText);
    mainWindow.draw(playerScoreText);
    mainWindow.draw(gameOverText);
    mainWindow.display();
}

void Game::handlePlayerActions(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Q) {
        mainWindow.close();
    }

    if (key == sf::Keyboard::R) {
        ResetGame();
    }

    if (key == sf::Keyboard::Add) {
        fps++;
    }

    if (key == sf::Keyboard::Subtract) {
        fps--;
    }


    // CHEAT CODES

    if (key == sf::Keyboard::C) { // TODO : remove this cheat code before exam
        pLives++;
        Action::isSuperLaserActive = true;
    }

    // END CHEAT CODES

    if (key == sf::Keyboard::Up)
        isUpPressed = isPressed;
    else if (key == sf::Keyboard::Down)
        isDownPressed = isPressed;
    else if (key == sf::Keyboard::Left)
        isLeftPressed = isPressed;
    else if (key == sf::Keyboard::Right)
        isRightPressed = isPressed;
    else if (key == sf::Keyboard::Space)
    {
        if ( !isPressed) {
            isSpacePressed = false;
        }
        else  if (isPressed && isSpacePressed == false && gameOver == false && !Action::isPlayerFiring){
            isSpacePressed = true;
            Action::PlayerFireLaser();
        }
    }
        
}

void Game::update(sf::Time elapsedTime)
{
    if (gameOver == true)
        return;

    if (EntityManager::entities.at(0)->type == EntityType::Stage9) {
        GameFinished();
        return;
    }

    HandleManager::HandleBackgroundMovement(EntityManager::entities.at(0), mainWindow.getSize());
    HandleManager::HandleBackgroundMovement(EntityManager::entities.at(1), mainWindow.getSize());
    
    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }
        else if (entity->type == EntityType::EnnemyAlphaHorizontalLeft)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::HorizontalBackAndForth, 450);
        }
        else if (entity->type == EntityType::EnnemyBetaHorizontalLeft)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::VerticalBackAndForth, 150);
        }
        else if (entity->type == EntityType::EnnemyBoss)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::HorizontalBackAndForth, 50);
        }
        else if (entity->type == EntityType::EnnemyGamma) {
            handleEnemiesMovement(entity, elapsedTime, MovementType::Circle, 10.f);
        }

    }

    //Game::entities_angle += (5.f * (M_PI/180));
    if (Game::entities_angle > 360.f)
        Game::entities_angle = 0.f;
    Game::entities_angle += 5.f;
    // handle player actions consequences there
    handlePlayerMove();

        
}

void Game::handleEnemiesMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, MovementType movementType, int movementSize) {
   switch (movementType)
    {
    case VerticalBackAndForth:
        verticalBackAndForthMovement(entity, elapsedTime, movementSize);
        break;
    case HorizontalBackAndForth:
        horizontalBackAndForthMovement(entity, elapsedTime, movementSize);
        break;
    case Circle:
        circleMovement(entity, elapsedTime, movementSize);
        break;
    case Zigzag:
        zigzagMovement(entity, elapsedTime, movementSize);
        break;
    default:
        printf("handleEnemiesMovement() : No movement type type provided !");
        break;
    }
}


void Game::verticalBackAndForthMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int ennemyFrameSize)
{
    sf::Vector2f movement(0.f, 0.f);

    if (entity->framePosition >= ennemyFrameSize)
        entity->framePosition = 0;

    if (entity->framePosition < ennemyFrameSize/2) {
        movement.y -= EnemiesSpeed;
    }
    else if (entity->framePosition >= ennemyFrameSize/2) {
        movement.y += EnemiesSpeed;
    }
    entity->framePosition += 1;

    entity->sprite.move(movement * elapsedTime.asSeconds());
}

void Game::horizontalBackAndForthMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int ennemyFrameSize)
{
    sf::Vector2f movement(0.f, 0.f);

    if (entity->framePosition >= ennemyFrameSize)
        entity->framePosition = 0;

    if (entity->framePosition < ennemyFrameSize / 2) {
        movement.x -= EnemiesSpeed;
    }
    else if (entity->framePosition >= ennemyFrameSize / 2) {
        movement.x += EnemiesSpeed;
    }
    entity->framePosition += 1;

    entity->sprite.move(movement * elapsedTime.asSeconds());
}

void Game::circleMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int circleSize)
{
    // entity->sprite.move(cos(Game::entities_angle) * elapsedTime.asSeconds() * EnemiesSpeed, sin(Game::entities_angle) * elapsedTime.asSeconds() * EnemiesSpeed);
    float x_pos = entity->sprite.getPosition().x;
    float y_pos = entity->sprite.getPosition().y;
    entity->sprite.move(sf::Vector2f((circleSize * cos(Game::entities_angle * (PI / 180))),(circleSize * sin(Game::entities_angle * (PI / 180)))));
}

void Game::zigzagMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize)
{
    horizontalBackAndForthMovement(entity, elapsedTime, movementSize);
    Game::horizontalMovesCounter++;
    if (Game::horizontalMovesCounter == 7) {
        verticalBackAndForthMovement(entity, elapsedTime, movementSize);
        Game::horizontalMovesCounter = 0;
    }
}

void Game::updateHandleManagement(sf::Time elapsedTime)
{
    Game::TimePerFrame = sf::seconds(1.f / fps);
    mStatisticsNumFrames += 1;
    updateTime += elapsedTime;
    if (updateTime >= sf::seconds(1.0f))
    {
        float value = (int)(fps * 100 + 0.5);
        fpsText.setString(std::to_string((int)value/100) + " FPS");
    }
    mStatisticsNumFrames = 0;
    HandleManager::HandlePlayerLaserMove(this->mainWindow.getSize().x);

    if (updateTime >= sf::seconds(0.050f))
    {
        if (gameOver == true)
            return;

        HandleTexts();
        HandleGameOver();
        HandleCollisionPlayerEnnemy();
        HandleCollisionPlayerLaserEnnemy();
        HandleEnnemyFiring();
        HandleEnnemyLasersMovement();
        HandleCollisionEnnemyLaserPlayer();
        HandleCollisionPlayerBonus();
        HandleBonusVisualsEffects();
    }
}

void Game::HandleTexts()
{
    std::string lives = "Lives: " + std::to_string(pLives);
    playerLivesText.setString(lives);
    std::string score = "Score: " + std::to_string(pScore);
    playerScoreText.setString(score);
    return;
}

void Game::HandleCollisionPlayerEnnemy()
{
    // Handle collision between the player and a regular ennemy

    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled== false)
        {
            continue;
        }

        if (!EntityManager::isEnnemy(entity))
        {
            continue;
        }

        sf::FloatRect ennemyBound;
        ennemyBound = entity->sprite.getGlobalBounds();

        sf::FloatRect boundPlayer;
        boundPlayer = EntityManager::GetPlayer()->sprite.getGlobalBounds();

        if (ennemyBound.intersects(boundPlayer) == true)
        {
            EntityManager::deleteEntity(entity);
            pLives--;
            break;
        }
    }
}

void Game::HandleCollisionPlayerLaserEnnemy() 
{
    // Handle collision between player's laser and enemies

    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }

        if (!EntityManager::isEnnemy(entity))
        {
            continue;
        }

        sf::FloatRect ennemyBound;
        ennemyBound = entity->sprite.getGlobalBounds();

        std::shared_ptr<Entity> laser = EntityManager::GetPlayerLaser();
        std::shared_ptr<Entity> superLaserDown = EntityManager::GetPlayerSuperLaserDown();
        std::shared_ptr<Entity> superLaserUp = EntityManager::GetPlayerSuperLaserUp();

        if (laser == nullptr || laser->enabled == false)
        {
            return;
        }
        sf::FloatRect boundLaser = laser->sprite.getGlobalBounds();

        if (ennemyBound.intersects(boundLaser) == true)
        {
            entity->health--;
            if (entity->health == 0) {
                if (entity->type == EntityType::EnnemyBoss) {
                    EntityManager::deleteEntity(laser);
                    Spawner::CircleStrategy(EntityType::EnnemyGamma, 8, sf::Vector2f(entity->sprite.getPosition().x, entity->sprite.getPosition().y));
                }
                EntityManager::deleteEntity(entity);
                pScore++;
                break;
            }
            else {
                EntityManager::deleteEntity(laser);
                break;
            }
        }

        if (superLaserDown != nullptr && superLaserDown->enabled == true) {

            sf::FloatRect boundSuperLaserDown = superLaserDown->sprite.getGlobalBounds();
            if (ennemyBound.intersects(boundSuperLaserDown) == true)
            {
                entity->health--;
                if (entity->health == 0) {
                    if (entity->type == EntityType::EnnemyBoss) {
                        EntityManager::deleteEntity(superLaserDown);
                        Spawner::CircleStrategy(EntityType::EnnemyGamma, 8, sf::Vector2f(entity->sprite.getPosition().x, entity->sprite.getPosition().y));
                    }
                    EntityManager::deleteEntity(entity);
                    pScore++;
                    break;
                }
                else {
                    EntityManager::deleteEntity(superLaserDown);
                    break;
                }
            }
        }

        if (superLaserUp != nullptr && superLaserUp->enabled == true) {

            sf::FloatRect boundSuperLaserUp = superLaserUp->sprite.getGlobalBounds();
            if (ennemyBound.intersects(boundSuperLaserUp) == true)
            {
                entity->health--;
                if (entity->health == 0) {
                    if (entity->type == EntityType::EnnemyBoss) {
                        EntityManager::deleteEntity(superLaserUp);
                        Spawner::CircleStrategy(EntityType::EnnemyGamma, 8, sf::Vector2f(entity->sprite.getPosition().x, entity->sprite.getPosition().y));
                    }
                    EntityManager::deleteEntity(entity);
                    pScore++;
                    break;
                }
                else {
                    EntityManager::deleteEntity(superLaserUp);
                    break;
                }
            }
        }
    }
}

void Game::HandleGameOver()
{
    if (pLives <= 0)
    {
        GameOver();
    }
}

void Game::GameOver()
{
    if (pLives <= 0)
    {
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setFont(sansationFont);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition(150.f, 0.f);
        gameOverText.setCharacterSize(50);


        int score_number = 0;
        string message = "\t\t\t\t\tGAME OVER\nHit R to restart or Q to quit the game\n\n\n\t\t\tYour username is ";
        string player_username = ScoreRegister::getRandomUsername();
        ScoreRegister::registerScore(player_username, pScore);

        string results = "\n\t\t\t\t\tScoreboard :\n________________________________\n";
        vector<string> scores = ScoreRegister::readScores();

        for (auto& score : scores)
        {
            results += "||\t\t\t" + score.substr(0, 3) + "\t\t\t\t||\t\t\t\t" + score.substr(4, score.length() - 1) + "\t\t\t||\n";
            score_number++;
            if (score_number > 8) {
                break;
            }
        }

        gameOverText.setString(message + player_username + results);
        gameOver = true;
    }
}

void Game::ResetGame()
{
    gameOver = false;
    gameOverText.setString("");
    EntityManager::deleteAll();
    initSprite();
    render();
}

void Game::GameFinished()
{
    int score_number = 0;
    string message = "Congratulation you finished the game\n\t\t\t\tHit R to restart\n\n\n\t\t\tYour username is ";
    string player_username = ScoreRegister::getRandomUsername();
    ScoreRegister::registerScore(player_username, pScore);

    string results = "\n\t\t\t\t\tScoreboard :\n________________________________\n";
    vector<string> scores = ScoreRegister::readScores();

    for (auto& score : scores)
    {
        results += "||\t\t\t" + score.substr(0, 3) + "\t\t\t\t||\t\t\t\t" + score.substr(4, score.length()-1) + "\t\t\t||\n";
        score_number++;
        if (score_number > 8) {
            break;
        }
    }


    gameOverText.setFillColor(sf::Color::Green);
    gameOverText.setFont(sansationFont);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(200.f, 70.f);
    gameOverText.setCharacterSize(40);

    gameOverText.setString(message + player_username + results);

    gameOver = true;
}

void Game::HandleEnnemyFiring()
{
    //
    // Handle Ennemies firing lasers
    //
    if (isEnnemyFiring == true)
        return;

    std::vector<std::shared_ptr<Entity>>::reverse_iterator rit = EntityManager::entities.rbegin();
    for (; rit != EntityManager::entities.rend(); rit++)
    {
        std::shared_ptr<Entity> entity = *rit;

        if (entity->enabled == false)
        {
            continue;
        }

        if (!EntityManager::isEnnemy(entity))
        {
            continue;
        }

        int r = rand() % 100;
        if (r >= 11)
            continue;

        sf::Vector2f firePos = sf::Vector2f(entity->sprite.getPosition().x-20, entity->sprite.getPosition().y);

        std::shared_ptr<Entity> ennemyFire = EntityFactory::createEntity(EntityType::LaserRedHorizontal, firePos, true);

        EntityManager::entities.push_back(ennemyFire);

        isEnnemyFiring = true;
        break;
    }
}

void Game::HandleEnnemyLasersMovement()
{
    //
    // Handle Ennemies lasers movement
    //
    if (isEnnemyFiring == false)
    {
        return;
    }

    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }

        if (entity->type != EntityType::LaserRedHorizontal)
        {
            continue;
        }

        float x, y;
        x = entity->sprite.getPosition().x;
        y = entity->sprite.getPosition().y;
        x -= 0.5f;

        if (x <= 0)
        {
            EntityManager::deleteEntity(entity);
            //entity->enabled = false;
            isEnnemyFiring = false;
            return;
        }
        else
        {
            entity->sprite.setPosition(x, y);
        }

    }
}

void Game::HandleCollisionEnnemyLaserPlayer()
{
    //
    //  Handle Collisions between ennemies laser and player
    //

    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }

        if (entity->type != EntityType::LaserRedHorizontal)
        {
            continue;
        }

        sf::FloatRect laserBound;
        laserBound = entity->sprite.getGlobalBounds();

        sf::FloatRect boundPlayer;
        boundPlayer = EntityManager::GetPlayer()->sprite.getGlobalBounds();

        if (laserBound.intersects(boundPlayer) == true)
        {
            EntityManager::deleteEntity(entity);
            isEnnemyFiring = false;
            pLives--;
            break;
        }
    }
}

void Game::HandleCollisionPlayerBonus()
{
    //
    //  Handle Collisions between player and the blue bonus
    //

    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }

        if (!EntityManager::isBonus(entity))
        {
            continue;
        }

        sf::FloatRect bonusBound;
        bonusBound = entity->sprite.getGlobalBounds();

        sf::FloatRect boundPlayer;
        boundPlayer = EntityManager::GetPlayer()->sprite.getGlobalBounds();

        if (bonusBound.intersects(boundPlayer) == true)
        {
            EntityManager::deleteEntity(entity);
            switch (entity->type)
            {
            case EntityType::BlueBonus:
                Action::PlayerSpeed = 20.f;
                EntityManager::GetPlayer()->sprite.setColor(sf::Color(0, 245, 245));
                break;
            case EntityType::GreenBonus:
                pLives = 4;
                break;
            case EntityType::YellowBonus:
                Action::isSuperLaserActive = true;
                break;
            default:
                break;
            }
            break;
        }
    }
}

void Game::HandleBonusVisualsEffects()
{
    shared_ptr<Entity> greenVisual = EntityManager::GetEntityByType(EntityType::GreenVisualEffect);
    shared_ptr<Entity> player = EntityManager::GetPlayer();

    if (pLives > 3)
    {
        greenVisual->enabled = true;
        greenVisual->sprite.setPosition(player->sprite.getPosition().x, player->sprite.getPosition().y - 25.f);
    }
    else {
        greenVisual->enabled = false;
    }
}

void Game::handlePlayerMove() {

    if (isUpPressed)
        Action::PlayerUpMove();
    if (isLeftPressed)
        Action::PlayerLeftMove();
    if (isDownPressed)
        Action::PlayerDownMove(mainWindow.getSize().y);
    if (isRightPressed)
        Action::PlayerRightMove(mainWindow.getSize().x);
}
