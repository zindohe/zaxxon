#include "pch.h"
#include "EntityManager.h"
#include "Action2.h"
#include "Spawner.h"

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

shared_ptr<Entity> EntityManager::GetEntityByType(EntityType type)
{
	for (std::shared_ptr<Entity> entity : EntityManager::entities)
	{
		if (entity->type == type)
		{
			return entity;
		}
	}

	return nullptr;
}

bool EntityManager::isEnnemy(std::shared_ptr<Entity> entity)
{
	if (entity->type == EntityType::EnnemyAlphaHorizontalLeft ||
		entity->type == EntityType::EnnemyBetaHorizontalLeft ||
		entity->type == EntityType::EnnemyBoss ||
		entity->type == EntityType::EnnemyGamma) {
		return true;
	}
	return false;
}

bool EntityManager::isBonus(std::shared_ptr<Entity> entity)
{
	if (entity->type == EntityType::BlueBonus ||
		entity->type == EntityType::GreenBonus ||
		entity->type == EntityType::YellowBonus) {
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

shared_ptr<Entity> EntityManager::GetPlayerSuperLaserDown()
{
	for (std::shared_ptr<Entity> entity : EntityManager::entities)
	{
		if (entity->enabled == false)
		{
			continue;
		}

		if (entity->type == EntityType::PlayerSuperLaserDown)
		{
			return entity;
		}
	}

	return nullptr;
}

shared_ptr<Entity> EntityManager::GetPlayerSuperLaserUp()
{
	for (std::shared_ptr<Entity> entity : EntityManager::entities)
	{
		if (entity->enabled == false)
		{
			continue;
		}

		if (entity->type == EntityType::PlayerSuperLaserUp)
		{
			return entity;
		}
	}

	return nullptr;
}

void EntityManager::deleteEntity(shared_ptr<Entity> entity)
{
	if (entity->type == EntityType::PlayerLaser ||
		entity->type == EntityType::PlayerSuperLaserDown ||
		entity->type == EntityType::PlayerSuperLaserUp) {
		Action::isPlayerFiring = false;
	}

	if (isEnnemy(entity)) {
		int r = rand() % 100 + 1;
		if (r >= 15)
			goto erase;

		if (r % 3 == 0) {
			//Health Bonus
			Spawner::DefaultStrategy(EntityType::GreenBonus, entity->sprite.getPosition());
		}
		else if(r % 3 == 1) {
			//Speed Bonus
			Spawner::DefaultStrategy(EntityType::BlueBonus, entity->sprite.getPosition());
		}
		else if (r % 3 == 2) {
			//SuperLaser Bonus
			Spawner::DefaultStrategy(EntityType::YellowBonus, entity->sprite.getPosition());
		}
	}

	erase:
	for (int i = 0; i < EntityManager::entities.size(); i++) {
		if (EntityManager::entities[i] == entity)
		{
			EntityManager::entities.erase(EntityManager::entities.begin()+i);
		}
	}
}

void EntityManager::DeleteAllEnnemies()
{
    for (auto iterator = EntityManager::entities.begin(); iterator != EntityManager::entities.end(); iterator++)
    {
		shared_ptr<Entity> entity = *iterator;
		if (entity != nullptr) {
			if (isEnnemy(entity) || isBonus(entity))
			{

				entity->enabled = false;
				iterator--;
				EntityManager::entities.erase(iterator + 1);
			}
		}
    }

	// Reset Stage's bonuses

	Action::PlayerSpeed = 10.f;
	Action::isSuperLaserActive = false;

	GetPlayer()->sprite.setColor(sf::Color(255, 255, 255));

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

