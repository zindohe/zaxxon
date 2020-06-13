#include "pch.h"
#include "EntityManager.h"

vector<shared_ptr<Entity>> EntityManager::entities;


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}


shared_ptr<Entity> EntityManager::GetPlayer()
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

bool EntityManager::isEnnemy(std::shared_ptr<Entity> entity)
{
	if (entity->type == EntityType::EnnemyAlphaHorizontalLeft || entity->type == EntityType::EnnemyBetaHorizontalLeft) {
		return true;
	}
	return false;
}

shared_ptr<Entity> EntityManager::GetPlayerLaser()
{
	for (std::shared_ptr<Entity> entity : EntityManager::entities)
	{
		if (entity->enabled == false)
		{
			continue;
		}

		if (entity->type == EntityType::PlayerLaser)
		{
			return entity;
		}
	}

	return nullptr;
}

void EntityManager::deleteEntity(shared_ptr<Entity> entity)
{
	for (int i = 0; i < EntityManager::entities.size(); i++) {
		if (EntityManager::entities[i] == entity)
		{
			EntityManager::entities.erase(EntityManager::entities.begin()+i);
		}
	}
}