#include "stdafx.h"
#include "bossDamagedState.h"
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
#include "boss.h"

bossState * bossDamagedState::inputHandle(boss * boss)
{
	return nullptr;
}

void bossDamagedState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 7)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = boss->_boss.img->getMaxFrameX();
		}
		else boss->_currentFrameX++;
	}
}

void bossDamagedState::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_attacked");
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_attacked");
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_attacked");
		break;
	case NO_ONE_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noOneArm_attacked");
		break;
	case NO_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noArm_attacked");
		break;
	default:
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

	boss->_isDamagedState = true;
}

void bossDamagedState::exit(boss * boss)
{
}
