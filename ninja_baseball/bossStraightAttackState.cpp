#include "stdafx.h"
#include "bossStraightAttackState.h"
#include "bossShootingState.h"
#include "bossShootingReady.h"
#include "bossShootingProp.h"
#include "bossEntryState.h"
#include "bossIdleState.h"
#include "bossWindState.h"
#include "bossMoveState.h"
#include "bossJabAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "bossDeathState.h"
#include "boss.h"

bossState * bossStraightAttackState::inputHandle(boss * boss)
{
	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
	{
		boss->_isStraightState = false;
		boss->_isStraightAttack = false;
		return new bossIdleState();
	}

	return nullptr;
}

void bossStraightAttackState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 3)
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

	move(boss);
}

void bossStraightAttackState::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_straight");
		boss->_imageName = "boss_straight";
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_straight");
		boss->_imageName = "noWing_straight";
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_straight");
		boss->_imageName = "noWingProp_straight";
		break;
	case NO_ONE_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noOneArm_straight");
		boss->_imageName = "noOneArm_straight";
		break;
	}
	if (!boss->_isLeft)
	{
		boss->_currentFrameX = 0;
		boss->_currentFrameY = 1;
		friction = -0.75f;
		dashPower = -25.f;
	}

	if (boss->_isLeft)
	{
		boss->_currentFrameX = 0;
		boss->_currentFrameY = 0;
		friction = 0.75f;
		dashPower = 25.f;
	}

	boss->_isStraightState = true;
	readyCount = 0;
	boss->_isMoveState = false;

}

void bossStraightAttackState::exit(boss * boss)
{
}

void bossStraightAttackState::move(boss * boss)
{
	if (readyCount >= 18)
	{
		boss->_boss.x -= dashPower;
		dashPower -= friction;
	}
}
