#include "pch.h"
#include "Entity.h"

Entity::Entity() {
	enabled = false;
	type = EntityType::None;
}

ostream& operator<<(ostream& os, const Entity& entity) {
	return os << "Entity( type=" << entity.type << ", positions=( " << entity.position.x << ", " << entity.position.y
		<< "), size=( " << entity.size.x << ", " << entity.size.y << "), sprite Origin=(" << entity.sprite.getOrigin().x
		<< ", "<< entity.sprite.getOrigin().y << ")" << ", enabled=" << entity.enabled << " )"; 
}