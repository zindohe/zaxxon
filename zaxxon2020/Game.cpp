#include "pch.h"
#include "Game.h"
#include "EntityManager.h"
#include "EntityFactory.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
const float Game::EnemiesSpeed = 100.f;

Game::Game() : mainWindow(sf::VideoMode(1200, 800), "ZAXXON 2020 HD", sf::Style::Close)
{
    EntityFactory::loadTextures();

    initSprite();
}
Game::~Game() {
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
}

void Game::update(sf::Time elapsedTime)
{
    for (std::shared_ptr<Entity> entity : EntityManager::entities)
    {
        if (entity->enabled == false)
        {
            continue;
        }
        else if (entity->type == EntityType::EnnemyAlphaHorizontalLeft)
        {
            handleEnemiesMovement(&entity->sprite, elapsedTime, MovementType::VerticalBackAndForth, 1500);
        }
        else if (entity->type == EntityType::EnnemyBetaHorizontalLeft)
        {
            handleEnemiesMovement(&entity->sprite, elapsedTime, MovementType::Circle, 5);
        }
        else if (entity->type == EntityType::EnnemyBoss)
        {
            handleEnemiesMovement(&entity->sprite, elapsedTime, MovementType::HorizontalBackAndForth, 50);
        }

        // entity->sprite.move(movement * elapsedTime.asSeconds());
    }
    Game::entities_angle += 50.f;
}

void Game::handleEnemiesMovement(sf::Sprite* sprite, sf::Time elapsedTime, MovementType movementType, int movementSize) {
   switch (movementType)
    {
    case VerticalBackAndForth:
        verticalBackAndForthMovement(sprite, elapsedTime, movementSize);
        break;
    case HorizontalBackAndForth:
        horizontalBackAndForthMovement(sprite, elapsedTime, movementSize);
        break;
    case Circle:
        circleMovement(sprite, elapsedTime, movementSize);
        break;
    case Zigzag:
        printf("handleEnemiesMovement() : Zigzag movement type not implemented !");
        break;
    default:
        printf("handleEnemiesMovement() : No movement type type provided !");
        break;
    }
}


void Game::verticalBackAndForthMovement(sf::Sprite* sprite, sf::Time elapsedTime, int ennemyFrameSize)
{
    sf::Vector2f movement(0.f, 0.f);

    if (Game::verticalEnemyFramePos == ennemyFrameSize)
        verticalEnemyFramePos = 0;

    if (Game::verticalEnemyFramePos < ennemyFrameSize/2) {
        movement.y -= EnemiesSpeed;
    }
    else if (Game::verticalEnemyFramePos >= ennemyFrameSize/2) {
        movement.y += EnemiesSpeed;
    }
    Game::verticalEnemyFramePos += 1;

    sprite->move(movement * elapsedTime.asSeconds());
}

void Game::horizontalBackAndForthMovement(sf::Sprite* sprite, sf::Time elapsedTime, int ennemyFrameSize)
{
    sf::Vector2f movement(0.f, 0.f);

    if (Game::horizontalEnemyFramePos == ennemyFrameSize)
        horizontalEnemyFramePos = 0;

    if (Game::horizontalEnemyFramePos < ennemyFrameSize / 2) {
        movement.x -= EnemiesSpeed;
    }
    else if (Game::horizontalEnemyFramePos >= ennemyFrameSize / 2) {
        movement.x += EnemiesSpeed;
    }
    Game::horizontalEnemyFramePos += 1;

    sprite->move(movement * elapsedTime.asSeconds());
}

void Game::circleMovement(sf::Sprite* sprite, sf::Time elapsedTime, int circleSize)
{
    // sprite->move(cos(Game::entities_angle) * elapsedTime.asSeconds() * EnemiesSpeed, sin(Game::entities_angle) * elapsedTime.asSeconds() * EnemiesSpeed);
    sprite->move(sf::Vector2f(circleSize * cos(Game::entities_angle), circleSize * sin(Game::entities_angle)));
}

void Game::zigzagMovement(sf::Sprite* sprite, sf::Time elapsedTime, int ennemyFrameSize)
{
}

void Game::initSprite() {
    
    shared_ptr<Entity> background = EntityFactory::createEntity(EntityType::Background, sf::Vector2f(0.f, 0.f), true);

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(100.f, 100.f), true);

    shared_ptr<Entity> laserCyanHorizontal = EntityFactory::createEntity(EntityType::LaserCyanHorizontal,
        sf::Vector2f(200.f, 60.f), true);

    shared_ptr<Entity> laserBlueHorizontal = EntityFactory::createEntity(EntityType::LaserBlueHorizontal,
        sf::Vector2f(200.f, 100.f), true);

    shared_ptr<Entity> laserRedHorizontal = EntityFactory::createEntity(EntityType::LaserRedHorizontal,
        sf::Vector2f(200.f, 140.f), true);




    shared_ptr<Entity> delimiter = EntityFactory::createEntity(EntityType::Delimiter,
        sf::Vector2f(600.f, 0.f), true);


    EntityManager::entities.push_back(background);
    EntityManager::entities.push_back(delimiter);

    EntityManager::entities.push_back(player);

    /*EntityManager::entities.push_back(laserCyanHorizontal);
    EntityManager::entities.push_back(laserBlueHorizontal);
    EntityManager::entities.push_back(laserRedHorizontal);*/



    shared_ptr<Entity> ennemyAlphaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyAlphaHorizontalLeft,
                                                                                sf::Vector2f(800.f, 150.f), true);
    // Ennemies Alpha
    EntityManager::entities.push_back(ennemyAlphaHorizontalLeft);

    for (float y = ennemyAlphaHorizontalLeft->size.y + 170.f; y < 580; y += ennemyAlphaHorizontalLeft->size.y + 20.f)
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
}