#include "stdafx.h"
#include "bossEntryState.h"
#include "bossIdleState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDeathState.h"
#include "boss.h"

bossState * bossEntryState::inputHandle(boss * boss)
{
	if (boss->_stateCount >= 3)
	{
		boss->_isPinLight = true;
		boss->_stateCount = 0;
		return new bossIdleState();
	}

	return nullptr;
}

void bossEntryState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 15)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = 0;
			boss->_stateCount++;
		}
		else boss->_currentFrameX++;
		boss->_currentFrameY = 0;
	}
}

void bossEntryState::enter(boss * boss)
{
	boss->_boss.img = IMAGEMANAGER->findImage("boss_entry");
	boss->_imageName = "boss_entry";

	boss->_currentFrameX = 0;
	boss->_currentFrameY = 0;
}

void bossEntryState::exit(boss * boss)
{
}
