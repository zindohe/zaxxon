#pragma once

enum EntityType
{
	Background,
	Player,
	Sbire,
	LaserCyanHorizontal,
	LaserBlueHorizontal,
	LaserRedHorizontal,
	EnnemyAlphaHorizontalLeft,
	EnnemyBetaHorizontalLeft,
	EnnemyBoss,
	Delimiter,

	None
};

enum MovementType
{
	VerticalBackAndForth,
	HorizontalBackAndForth,
	Circle,
	Zigzag
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
