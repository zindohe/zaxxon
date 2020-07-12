#include "pch.h"
#include "Action2.h"

#include "EntityManager.h"
#include "EntityFactory.h"

float Action::PlayerSpeed = 10.f;
bool Action::isSuperLaserActive = false;
bool Action::isPlayerFiring = false;

void Action::PlayerFireLaser() {
	shared_ptr<Entity> player = EntityManager::GetPlayer();

	int position_x = player->sprite.getPosition().x + player->sprite.getTexture()->getSize().x;
	int position_y = player->sprite.getPosition().y - (player->sprite.getTexture()->getSize().y / 2);
	int player_size = player->sprite.getTexture()->getSize().y;

	shared_ptr<Entity> playerLaser = EntityFactory::createEntity(EntityType::PlayerLaser, sf::Vector2f(position_x, position_y), true);
	
	if (isSuperLaserActive) {
		shared_ptr<Entity> playerSuperLaserDown = EntityFactory::createEntity(EntityType::PlayerSuperLaserDown, sf::Vector2f(position_x + 50, position_y - player_size), true);
		shared_ptr<Entity> playerSuperLaserUp = EntityFactory::createEntity(EntityType::PlayerSuperLaserUp, sf::Vector2f(position_x, position_y + player_size), true);
		
		playerSuperLaserDown->sprite.setRotation(45);
		playerSuperLaserUp->sprite.setRotation(-45);

		EntityManager::entities.push_back(playerSuperLaserDown);
		EntityManager::entities.push_back(playerSuperLaserUp);
	}
	

	EntityManager::entities.push_back(playerLaser);
	isPlayerFiring = true;
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

