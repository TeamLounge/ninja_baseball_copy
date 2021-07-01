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
#include "bossSmallDamagedState.h"
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
	if (boss->_currentFrameX == 0)
	{
		frameCount++;
		if (frameCount >= 30)
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
	}

	else
	{
		frameCount++;
		if (frameCount >= 15)
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
	}


	jump(boss);
}

void bossDeathState::enter(boss * boss)
{
	boss->_boss.img = IMAGEMANAGER->findImage("noArm_death");
	boss->_imageName = "noArm_death";

	readyCount = 0;
	boss->_currentFrameX = 0;
}

void bossDeathState::exit(boss * boss)
{
}

void bossDeathState::jump(boss * boss)
{
	if (readyCount >= 1 && !boss->_isJump &&
		boss->_currentFrameX == readyCount)
	{
		boss->_isJump = true;
		jumpPower = 10.5f;
		gravity = 0.25f;
		readyCount = 0;
		if ((boss->_boss.rc.left + boss->_boss.rc.right) / 2 < CAMERAMANAGER->getCameraCenterX()) moveX = 4.5f;
		else moveX = -5.5f;
	}

	if (boss->_isJump)
	{
		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
		boss->_boss.x += moveX;
		boss->_jumpShadowY -= 1.35f;
	}

	if ((boss->_bossShadow.rc.bottom + boss->_bossShadow.rc.top) / 2 < boss->_boss.rc.bottom)
	{
		boss->_boss.rc.bottom = boss->_jumpShadowY - 5;
		jumpPower = 0;
		gravity = 0;
		boss->_isJump = false;
	}
}
