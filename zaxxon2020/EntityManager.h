#pragma once
#include "Entity.h"

class EntityManager
{
	public : 
		EntityManager();
		~EntityManager();
		
	public : 
		static vector<shared_ptr<Entity>> entities;
		static std::shared_ptr<Entity> GetPlayer();
};

