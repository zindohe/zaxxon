#pragma once
class Game
{
	public:
		Game();
		~Game();
		void run();
	
	private:
		sf::RenderWindow mainWindow; // Fen�tre Principale o� l'on va poser des elements graphique
		sf::CircleShape shape;
};

