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
		static void Execute(ActionType type);
	private:
		static void PlayerFireLaser();
		static void PlayerLeftMove();
		static void PlayerRightMove();
		static void PlayerUpMove();
		static void PlayerDownMove();

	private:
		static const float PlayerSpeed;
};

