#include "stdafx.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
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

bossState * bossShootingReady::inputHandle(boss * boss)
{
	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
	{
		return new bossShootingState();
	}

	return nullptr;
}

void bossShootingReady::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 8)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = boss->_boss.img->getMaxFrameX();
		}
		else boss->_currentFrameX++;
	}
}

void bossShootingReady::enter(boss * boss)
{
	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_shootingR");
		boss->_imageName = "boss_shootingR";
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_shootingReady");
		boss->_imageName = "noWing_shootingReady";
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

	boss->_isMoveState = false;
}

void bossShootingReady::exit(boss * boss)
{
}
