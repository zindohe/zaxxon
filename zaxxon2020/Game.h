#pragma once
class Game
{
	public:
		Game();
		~Game();
		void run();
	
	private:
		sf::RenderWindow mainWindow; // Fenêtre Principale où l'on va poser des elements graphique
		sf::CircleShape shape;
};

