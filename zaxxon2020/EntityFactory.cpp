#include "pch.h"
#include "EntityFactory.h"

map<EntityType, string> EntityFactory::textureFiles = { 
												{EntityType::Background, "sprites/galaxy.jpg"},
												{EntityType::Player, "sprites/vaisseau.png"},
												{EntityType::LaserCyanHorizontal, "sprites/laser_cyan_horizontal.png"},
												{EntityType::LaserBlueHorizontal, "sprites/laser_blue_horizontal.png"},
												{EntityType::LaserRedHorizontal, "sprites/laser-red-horizontal.png"},
												{EntityType::EnnemyAlphaHorizontalLeft, "sprites/ennemiy_alpha_horizontal_left.png"},
												{EntityType::EnnemyBetaHorizontalLeft, "sprites/ennemy_beta_horizontal_left.png"},
												{EntityType::EnnemyBoss, "sprites/ennemy_insect.png"},
												{EntityType::Delimiter, "sprites/delimiter.png"}
												};

map<EntityType, shared_ptr<sf::Texture>> EntityFactory::textures;

shared_ptr<Entity> EntityFactory::createEntity(EntityType type, const sf::Vector2f &positions, bool enabled) {


	shared_ptr<Entity> entity = make_shared<Entity>();
	entity->type = type;
	entity->position = positions;
	entity->enabled = enabled;

	shared_ptr<sf::Texture> texture = textures.at(type);
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setPosition(positions);

	entity->size = texture->getSize();
	entity->sprite = sprite;

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

