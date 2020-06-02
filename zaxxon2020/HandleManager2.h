#pragma once

#include "Entity.h"

class HandleManager
{
public:
	static void HandlePlayerLaserMove(const float windowWidthSize);
	static void HandleBackgrounfMovement(shared_ptr<Entity> background, const float windowWidthSize);

private:
	static void ChangeToNextStage();
};

