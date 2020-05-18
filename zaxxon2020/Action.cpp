#include "pch.h"
#include "Action.h"

#include "EntityManager.h"
#include "EntityFactory.h"

const float Action::PlayerSpeed = 10.f;

void Action::Execute(ActionType type)
{
	switch (type)
	{
		case ActionType::PlayerFireLaser:
			PlayerFireLaser();
			break;
		case ActionType::PlayerLeftMove:
			PlayerLeftMove();
			break;
		case ActionType::PlayerRightMove:
			PlayerRightMove();
			break;
		case ActionType::PlayerUpMove:
			PlayerUpMove();
			break;
		case ActionType::PlayerDownMove:
			PlayerDownMove();
			break;
		default:
			break;
	}
}

void Action::PlayerFireLaser() {
	shared_ptr<Entity> player = EntityManager::GetPlayer();

	int position_x = player->sprite.getPosition().x + player->sprite.getTexture()->getSize().x;
	int position_y = player->sprite.getPosition().y ;

	//EntityManager::GetPlayer()->m_sprite.getPosition().x + EntityManager::GetPlayer()->m_sprite.getTexture()->getSize().x / 2,
	//	EntityManager::GetPlayer()->m_sprite.getPosition().y - 10

	shared_ptr<Entity> playerLaser = EntityFactory::createEntity(EntityType::PlayerLaser, sf::Vector2f(position_x, position_y), true);
	EntityManager::entities.push_back(playerLaser);
}


void Action::PlayerLeftMove() {
	sf::Vector2f movement(-PlayerSpeed, 0.f);
	shared_ptr<Entity> player = EntityManager::GetPlayer();
	player->sprite.move(movement);
}

void Action::PlayerRightMove() {
	sf::Vector2f movement(PlayerSpeed, 0.f);
	shared_ptr<Entity> player = EntityManager::GetPlayer();
	player->sprite.move(movement);
}

void Action::PlayerUpMove() {
	sf::Vector2f movement(0.f, -PlayerSpeed);
	shared_ptr<Entity> player = EntityManager::GetPlayer();
	player->sprite.move(movement);
}

void Action::PlayerDownMove() {
	sf::Vector2f movement(0.f, PlayerSpeed);
	shared_ptr<Entity> player = EntityManager::GetPlayer();
	player->sprite.move(movement);
}
