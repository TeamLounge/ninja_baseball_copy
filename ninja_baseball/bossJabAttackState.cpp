#include "stdafx.h"
#include "bossJabAttackState.h"
#include "bossEntryState.h"
#include "bossIdleState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "bossDeathState.h"
#include "bossSmallDamagedState.h"
#include "boss.h"

bossState * bossJabAttackState::inputHandle(boss * boss)
{
	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
	{
		boss->_isJabAttack = false;
		boss->_isJabState = false;
		return new bossIdleState();
	}

	return nullptr;
}

void bossJabAttackState::update(boss * boss)
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

void bossJabAttackState::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_oneTwoPunch");
		//boss->_imageName = "boss_oneTwoPunch";
		boss->setImageName("boss_oneTwoPunch");
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_oneTwoPunch");
		boss->_imageName = "noWing_oneTwoPunch";
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_oneTwoPunch");
		boss->_imageName = "noWingProp_oneTwoPunch";
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

	boss->_isJabState = true;
	boss->_isMoveState = false;
}

void bossJabAttackState::exit(boss * boss)
{
}
