#pragma once

enum EntityType
{
	Background,
	Player,
	Sbire,
	PlayerLaser,
	LaserBlueHorizontal,
	LaserRedHorizontal,
	EnnemyAlphaHorizontalLeft,
	EnnemyBetaHorizontalLeft,
	EnnemyBoss,
	Delimiter,

	None
};

class Entity
{

	public:
		Entity();
		~Entity() { };
		friend ostream& operator<<(ostream& os, const Entity& entity);
	public:
		sf::Sprite sprite;
		sf::Vector2u size;
		sf::Vector2f position;
		EntityType type;
		bool enabled; //	True on affiche, False on ne l'affiche pas
};

