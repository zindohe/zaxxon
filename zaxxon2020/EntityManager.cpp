#include "pch.h"
#include "EntityManager.h"

vector<shared_ptr<Entity>> EntityManager::entities;


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}


std::shared_ptr<Entity> EntityManager::GetPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::entities)
	{
		if (entity->enabled == false)
		{
			continue;
		}

		if (entity->type == EntityType::Player)
		{
			return entity;
		}
	}

	return nullptr;
}
