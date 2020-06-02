#include "pch.h"
#include "Game.h"

#include "EntityManager.h"
#include "EntityFactory.h"
#include "Action2.h"
#include "HandleManager2.h"

const float Game::PlayerSpeed = 10.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
const float Game::EnemiesSpeed = 100.f;

Game::Game() :  mainWindow(sf::VideoMode(1200, 800), "ZAXXON 2020 HD", sf::Style::Close),
                isUpPressed(false),
                isDownPressed(false),
                isLeftPressed(false),
                isRightPressed(false),
                isSpacePressed(false)
{
    EntityFactory::loadTextures();
    initSprite();
}

Game::~Game() {
}

void Game::initSprite() {

    shared_ptr<Entity> stage1 = EntityFactory::createEntity(EntityType::Stage1, sf::Vector2f(0.f, 0.f), true);
    float pos_x_stage2 = stage1->position.x + stage1->size.x;
    shared_ptr<Entity> stage2 = EntityFactory::createEntity(EntityType::Stage2, sf::Vector2f(pos_x_stage2, 0.f), true);

    EntityManager::entities.push_back(stage1);
    EntityManager::entities.push_back(stage2);

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(100.f, 100.f), true);

    EntityManager::entities.push_back(player);

    HandleManager::EnnemiesStage1(mainWindow.getSize());
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
            handleEnemiesMovement(entity, elapsedTime, MovementType::VerticalBackAndForth, 150);
        }
        else if (entity->type == EntityType::EnnemyBetaHorizontalLeft)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::VerticalBackAndForth, 50);
        }
        else if (entity->type == EntityType::EnnemyBoss)
        {
            handleEnemiesMovement(entity, elapsedTime, MovementType::HorizontalBackAndForth, 50);
        }

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
    HandleManager::HandlePlayerLaserMove(this->mainWindow.getSize().x);

   
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
