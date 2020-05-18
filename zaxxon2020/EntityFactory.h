#pragma once

#include "Entity.h"

class EntityFactory
{
	private:
		static map<EntityType, string> textureFiles;
		static map<EntityType, shared_ptr<sf::Texture>> textures;
	public:
		static shared_ptr<Entity> createEntity(EntityType type,const sf::Vector2f& positions, bool enabled);
		static void loadTextures(); // Load all textures

};

