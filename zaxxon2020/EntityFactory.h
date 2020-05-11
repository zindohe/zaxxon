#pragma once

#include "Entity.h"

class EntityFactory
{

public:
	static shared_ptr<Entity> createEntity(EntityType type, const sf::Vector2f& positions, bool enabled);

};

