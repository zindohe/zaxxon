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


void EntityManager::DeleteAllEnnemies()
{
	cout << "vector entities size before : " << EntityManager::entities.size() << endl;
    for (auto iterator = EntityManager::entities.begin(); iterator != EntityManager::entities.end(); iterator++)
    {
		shared_ptr<Entity> entity = *iterator;
        if (entity->type == EntityType::EnnemyAlphaHorizontalLeft ||
			entity->type == EntityType::EnnemyBetaHorizontalLeft ||
			entity->type == EntityType::EnnemyBoss )
        {

			entity->enabled = false;
			iterator--;
			EntityManager::entities.erase(iterator + 1);
        }
    }

	cout << "vector entities size after : " << EntityManager::entities.size() << endl;

}

