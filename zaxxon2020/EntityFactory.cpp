#include "pch.h"
#include "EntityFactory.h"

map<EntityType, string> EntityFactory::textureFiles = { {EntityType::Player, "vaisseau.png"},
												{EntityType::Laser_cyan_right, "sprites/laser-cyan-horizontal.png"} };

map<EntityType, shared_ptr<sf::Texture>> EntityFactory::textures;

shared_ptr<Entity> EntityFactory::createEntity(EntityType type, const sf::Vector2f &positions, bool enabled) {

	shared_ptr<sf::Texture> texture = textures.at(type);

	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setPosition(positions);


	shared_ptr<Entity> entity = make_shared<Entity>();
	entity->size = texture->getSize();
	entity->position = sprite.getPosition();
	entity->type = type; 
	entity->sprite = sprite;
	entity->enabled = enabled;

	return entity;
}


void EntityFactory::loadTextures() {
	
	for (pair<EntityType, string> element : textureFiles)
	{
		shared_ptr<sf::Texture> texture = make_shared<sf::Texture>();
		if (!texture->loadFromFile(element.second)) exit(EXIT_FAILURE);
		textures.insert({ element.first, texture });
	}

}

