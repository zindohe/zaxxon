#pragma once
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
		void render();
		void init();

		sf::RenderWindow mainWindow; // Fenêtre Principale où l'on va poser des elements graphique
		sf::CircleShape shape;
		static const sf::Time	TimePerFrame;
		bool isUpPressed = false;
		bool isDownPressed = false;
		bool isLeftPressed = false;
		bool isRightPressed = false;

		sf::Text testText;
		sf::Font testFont;
};

