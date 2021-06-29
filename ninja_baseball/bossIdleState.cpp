#include "stdafx.h"
#include "bossIdleState.h"
#include "bossEntryState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "boss.h"

bossState * bossIdleState::inputHandle(boss * boss)
{
	if (boss->_stateCount >= 3 && !boss->_isPreWind)
	{
		boss->_stateCount = 0;
		boss->_isJump = true;
		boss->_isPreWind = true;
		return new bossWindState();
	}

	if (boss->_stateCount >= 2 && boss->_isPreWind)
	{
		boss->_stateCount = 0;
		boss->_isShootingAttack = false;
		return new bossMoveState();
	}

	return nullptr;
}

void bossIdleState::update(boss * boss)
{
	if (!boss->_isLeft)
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
			boss->_currentFrameY = 1;
		}
	}

	else if (boss->_isLeft)
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
}

void bossIdleState::enter(boss * boss)
{
	boss->_bossPinLight.img = IMAGEMANAGER->findImage("boss_pinLight");
	boss->_stateCount = boss->_count;

	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_idle");
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_idle");
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_idle");
		break;
	case NO_ONE_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noOneArm_idle");
		break;
	case NO_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noArm_move");
		break;
	}

	if (!boss->_isLeft)
	{
		boss->_currentFrameX = 0;
		boss->_currentFrameY = 1;
	}

	if (boss->_isLeft)
	{
		boss->_currentFrameX = 0;
		boss->_currentFrameY = 0;
	}
}

void bossIdleState::exit(boss * boss)
{
}
