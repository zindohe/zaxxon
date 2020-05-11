#include "pch.h"
#include "Game.h"

Game::Game() : mainWindow(sf::VideoMode(840, 600), "SFML works!", sf::Style::Close)
             , shape(100.f){
    shape.setFillColor(sf::Color::Red);
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

        mainWindow.clear();
        mainWindow.draw(shape);
        mainWindow.display();
    }
}
