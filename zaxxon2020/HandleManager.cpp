#include "pch.h"
#include "HandleManager.h"

#include "EntityManager.h"

void HandleManager::HandlePlayerLaserMove(const float windowWidthSize) 
{
    for (shared_ptr<Entity> entity : EntityManager::entities)
    {
        if ( entity->enabled == false || entity->type != EntityType::PlayerLaser)
        {
            continue;
        }

        sf::Vector2f position = entity->sprite.getPosition();
        position.x += 1;

        if (position.x > windowWidthSize)
        {
            entity->enabled = false;
        }

        entity->sprite.setPosition(position);
    }
}
