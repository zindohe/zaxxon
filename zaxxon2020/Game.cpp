#include "pch.h"
#include "Game.h"
#include "EntityManager.h"
#include "EntityFactory.h"

map<EntityType, string> Game::textureFiles = { {EntityType::Player, "vaisseau.png"} };

Game::Game() : mainWindow(sf::VideoMode(840, 600), "ZAXXON 2020 HD", sf::Style::Close) {
    loadTextures();

    shared_ptr<Entity> player = EntityFactory::createEntity(EntityType::Player, sf::Vector2f(300.f, 100.f) , true);


    sf::Sprite sprite;
    sprite.setTexture(textures.at(EntityType::Player));
    sprite.setPosition(100.f, 100.f);

    std::shared_ptr<Entity> p = std::make_shared<Entity>(); //
    p->sprite = sprite;
    p->type = EntityType::Player;
    p->size = t.getSize();
    p->position = sprite.getPosition();
    p->enabled = true;

    EntityManager::entities.push_back(p);

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

void Game::loadTextures() {

    for (pair<EntityType, string> element : textureFiles)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(element.second)) exit(EXIT_FAILURE);

        textures.insert({ element.first, texture });
    }
}
