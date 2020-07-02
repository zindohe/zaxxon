#pragma once


enum ActionType
{
	PlayerFireLaser,
	PlayerLeftMove,
	PlayerRightMove,
	PlayerUpMove,
	PlayerDownMove
};

class Action
{
public:
	static void PlayerFireLaser();
	static void PlayerLeftMove();
	static void PlayerRightMove(const float windowWidthSize);
	static void PlayerUpMove();
	static void PlayerDownMove(const float windowHeightSize);
	static float PlayerSpeed;
};

