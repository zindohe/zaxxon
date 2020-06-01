#include "pch.h"
#include "Game.h"

#include "EntityManager.h"
#include "EntityFactory.h"
#include "Action2.h"
#include "HandleManager2.h"

const float Game::PlayerSpeed = 10.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :  mainWindow(sf::VideoMode(1200, 800), "ZAXXON 2020 HD", sf::Style::Close),
                isUpPressed(false),
                isDownPressed(false),
                isLeftPressed(false),
                isRightPressed(false),
                isSpacePressed(false),
                updateTime()
{
    EntityFactory::loadTextures();
    initSprite();
}

Game::~Game() {
}

void Game::initSprite() {

    shared_ptr<Entity> background = EntityFactory::createEntity(EntityType::Background, sf::Vector2f(0.f, 0.f), true);

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(100.f, 100.f), true);


    shared_ptr<Entity> delimiter = EntityFactory::createEntity(EntityType::Delimiter,
        sf::Vector2f(600.f, 0.f), true);


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
        if ( isPressed == false || isSpacePressed == true)
        {
            isSpacePressed = false;
            return;
        }
        isSpacePressed = isPressed;
        Action::PlayerFireLaser();
    }
        
}

void Game::update(sf::Time elapsedTime)
{
    // handle player actions consequences there
    handlePlayerMove();
        
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


void Game::updateHandleManagement(sf::Time elapsedTime)
{
    updateTime += elapsedTime;
    if (updateTime >= sf::seconds(1.0f))
    {
        
    }
    HandleManager::HandlePlayerLaserMove(this->mainWindow.getSize().x);
   
}