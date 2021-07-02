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
#include "bossSmallDamagedState.h"
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
		boss->_isSmallDamagedState = false;
		boss->_isGreenAttack12 = false;
		boss->_isGreenAttack3 = false;
		boss->_isGreenCatchBackAttack = false;
		boss->_isGreenCatchFrontCombo = false;
		return new bossIdleState();
	}

	if ((boss->_bossForm == NO_ONE_ARM || boss->_bossForm == NO_ARM) &&
		boss->_isUpperCut && boss->_stateCount == boss->_bossForm && 
		boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1 &&
		boss->_count < 20)
	{
		boss->_isDamaged = false;
		boss->_isDamagedState = false;
		boss->_isSmallDamagedState = false;
		boss->_isUpperCut = false;
		boss->_isGreenAttack12 = false;
		boss->_isGreenAttack3 = false;
		boss->_isGreenCatchBackAttack = false;
		boss->_isGreenCatchFrontCombo = false;
		return new bossIdleState();
	}

	if (boss->_bossForm != NO_ONE_ARM && boss->_bossForm != NO_ARM &&
		boss->_isUpperCut && boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1 &&
		boss->_stateCount == boss->_bossForm)
	{
		boss->_isDamaged = false;
		boss->_isDamagedState = false;
		boss->_isSmallDamagedState = false;
		boss->_isUpperCut = false;
		boss->_isGreenAttack12 = false;
		boss->_isGreenAttack3 = false;
		boss->_isGreenCatchBackAttack = false;
		boss->_isGreenCatchFrontCombo = false;
		return new bossUpperCutState();	
	}

	if (boss->_bossForm == NO_ARM && boss->_count >= 20 && 
		boss->_stateCount == boss->_bossForm && boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1)
	{
		deathCount++;
		if (deathCount >= 4)
		{
			boss->_isDamagedState = false;
			return new bossDeathState();
		}
	}

	return nullptr;
}

void bossDamagedState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 9)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() - 1 &&
			boss->_isJump)
		{
			boss->_currentFrameX = 0;
		}

		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() && !boss->_isJump)
		{
			readyCount++;
			if (readyCount >= 3)
			{
				boss->_currentFrameX = boss->_boss.img->getMaxFrameX() + 1;
			}

		}

		else boss->_currentFrameX++;
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
	
	if (boss->_isSmallDamaged)
	{
		boss->_count++;
		boss->_isSmallDamaged = false;
	}

	else
	{
		boss->_count++;
	}

	if (boss->_isGreenCatchBackAttack || boss->_isGreenCatchFrontCombo)
	{
		jumpPower = 15.5f;
		gravity = 0.55f;
	}

	else
	{
		jumpPower = 12.5f;
		gravity = 0.55f;
	}
	readyCount = 0;
	deathCount = 0;
	catchCount = 0;
}

void bossDamagedState::exit(boss * boss)
{
}

void bossDamagedState::jump(boss * boss)
{
	if (boss->_isJump && boss->_isGreenCatchBackAttack && !boss->_isGreenCatchFrontCombo)
	{
		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
		if (boss->_currentFrameY == 1) boss->_boss.x += 13.7f;
		if (boss->_currentFrameY == 0) boss->_boss.x -= 13.7f;
	}

	if (boss->_isJump && !boss->_isGreenCatchBackAttack && !boss->_isGreenCatchFrontCombo)
	{
		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
		if (boss->_currentFrameY == 1) boss->_boss.x -= 1.5f;
		if (boss->_currentFrameY == 0) boss->_boss.x += 1.5f;
	}

	if (boss->_isJump && !boss->_isGreenCatchBackAttack && boss->_isGreenCatchFrontCombo)
	{
		boss->_boss.y -= jumpPower;
		jumpPower -= gravity;
		if (boss->_currentFrameY == 1) boss->_boss.x -= 13.7f;
		if (boss->_currentFrameY == 0) boss->_boss.x += 13.7f;
	}

	if ((boss->_bossShadow.rc.bottom + boss->_bossShadow.rc.top) / 2 < boss->_boss.rc.bottom)
	{
		boss->_boss.rc.bottom = boss->_jumpShadowY - 5;
		jumpPower = 0;
		gravity = 0;
		boss->_isJump = false;
	}
}
