#pragma once

#include "Entity.h"

class Spawner
{
public:
	static void LinearStrategy(sf::Vector2u mainWindowSize, EntityType type, int number, sf::Vector2f first_positions);
	static void DefaultStrategy(EntityType type, sf::Vector2f first_positions);
	static void CircleStrategy(EntityType type, int number, sf::Vector2f first_positions);
};

