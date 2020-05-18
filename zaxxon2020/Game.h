#pragma once

#include "EntityFactory.h"

class Game
{
	public:
		Game();
		~Game();
		void run();
		
	private:
		void processEvents();
		void handlePlayerActions(sf::Keyboard::Key key, bool isPressed);
		void update(sf::Time elapsedTime);

		sf::RenderWindow mainWindow; // Fen�tre Principale o� l'on va poser des elements graphique
		
		void render();
		void initSprite();

		sf::CircleShape shape;
		static const sf::Time	TimePerFrame;
		bool isUpPressed = false;
		bool isDownPressed = false;
		bool isLeftPressed = false;
		bool isRightPressed = false;
};

