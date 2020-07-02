#pragma once

#include "EntityFactory.h"

class Game
{
	public:
		Game();
		~Game();
		void run();
		
	private:

		void render();
		void initSprite();
		void update(sf::Time elapsedTime);
		void processEvents();
		void ResetGame();

		void updateHandleManagement(sf::Time elapsedTime);
		void handlePlayerMove();

		
		void handlePlayerActions(sf::Keyboard::Key key, bool isPressed);
		void handleEnemiesMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, MovementType movementType, int movementSize);
		

		void HandleGameOver();
		void GameOver();
		void GameFinished();
		void HandleTexts();
		void HandleCollisionPlayerEnnemy();
		void HandleCollisionPlayerLaserEnnemy();
		void HandleEnnemyFiring();
		void HandleEnnemyLasersMovement();
		void HandleCollisionEnnemyLaserPlayer();
		void HandleCollisionPlayerBonus();


		void verticalBackAndForthMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);
		void horizontalBackAndForthMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);
		void circleMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);
		void zigzagMovement(std::shared_ptr<Entity> entity, sf::Time elapsedTime, int movementSize);


		sf::RenderWindow mainWindow; // Fenetre Principale ou l'on va poser des elements graphique

		
		static const float		PlayerSpeed;
		static const sf::Time	TimePerFrame;
		std::size_t	mStatisticsNumFrames;
		bool isUpPressed = false;
		bool isDownPressed = false;
		bool isLeftPressed = false;
		bool isRightPressed = false;
		bool isSpacePressed = false;

		int verticalEnemyFramePos = 0;
		int horizontalEnemyFramePos = 0;
		float entities_angle = 90.f * PI / 180.f;
		int horizontalMovesCounter = 0;
		static const float EnemiesSpeed;

		bool gameOver = false;
		bool isEnnemyFiring = false;

		sf::Time updateTime;
		sf::Text fpsText;
		sf::Text gameOverText;
		sf::Font sansationFont;
		sf::Text playerLivesText;
		int pLives = 3;
		sf::Text playerScoreText;
		int pScore = 0;
};

