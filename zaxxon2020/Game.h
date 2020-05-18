#pragma once

#include "EntityFactory.h"

class Game
{
	public:
		Game();
		~Game();
		void run();
		
	private:

		sf::RenderWindow mainWindow; // Fen�tre Principale o� l'on va poser des elements graphique

		void render();
		void initSprite();

		void processEvents();
		void handlePlayerActions(sf::Keyboard::Key key, bool isPressed);
		void update(sf::Time elapsedTime);
		void handlePlayerMove();
		
		static const float		PlayerSpeed;
		static const sf::Time	TimePerFrame;

		// KeyBoard Action
		bool isUpPressed;
		bool isDownPressed;
		bool isLeftPressed;
		bool isRightPressed;
		bool isSpacePressed;
};

