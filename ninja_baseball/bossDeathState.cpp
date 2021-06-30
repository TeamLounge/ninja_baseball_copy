#include "stdafx.h"
#include "bossDeathState.h"
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

bossState * bossDeathState::inputHandle(boss * boss)
{
	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
	{
		boss->_isDeathState = true;
	}

	return nullptr;
}

void bossDeathState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 12)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = boss->_boss.img->getMaxFrameX();
		}
		else boss->_currentFrameX++;
	}
}

void bossDeathState::enter(boss * boss)
{
	boss->_boss.img = IMAGEMANAGER->findImage("noArm_death");
	boss->_imageName = "noArm_death";
}

void bossDeathState::exit(boss * boss)
{
}
