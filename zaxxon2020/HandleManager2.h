#pragma once

#include "Entity.h"

class HandleManager
{
public:
	static void HandlePlayerLaserMove(const float windowWidthSize);
	static void HandleBackgroundMovement(shared_ptr<Entity> background, const sf::Vector2u mainWindowSize);

	static void EnnemiesStage1(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage2(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage3(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage4(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage5(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage6(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage7(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage8(const sf::Vector2u mainWindowSize);
	static void EnnemiesStage9(const sf::Vector2u mainWindowSize);

private:
	static void ChangeToNextStage();
	static void SpawnEnnemies(const sf::Vector2u mainWindowSize);

};

