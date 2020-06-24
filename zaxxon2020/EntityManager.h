#pragma once
#include "Entity.h"

class EntityManager
{
	public : 
		EntityManager();
		~EntityManager();
		
	public : 
		static vector<shared_ptr<Entity>> entities;
		static shared_ptr<Entity> GetPlayer();
		static void DeleteAllEnnemies();
		static bool isEnnemy(shared_ptr<Entity> entity);
		static shared_ptr<Entity> GetPlayerLaser();
		static void deleteEntity(shared_ptr<Entity> entity);
		static void deleteAll();
		static void deleteEnemyLaser();
};



