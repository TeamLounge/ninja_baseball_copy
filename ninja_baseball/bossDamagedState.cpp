#include "stdafx.h"
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
#include "bossDeathState.h"
#include "boss.h"

bossState * bossDamagedState::inputHandle(boss * boss)
{
	//부품이 바로 빠져나가는 작업 해야됨. // 마지막 죽는장면 해야됨
	if (boss->_stateCount != boss->_bossForm)
	{
		return new bossDamagedState();
	}

	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1 &&
		!boss->_isUpperCut && boss->_stateCount == boss->_bossForm)
	{
		boss->_isDamaged = false;
		boss->_isDamagedState = false;
		return new bossIdleState();
	}

	if ((boss->_bossForm == NO_ONE_ARM || boss->_bossForm == NO_ARM) &&
		boss->_isUpperCut && boss->_stateCount == boss->_bossForm)
	{
		boss->_isDamaged = false;
		boss->_isDamagedState = false;
		boss->_isUpperCut = false;
		return new bossIdleState();
	}

	if (boss->_bossForm != NO_ONE_ARM && boss->_bossForm != NO_ARM &&
		boss->_isUpperCut && boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1 &&
		boss->_stateCount == boss->_bossForm)
	{
		boss->_isDamaged = false;
		boss->_isDamagedState = false;
		boss->_isUpperCut = false;
		return new bossUpperCutState();	
	}

	if (boss->_bossForm == NO_ARM && boss->_count >= 15 && 
		boss->_stateCount == boss->_bossForm)
	{
		return new bossDeathState();
	}

	return nullptr;
}

void bossDamagedState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 15)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() - 1 &&
			boss->_isJump)
		{
			boss->_currentFrameX = 0;
		}

		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			boss->_currentFrameX = boss->_boss.img->getMaxFrameX() +1;
		}

		else boss->_currentFrameX++;
	}

	if (boss->_count == 3)
	{
		EFFECTMANAGER->update("boss_left_leftWing", 3.f, 5.f);
	}

	jump(boss);
}

void bossDamagedState::enter(boss * boss)
{
	boss->_stateCount = boss->_bossForm;

	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_attacked");
		boss->_imageName = "boss_attacked";
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_attacked");
		boss->_imageName = "noWing_attacked";
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_attacked");
		boss->_imageName = "noWingProp_attacked";
		break;
	case NO_ONE_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noOneArm_attacked");
		boss->_imageName = "noOneArm_attacked";
		break;
	case NO_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noArm_attacked");
		boss->_imageName = "noArm_attacked";
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

	boss->_isDamagedState = true;
	boss->_isMoveState = false;
	boss->_count++;

	if (boss->_count == 3)
	{
		EFFECTMANAGER->play("boss_left_leftWing", boss->_boss.rc.left, boss->_boss.rc.right);
	}


	jumpPower = 7.5f;
	gravity = 0.55f;
	readyCount = 0;
}

void bossDamagedState::exit(boss * boss)
{
}

void bossDamagedState::jump(boss * boss)
{
	if (boss->_isJump)
	{
		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
		if (boss->_currentFrameY == 1) boss->_boss.x -= 1.5f;
		if (boss->_currentFrameY == 0) boss->_boss.x += 1.5f;
	}

	if ((boss->_bossShadow.rc.bottom + boss->_bossShadow.rc.top) / 2 < boss->_boss.rc.bottom)
	{
		boss->_boss.rc.bottom = boss->_jumpShadowY - 5;
		jumpPower = 0;
		gravity = 0;
		boss->_isJump = false;
	}
}
