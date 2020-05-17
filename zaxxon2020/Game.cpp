#include "pch.h"
#include "Game.h"
#include "EntityManager.h"
#include "EntityFactory.h"

Game::Game() : mainWindow(sf::VideoMode(840, 600), "ZAXXON 2020 HD", sf::Style::Close)
{
    EntityFactory::loadTextures();

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(300.f, 100.f) , true);

    EntityManager::entities.push_back(player);

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
