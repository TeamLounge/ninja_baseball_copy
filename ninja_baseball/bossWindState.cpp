#include "stdafx.h"
#include "bossWindState.h"
#include "bossIdleState.h"
#include "bossEntryState.h"
#include "bossMoveState.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "bossDeathState.h"
#include "boss.h"

bossState * bossWindState::inputHandle(boss * boss)
{
	if (!boss->_isJump)
	{
		boss->_stateCount = 0;
		EFFECTMANAGER->stop("boss_windEffect");
		EFFECTMANAGER->stop("boss_windEffect2");
		return new bossIdleState();
	}

	return nullptr;
}

void bossWindState::update(boss * boss)
{
	frameCount++;

	if (frameCount >= 3 && jumpPower >= 0.2f)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = 0;
		}
		else boss->_currentFrameX++;
		boss->_currentFrameY = 0;
	}

	if (frameCount >= 8 && jumpPower < 0.2f)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = 0;
		}
		else boss->_currentFrameX++;
		boss->_currentFrameY = 0;
	}
	
	EFFECTMANAGER->play("boss_windEffect", boss->_bossShadow.rc.left - RND->getFromFloatTo(150.f, 600.f),
		boss->_boss.rc.bottom + RND->getFromFloatTo(-150.f, 150.f));
	EFFECTMANAGER->update(RND->getFromFloatTo(-1.5f, -3.5f), RND->getFromFloatTo(5.5f, 15.5f));

	EFFECTMANAGER->play("boss_windEffect2", boss->_bossShadow.rc.left - RND->getFromFloatTo(150.f, 600.f),
		boss->_boss.rc.bottom + RND->getFromFloatTo(-150.f, 150.f));
	EFFECTMANAGER->update(RND->getFromFloatTo(-1.5f, -3.5f), RND->getFromFloatTo(-5.5f, -15.5f));

	flying(boss);
}

void bossWindState::enter(boss * boss)
{
	boss->_boss.img = IMAGEMANAGER->findImage("boss_wind");
	boss->_imageName = "boss_wind";

	boss->_currentFrameX = 0;
	boss->_currentFrameY = 0;

	jumpPower = 3.5f;
	gravity = 0.f;
	
}

void bossWindState::exit(boss * boss)
{
}

void bossWindState::flying(boss * boss)
{
	if (boss->_isJump)
	{
		boss->_stateCount++;

		if (boss->_stateCount >= 30 && gravity == 0)
		{
			gravity = 0.08f;
			boss->_isPinLight = false;
			boss->_stateCount = 0;
		}

		if (boss->_stateCount >= 40 && gravity != 0)
		{
			jumpPower = 0.25f;
			gravity = 0.08f;
			boss->_stateCount = 0;
		}

		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
		boss->_boss.x -= 3.5f;

		if ((boss->_bossShadow.rc.bottom + boss->_bossShadow.rc.top) / 2 < boss->_boss.rc.bottom)
		{
			boss->_boss.rc.bottom = boss->_jumpShadowY;
			jumpPower = 0;
			gravity = 0;
			boss->_isJump = false;
		}
	}
}
