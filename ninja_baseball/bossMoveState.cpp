#include "stdafx.h"
#include "bossMoveState.h"
#include "bossWindState.h"
#include "bossIdleState.h"
#include "bossEntryState.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "boss.h"

bossState * bossMoveState::inputHandle(boss * boss)
{
	if (boss->_isShootingAttack && !boss->_isJabAttack)
	{
		return new bossShootingReady();
	}

	if (boss->_isJabAttack && !boss->_isShootingAttack)
	{
		return new bossJabAttackState();
	}

	if (boss->_isStraightAttack)
	{
		return new bossStraightAttackState();
	}

	if (boss->_isDamaged)
	{
		return new bossDamagedState();
	}

	return nullptr;
}

void bossMoveState::update(boss * boss)
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

		if (!boss->_isMoveStopRangeX) boss->_boss.x += 2.5f;
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

		if (!boss->_isMoveStopRangeX) boss->_boss.x -= 2.5f;
	}

	if (!boss->_isMoveStopRangeY)
	{
		if (!boss->_isUpper) boss->_boss.y -= 1.5f;
		if (boss->_isUpper) boss->_boss.y += 1.5f;
	}
}

void bossMoveState::enter(boss * boss)
{
	//boss->_stateCount = boss->_count;

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

void bossMoveState::exit(boss * boss)
{
}
