#pragma once

#include "Entity.h"

class Game
{
	public:
		Game();
		~Game();
		void run();
		void render();
		
	
	private:
		sf::RenderWindow mainWindow; // Fen�tre Principale o� l'on va poser des elements graphique
		sf::Texture t;
		
		map<EntityType, sf::Texture> textures;
		static map<EntityType, string> textureFiles;
		void loadTextures(); // Load all textures
};

