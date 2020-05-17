#include "pch.h"
#include "Game.h"
#include "EntityManager.h"
#include "EntityFactory.h"

Game::Game() : mainWindow(sf::VideoMode(1200, 800), "ZAXXON 2020 HD", sf::Style::Close)
{
    EntityFactory::loadTextures();

    initSprite();
}
Game::~Game() {
}

void Game::run() {

    while (mainWindow.isOpen())
    {
        
        
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
        }

        render();
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

void Game::initSprite() {
    
    shared_ptr<Entity> background = EntityFactory::createEntity(EntityType::Background, sf::Vector2f(0.f, 0.f), true);

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(100.f, 100.f), true);

    shared_ptr<Entity> laserCyanHorizontal = EntityFactory::createEntity(EntityType::LaserCyanHorizontal,
        sf::Vector2f(200.f, 60.f), true);

    shared_ptr<Entity> laserBlueHorizontal = EntityFactory::createEntity(EntityType::LaserBlueHorizontal,
        sf::Vector2f(200.f, 100.f), true);

    shared_ptr<Entity> laserRedHorizontal = EntityFactory::createEntity(EntityType::LaserRedHorizontal,
        sf::Vector2f(200.f, 140.f), true);


    shared_ptr<Entity> ennemyBoss = EntityFactory::createEntity(EntityType::EnnemyBoss,
        sf::Vector2f(1000.f, 120.f), true);

    shared_ptr<Entity> delimiter = EntityFactory::createEntity(EntityType::Delimiter,
        sf::Vector2f(600.f, 0.f), true);


    EntityManager::entities.push_back(background);
    EntityManager::entities.push_back(delimiter);

    EntityManager::entities.push_back(player);
   
    EntityManager::entities.push_back(ennemyBoss);


    EntityManager::entities.push_back(laserCyanHorizontal);
    EntityManager::entities.push_back(laserBlueHorizontal);
    EntityManager::entities.push_back(laserRedHorizontal);

    shared_ptr<Entity> ennemyAlphaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyAlphaHorizontalLeft,
        sf::Vector2f(900.f, 0.f), true);
    EntityManager::entities.push_back(ennemyAlphaHorizontalLeft);

    //Ennemy Alpha

    for (float y = ennemyAlphaHorizontalLeft->size.y + 20.f; y < 580; y += ennemyAlphaHorizontalLeft->size.y + 20.f)
    {
        cout << "Y : " << y << "Largeur vaisseau : " << ennemyAlphaHorizontalLeft->size.y << endl;
        shared_ptr<Entity> ennemyAlphaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyAlphaHorizontalLeft,
                                                                                    sf::Vector2f(800.f, y), true);
        EntityManager::entities.push_back(ennemyAlphaHorizontalLeft);
    }

    //Ennemy Beta

    shared_ptr<Entity> ennemyBetaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyBetaHorizontalLeft,
                                                                                sf::Vector2f(900.f, 0.f), true);

    EntityManager::entities.push_back(ennemyBetaHorizontalLeft);

    for (float y = ennemyBetaHorizontalLeft->size.y + 20.f; y < 580; y += ennemyBetaHorizontalLeft->size.y + 20.f)
    {
        shared_ptr<Entity> ennemyBetaHorizontalLeft = EntityFactory::createEntity(EntityType::EnnemyBetaHorizontalLeft,
                                                                                    sf::Vector2f(900.f, y), true);
        EntityManager::entities.push_back(ennemyBetaHorizontalLeft);
    }
}