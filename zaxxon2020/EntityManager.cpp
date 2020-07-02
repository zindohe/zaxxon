#include "pch.h"
#include "EntityManager.h"
#include "Action2.h"

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

void EntityManager::DeleteAllEnnemies()
{
	cout << "vector entities size before : " << EntityManager::entities.size() << endl;
    for (auto iterator = EntityManager::entities.begin(); iterator != EntityManager::entities.end(); iterator++)
    {
		shared_ptr<Entity> entity = *iterator;
		if (entity != nullptr) {
			if (entity->type == EntityType::EnnemyAlphaHorizontalLeft ||
				entity->type == EntityType::EnnemyBetaHorizontalLeft ||
				entity->type == EntityType::EnnemyBoss ||
				entity->type == EntityType::BlueBonus ||
				entity->type == EntityType::GreenBonus)
			{

				entity->enabled = false;
				iterator--;
				EntityManager::entities.erase(iterator + 1);
			}
		}
    }

	// Reset Stage's bonuses

	Action::PlayerSpeed = 10.f;

	cout << "vector entities size after : " << EntityManager::entities.size() << endl;

}

void EntityManager::deleteAll()
{
	EntityManager::entities.clear();
}

void EntityManager::deleteEnemyLaser()
{
	for (int i = 0; i < EntityManager::entities.size(); i++) {
		if (EntityManager::entities[i]->type == EntityType::LaserRedHorizontal)
		{
			EntityManager::entities.erase(EntityManager::entities.begin() + i);
			return;
		}
	}
}

