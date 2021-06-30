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
#include "bossDeathState.h"
#include "boss.h"

bossState * bossUpperCutState::inputHandle(boss * boss)
{
	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() &&
		!boss->_isJump)
	{
		boss->_isUpperCutState = false;
		return new bossIdleState();
	}

	return nullptr;
}

void bossUpperCutState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 5)
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
		boss->_boss.img = IMAGEMANAGER->findImage("boss_upperCut");
		boss->_imageName = "boss_upperCut";
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_upperCut");
		boss->_imageName = "noWing_upperCut";
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_upperCut");
		boss->_imageName = "noWingProp_upperCut";
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
	if (readyCount >= 4 && !boss->_isJump &&
		boss->_currentFrameX == readyCount)
	{
		boss->_isJump = true;
		jumpPower = 7.5f;
		gravity = 0.55f;
		readyCount = 0;
	}

	if (boss->_isJump)
	{
		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
	}

	if ((boss->_bossShadow.rc.bottom + boss->_bossShadow.rc.top) / 2 < boss->_boss.rc.bottom)
	{
		boss->_boss.rc.bottom = boss->_jumpShadowY - 5;
		jumpPower = 0;
		gravity = 0;
		boss->_isJump = false;
	}
}
