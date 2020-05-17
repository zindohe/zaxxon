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
		sf::RenderWindow mainWindow; // Fenêtre Principale où l'on va poser des elements graphique
};

