#include "pch.h"
#include "EntityFactory.h"

map<EntityType, string> EntityFactory::textureFiles = {
												{EntityType::Stage1, "sprites/stage1.jpg"},
												{EntityType::Stage2, "sprites/stage2.png"},
												{EntityType::Stage3, "sprites/stage3.png"},
												{EntityType::Stage4, "sprites/stage4.jpg"},
												{EntityType::Stage5, "sprites/stage5.jpg"},
												{EntityType::Stage6, "sprites/stage6.png"},
												{EntityType::Stage7, "sprites/stage7.png"},
												{EntityType::Stage8, "sprites/stage8.png"},
												{EntityType::Stage9, "sprites/stage9.jpg"},

												{EntityType::Player, "sprites/vaisseau.png"},
												{EntityType::PlayerLaser, "sprites/laser_blue_horizontal.png"},
												{EntityType::LaserBlueHorizontal, "sprites/laser_blue_horizontal.png"},
												{EntityType::LaserRedHorizontal, "sprites/laser-red-horizontal.png"},
												{EntityType::EnnemyAlphaHorizontalLeft, "sprites/ennemiy_alpha_horizontal_left.png"},
												{EntityType::EnnemyBetaHorizontalLeft, "sprites/ennemy_beta_horizontal_left.png"},
												{EntityType::EnnemyBoss, "sprites/ennemy_insect.png"},
												{EntityType::Delimiter, "sprites/delimiter.png"},
												{EntityType::BlueBonus, "sprites/laser_cyan_vertical.png"},
												{EntityType::GreenBonus, "sprites/green_bonus2.png"},
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
	entity->framePosition = 0;

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

