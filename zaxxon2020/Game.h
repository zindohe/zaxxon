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
		void handleEnemiesMovement(sf::Sprite* sprite, sf::Time elapsedTime, MovementType movementType);
		void update(sf::Time elapsedTime);

		void verticalBackAndForthMovement(sf::Sprite* sprite, sf::Time elapsedTime);
		void horizontalBackAndForthMovement(sf::Sprite* sprite, sf::Time elapsedTime);
		void circleMovement(sf::Sprite* sprite, sf::Time elapsedTime);
		void zigzagMovement(sf::Sprite* sprite, sf::Time elapsedTime);


		sf::RenderWindow mainWindow; // Fen�tre Principale o� l'on va poser des elements graphique
		
		void render();
		void initSprite();

		sf::CircleShape shape;
		static const sf::Time	TimePerFrame;
		static const float		EnemiesSpeed;
		bool isUpPressed = false;
		bool isDownPressed = false;
		bool isLeftPressed = false;
		bool isRightPressed = false;
		int verticalEnemyFramePos = 0;
};

