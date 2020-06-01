#include "pch.h"
#include "Action2.h"

#include "EntityManager.h"
#include "EntityFactory.h"

const float Action::PlayerSpeed = 10.f;

void Action::PlayerFireLaser() {
	shared_ptr<Entity> player = EntityManager::GetPlayer();

	int position_x = player->sprite.getPosition().x + player->sprite.getTexture()->getSize().x;
	int position_y = player->sprite.getPosition().y - (player->sprite.getTexture()->getSize().y / 2);

	shared_ptr<Entity> playerLaser = EntityFactory::createEntity(EntityType::PlayerLaser, sf::Vector2f(position_x, position_y), true);
	EntityManager::entities.push_back(playerLaser);
}


void Action::PlayerLeftMove() {
	shared_ptr<Entity> player = EntityManager::GetPlayer();
	if (player->sprite.getPosition().x > PlayerSpeed)
	{
		sf::Vector2f movement(-PlayerSpeed, 0.f);
		player->sprite.move(movement);
	}
}

void Action::PlayerRightMove(const float windowWidthSize) {

	shared_ptr<Entity> player = EntityManager::GetPlayer();
	if (player->sprite.getPosition().x + player->size.x < windowWidthSize - PlayerSpeed)
	{
		sf::Vector2f movement(PlayerSpeed, 0.f);
		player->sprite.move(movement);
	}
}

void Action::PlayerUpMove() {

	shared_ptr<Entity> player = EntityManager::GetPlayer();
	if (player->sprite.getPosition().y > PlayerSpeed)
	{
		sf::Vector2f movement(0.f, -PlayerSpeed);
		player->sprite.move(movement);
	}

}

void Action::PlayerDownMove(const float windowHeightSize) {

	shared_ptr<Entity> player = EntityManager::GetPlayer();

	if (player->sprite.getPosition().y + player->size.y < windowHeightSize - PlayerSpeed)
	{
		sf::Vector2f movement(0.f, PlayerSpeed);
		player->sprite.move(movement);
	}

}

