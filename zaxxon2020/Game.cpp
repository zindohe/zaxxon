#include "pch.h"
#include "Game.h"

#include "EntityManager.h"
#include "EntityFactory.h"
#include "Action2.h"
#include "HandleManager2.h"

const float Game::PlayerSpeed = 10.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
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
        printf("Font loaded !");
    }
    else {
        printf("Failed to load font");
    }

    EntityFactory::loadTextures();
    initSprite();
}

Game::~Game() {
}

void Game::initSprite() {

    shared_ptr<Entity> background = EntityFactory::createEntity(EntityType::Background, sf::Vector2f(0.f, 0.f), true);

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(100.f, 100.f), true);


    shared_ptr<Entity> delimiter = EntityFactory::createEntity(EntityType::Delimiter, sf::Vector2f(600.f, 0.f), true);


    EntityManager::entities.push_back(background);
    EntityManager::entities.push_back(delimiter);

    EntityManager::entities.push_back(player);

    shared_ptr<Entity> ennemyAlphaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyAlphaHorizontalLeft,
        sf::Vector2f(900.f, 0.f), true);
    // Ennemies Alpha
    EntityManager::entities.push_back(ennemyAlphaHorizontalLeft);

    for (float y = ennemyAlphaHorizontalLeft->size.y + 20.f; y < 580; y += ennemyAlphaHorizontalLeft->size.y + 20.f)
    {
        shared_ptr<Entity> ennemyAlphaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyAlphaHorizontalLeft,
            sf::Vector2f(800.f, y), true);
        EntityManager::entities.push_back(ennemyAlphaHorizontalLeft);
    }

    //Ennemies Beta
    shared_ptr<Entity> ennemyBetaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyBetaHorizontalLeft,
        sf::Vector2f(900.f, 0.f), true);
    EntityManager::entities.push_back(ennemyBetaHorizontalLeft);

    for (float y = ennemyBetaHorizontalLeft->size.y + 20.f; y < 580; y += ennemyBetaHorizontalLeft->size.y + 20.f)
    {
        shared_ptr<Entity> ennemyBetaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyBetaHorizontalLeft,
            sf::Vector2f(900.f, y), true);

        EntityManager::entities.push_back(ennemyBetaHorizontalLeft);
    }

    shared_ptr<Entity> ennemyBoss = EntityFactory::createEntity(EntityType::EnnemyBoss,
        //Ennemy Boss
        sf::Vector2f(1000.f, 120.f), true);
    EntityManager::entities.push_back(ennemyBoss);

    pLives = 3;
    pScore = 0;

    // FPS

    fpsText.setFont(sansationFont);
    fpsText.setPosition(5.f, 5.f);
    fpsText.setCharacterSize(10);
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
   
}


void Game::run() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mainWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
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
        printf("q pressed");
        mainWindow.close();
    }

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
        if ( !isPressed ) {
            isSpacePressed = false;
        }
        else  if (isPressed && isSpacePressed == false){
            isSpacePressed = true;
            Action::PlayerFireLaser();
        }
    }
        
}

void Game::update(sf::Time elapsedTime)
{
    if (gameOver == true)
        return;
    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }
        else if (entity->type == EntityType::EnnemyAlphaHorizontalLeft)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::HorizontalBackAndForth, 950);
        }
        else if (entity->type == EntityType::EnnemyBetaHorizontalLeft)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::Circle, 5);
        }
        else if (entity->type == EntityType::EnnemyBoss)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::HorizontalBackAndForth, 50);
        }

        // entity->sprite.move(movement * elapsedTime.asSeconds());
    }
    Game::entities_angle += 50.f;
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
    entity->sprite.move(sf::Vector2f(circleSize * cos(Game::entities_angle), circleSize * sin(Game::entities_angle)));
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
    mStatisticsNumFrames += 1;
    updateTime += elapsedTime;
    if (updateTime >= sf::seconds(1.0f))
    {
        fpsText.setString(std::to_string(mStatisticsNumFrames) + " FPS");
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
        /*HandleGameOver();
        HandleCollisionWeaponEnemy();
        HandleCollisionWeaponPlayer();
        HandleCollisionWeaponBlock();
        HandleCollisionEnemyWeaponBlock();
        HandleCollisionEnemyMasterWeaponBlock();
        HandleCollisionEnemyMasterWeaponPlayer();
        HandleCollisionBlockEnemy();
        HandleCollisionWeaponEnemyMaster();
        HanldeWeaponMoves();
        HanldeEnemyWeaponMoves();
        HanldeEnemyMasterWeaponMoves();
        HandleEnemyMoves();
        HandleEnemyMasterMove();
        HandleEnemyWeaponFiring();
        HandleEnemyMasterWeaponFiring();*/
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
            //break;
            goto end;
        }
    }

end:
    //nop
    return;
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
        if (laser == nullptr || laser->enabled == false)
        {
            return;
        }
        sf::FloatRect boundLaser = laser->sprite.getGlobalBounds();

        if (ennemyBound.intersects(boundLaser) == true)
        {
            EntityManager::deleteEntity(entity);
            pScore++;
            //break;
            goto end;
        }
    }

end:
    //nop
    return;
}

void Game::HandleGameOver()
{
   if (EntityManager::GetPlayer()->enabled == false)
    {
        GameOver();
    }

    if (pLives == 0)
    {
        GameOver();
    }
}

void Game::GameOver()
{
    if (pLives == 0)
    {
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setFont(sansationFont);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition(350.f, 350.f);
        gameOverText.setCharacterSize(80);

        gameOverText.setString("GAME OVER");

        gameOver = true;
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