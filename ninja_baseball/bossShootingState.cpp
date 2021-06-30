#include "stdafx.h"
#include "bossShootingState.h"
#include "bossShootingReady.h"
#include "bossShootingProp.h"
#include "bossEntryState.h"
#include "bossIdleState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "bossDeathState.h"
#include "boss.h"

bossState * bossShootingState::inputHandle(boss * boss)
{
	if (boss->_stateCount >= 4)
	{
		boss->_isTrigger = false;
		boss->_stateCount = 0;
		EFFECTMANAGER->stop("boss_bullet");
		return new bossShootingProp();
	}

	return nullptr;
}

void bossShootingState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 5)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_stateCount++;
			boss->_currentFrameX = 0;
		}
		else boss->_currentFrameX++;
	}

	EFFECTMANAGER->play("boss_bullet", (boss->_longRangeAtkRc.left + boss->_longRangeAtkRc.right) / 2 + RND->getFromFloatTo(-100.f, 100.f),
		(boss->_longRangeAtkRc.top - 50) + RND->getFromFloatTo(-10.f, 10.f), 15);

	EFFECTMANAGER->update(_fireX, 0);

}

void bossShootingState::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_shooting");
		boss->_imageName = "boss_shooting";
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_shooting");
		boss->_imageName = "noWing_shooting";
		break;
	}

	boss->_stateCount = 0;
	boss->_isTrigger = true;
	boss->_isShootingState = true;

	if (!boss->_isLeft)
	{
		boss->_currentFrameX = 0;
		boss->_currentFrameY = 1;
		_fireX = 2.5f;
	}

	if (boss->_isLeft)
	{
		boss->_currentFrameX = 0;
		boss->_currentFrameY = 0;
		_fireX = -2.5f;
	}
}

void bossShootingState::exit(boss * boss)
{
}
