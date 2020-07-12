#include "pch.h"
#include "Spawner.h"

#include "EntityFactory.h"
#include "EntityManager.h"


void Spawner::LinearStrategy(sf::Vector2u mainWindowSize, EntityType type, int number, sf::Vector2f first_positions)
{

    shared_ptr<Entity> entity = EntityFactory::createEntity(EntityType::EnnemyAlphaHorizontalLeft, first_positions, true);

    float factor_y = (mainWindowSize.y / number);

    for (int i = 1; i <= number; i++)
    {
        float pos_y = (factor_y * i) - (factor_y / 2) - (entity->size.y / 2) + first_positions.y;
        entity = EntityFactory::createEntity(type, sf::Vector2f(first_positions.x, pos_y), true);
        EntityManager::entities.push_back(entity);
    }
}

void Spawner::DefaultStrategy(EntityType type, sf::Vector2f first_positions)
{
    shared_ptr<Entity> entity = EntityFactory::createEntity(type, first_positions, true);

    EntityManager::entities.push_back(entity);

}

void Spawner::CircleStrategy(EntityType type, int number, sf::Vector2f first_positions)
{
    shared_ptr<Entity> entity;

    float angle = 0.f;
    float angle_between = 360.f / number;
    float radius = 80.f;


    for (int i = 1; i <= number; i++)
    {
        entity = EntityFactory::createEntity(type, sf::Vector2f(first_positions.x + (radius * cos(angle * (PI / 180))), first_positions.y + (radius * sin(angle * (PI / 180)))), true);
        EntityManager::entities.push_back(entity);
        angle += angle_between;
    }
}



