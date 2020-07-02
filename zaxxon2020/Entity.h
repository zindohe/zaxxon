#pragma once

enum EntityType
{
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	Stage6,
	Stage7,
	Stage8,
	Stage9,

	Player,
	Sbire,
	PlayerLaser,
	PlayerSuperLaserDown,
	PlayerSuperLaserUp,
	LaserBlueHorizontal,
	LaserRedHorizontal,
	EnnemyAlphaHorizontalLeft,
	EnnemyBetaHorizontalLeft,
	EnnemyBoss,
	Delimiter,

	BlueBonus,
	GreenBonus,
	YellowBonus,

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
		int framePosition;
};

