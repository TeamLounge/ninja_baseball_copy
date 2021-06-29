#include "stdafx.h"
#include "bossUpperCutState.h"
#include "bossStraightAttackState.h"
#include "bossShootingState.h"
#include "bossShootingReady.h"
#include "bossShootingProp.h"
#include "bossEntryState.h"
#include "bossIdleState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossJabAttackState.h"
#include "bossDamagedState.h"
#include "boss.h"

bossState * bossUpperCutState::inputHandle(boss * boss)
{
	return nullptr;
}

void bossUpperCutState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 10)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = boss->_boss.img->getMaxFrameX();
			readyCount = 0;
		}
		else
		{
			boss->_currentFrameX++;
			readyCount++;
		}
	}

	jump(boss);
}

void bossUpperCutState::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_straight");
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_upperCut");
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_upperCut");
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

	boss->_isUpperCutState = true;
}

void bossUpperCutState::exit(boss * boss)
{
}

void bossUpperCutState::jump(boss * boss)
{

}
