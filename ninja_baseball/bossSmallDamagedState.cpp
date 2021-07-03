#include "stdafx.h"
#include "bossSmallDamagedState.h"
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

bossState * bossSmallDamagedState::inputHandle(boss * boss)
{
	//부품이 바로 빠져나가는 작업 해야됨. // 마지막 죽는장면 해야됨
	if (boss->_stateCount != boss->_bossForm)
	{
		return new bossSmallDamagedState();
	}

	if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1 &&
		boss->_count < 20)
	{
		boss->_isSmallDamaged = false;
		boss->_isSmallDamagedState = false;
		boss->_isGreenAttack12 = false;
		boss->_isGreenAttack3 = false;
		boss->_isRedAttack1 = false;
		boss->_isRedAttack2 = false;
		boss->_isRedAttack3 = false;
		boss->_isGreenCatchAttack = false;
		return new bossIdleState();
	}

	if (boss->_bossForm == NO_ARM && boss->_count >= 20 &&
		boss->_stateCount == boss->_bossForm &&
		boss->_currentFrameX == boss->_boss.img->getMaxFrameX() + 1)
	{
		deathCount++;
		if (deathCount >= 4)
		{
			boss->_isSmallDamagedState = false;
			return new bossDeathState();
		}
	}

	if (boss->_isGreenAttack12)
	{
		boss->_isGreenAttack12 = false;
		boss->_currentFrameX = 0;
	}

	if (boss->_isRedAttack1 || boss->_isRedAttack2)
	{
		if (boss->_isRedAttack1) boss->_isRedAttack1 = false;
		if (boss->_isRedAttack2) boss->_isRedAttack2 = false;
		boss->_currentFrameX = 0;
	}

	if (boss->_isGreenAttack3)
	{
		boss->_isJump = true;
		boss->_isGreenAttack3 = false;
		boss->_isSmallDamagedState = false;
		return new bossDamagedState();
	}

	if (boss->_isRedAttack3)
	{
		boss->_isJump = true;
		boss->_isRedAttack3 = false;
		boss->_isSmallDamagedState = false;
		return new bossDamagedState();
	}

	if (boss->_isRedDynamiteDance)
	{
		boss->_isRedDynamiteOn = true;
		frameCount = 0;
		count++;
		if (count >= 10)
		{
			count = 0;
			boss->_currentFrameX++;
			if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX() - 1)
			{
				boss->_currentFrameX = 0;
				boss->_count++;
			}
		}
	}

	if (!boss->_isRedDynamiteDance && boss->_isRedDynamiteOn)
	{
		boss->_isJump = true;
		boss->_isSmallDamagedState = false;
		return new bossDamagedState();
	}

	if (boss->_isRedHomeRunAttack)
	{
		boss->_isJump = true;
		boss->_isRedAttack1 = false;
		boss->_isRedAttack2 = false;
		boss->_isSmallDamagedState = false;
		return new bossDamagedState();
	}

	if (!boss->_isGreenCatch && boss->_isGreenCatchAttackPre)
	{
		boss->_isSmallDamagedState = false;
		boss->_isSmallDamaged = false;
		return new bossIdleState();
	}

	if (boss->_isGreenCatch)
	{
		frameCount = 0;
		boss->_isGreenCatchAttackPre = true;

		if (boss->_isGreenCatchAttack)
		{
			if (boss->_currentFrameX <= 2 && catchAtkCount == 1)
			{
				boss->_count++;
				boss->_isGreenCatchAttack = false;
				boss->_isGreenCatch = false;
				boss->_isGreenCatchAttackPre = false;
				catchAtkCount++;
			}

			if (boss->_currentFrameX <= 2 && catchAtkCount == 0)
			{
				boss->_isGreenCatchAttack = false;
				boss->_isGreenCatchAttackPre = false;
				boss->_count++;
				catchAtkCount++;
			}

			catchCount++;
			if (catchCount >= 5)
			{
				catchCount = 0;
				boss->_currentFrameX++;
				if (boss->_currentFrameX > 2)
				{
					boss->_currentFrameX = 0;
				}
			}
		}
		
		if (boss->_isGreenCatchBackAttack)
		{
			boss->_isJump = true;
			boss->_isGreenCatch = false;
			boss->_isSmallDamagedState = false;
			boss->_isGreenCatchAttack = false;
			boss->_isGreenCatchAttackPre = false;
			return new bossDamagedState();
		}

			if (boss->_isGreenCatchFrontCombo)
		{
			boss->_isJump = true;
			boss->_isGreenCatch = false;
			boss->_isSmallDamagedState = false;
			boss->_isGreenCatchAttack = false;
			boss->_isGreenCatchAttackPre = false;
			return new bossDamagedState();
		}
	}
	return nullptr;
}

void bossSmallDamagedState::update(boss * boss)
{
	frameCount++;
	if (frameCount >= 9)
	{
		frameCount = 0;
		if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
		{
			readyCount++;
			if (readyCount >= 2)
			{
				boss->_currentFrameX = boss->_boss.img->getMaxFrameX() + 1;
			}
			
		}

		if (boss->_isGreenCatch)
		{
			boss->_currentFrameX = 0;
		}

		else boss->_currentFrameX++;
	}
}

void bossSmallDamagedState::enter(boss * boss)
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

	boss->_isSmallDamagedState = true;
	boss->_isMoveState = false;
	boss->_isGreenCatchAttackPre = false;
	
	if (!boss->_isGreenCatch)
	{
		boss->_count++;
	}

	readyCount = 0;
	deathCount = 0;
	damageCount = 0;
	damageCount = 0;
	cCount = 0;
	atkCnt = 0;
	catchAtkCount = 0;
}

void bossSmallDamagedState::exit(boss * boss)
{
}
