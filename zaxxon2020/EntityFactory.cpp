#include "pch.h"
#include "EntityFactory.h"


shared_ptr<Entity> EntityFactory::createEntity(EntityType type, const sf::Vector2f &positions, bool enabled) {

	string texturePath = "vaisseau.png";
	switch (type)
	{
		case Player:
			texturePath = "vaisseau.png";
			break;
		default:
			break;
	}

	sf::Texture texture;
	if (!texture.loadFromFile(texturePath)) {
		exit(EXIT_FAILURE);
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(100.f, 200.f);


	shared_ptr<Entity> entity = make_shared<Entity>();
	entity->size = texture.getSize();
	entity->position = sprite.getPosition();
	entity->type = type; 
	entity->sprite = sprite;
	entity->enabled = true;

	return entity;
}
