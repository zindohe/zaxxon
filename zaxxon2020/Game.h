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
		void handleEnemiesMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, MovementType movementType, int movementSize);
		void update(sf::Time elapsedTime);

		void verticalBackAndForthMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);
		void horizontalBackAndForthMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);
		void circleMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);
		void zigzagMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);


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
		int horizontalEnemyFramePos = 0;
		float entities_angle = 90.f * PI / 180.f;
		int horizontalMovesCounter = 0;
};

