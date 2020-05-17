#pragma once

#include "EntityFactory.h"

class Game
{
	public:
		Game();
		~Game();
		void run();
		void render();
		
	
	private:
		sf::RenderWindow mainWindow; // Fen�tre Principale o� l'on va poser des elements graphique
};

