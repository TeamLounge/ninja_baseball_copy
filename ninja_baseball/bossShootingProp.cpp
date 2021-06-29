#include "stdafx.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossEntryState.h"
#include "bossIdleState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "boss.h"

bossState * bossShootingProp::inputHandle(boss * boss)
{
	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
	{
		return new bossIdleState();
	}

	return nullptr;
}

void bossShootingProp::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 15)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = boss->_boss.img->getMaxFrameX();
		}
		else boss->_currentFrameX++;
	}
}

void bossShootingProp::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_shootingProp");
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_shootingProp");
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

void bossShootingProp::exit(boss * boss)
{
}
