#include "pch.h"
#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mainWindow(sf::VideoMode(840, 600), "SFML works!", sf::Style::Close)
             , shape(100.f){
    shape.setFillColor(sf::Color::Green);
    if (!testFont.loadFromFile("Media/Sansation.ttf"))
    {
        printf("ERREUR : police non chargee");
    }

    init();
}
Game::~Game() {

}

void Game::init()
{
    testText.setString("NO MOVE");
    testText.setFont(testFont);
    testText.setPosition(0.f, 0.f);
    testText.setCharacterSize(24);
    testText.setFillColor(sf::Color::Blue);
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

void Game::render() 
{
    mainWindow.clear();
    mainWindow.draw(testText);
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
    // handle player actions consequences there
    if (isUpPressed) {
        testText.setString("UP");
    } else if (isDownPressed) {
        testText.setString("DOWN");
    }
}

