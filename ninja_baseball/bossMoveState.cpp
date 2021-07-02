#include "stdafx.h"
#include "bossMoveState.h"
#include "bossWindState.h"
#include "bossIdleState.h"
#include "bossEntryState.h"
#include "bossShootingProp.h"
#include "bossShootingReady.h"
#include "bossShootingState.h"
#include "bossJabAttackState.h"
#include "bossStraightAttackState.h"
#include "bossUpperCutState.h"
#include "bossDamagedState.h"
#include "bossDeathState.h"
#include "bossSmallDamagedState.h"
#include "boss.h"

bossState * bossMoveState::inputHandle(boss * boss)
{
	if (boss->_isShootingAttack)
	{
		if (boss->_bossForm == DEFAULT || boss->_bossForm == NO_WING) return new bossShootingReady();
		else boss->_isShootingAttack = false;
	}

	if (boss->_isJabAttack)
	{
		if (boss->_bossForm == DEFAULT ||
			boss->_bossForm == NO_WING ||
			boss->_bossForm == NO_WING_PROP) return new bossJabAttackState();
		else boss->_isJabAttack = false;
	}

	if (boss->_isStraightAttack)
	{
		if (boss->_bossForm != NO_ARM) return new bossStraightAttackState();
		else boss->_isStraightAttack = false;
	}

	if (boss->_isDamaged)
	{
		boss->_isJump = true;
		return new bossDamagedState();
	}

	if (boss->_isSmallDamaged )
	{
		return new bossSmallDamagedState();
	}
	return nullptr;
}

void bossMoveState::update(boss * boss)
{
	if (boss->_bossForm != NO_ARM)
	{
		if (!boss->_isLeft)
		{
			frameCount++;
			if (frameCount >= 15)
			{
				frameCount = 0;
				if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
				{
					boss->_currentFrameX = 0;
					boss->_stateCount++;
				}
				else boss->_currentFrameX++;
				boss->_currentFrameY = 1;
			}

			if (!boss->_isMoveStopRangeX) boss->_boss.x += 2.5f;
		}

		else if (boss->_isLeft)
		{
			frameCount++;
			if (frameCount >= 15)
			{
				frameCount = 0;
				if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
				{
					boss->_currentFrameX = 0;
					boss->_stateCount++;
				}
				else boss->_currentFrameX++;
				boss->_currentFrameY = 0;
			}

			if (!boss->_isMoveStopRangeX) boss->_boss.x -= 2.5f;
		}

		if (!boss->_isMoveStopRangeY)
		{
			if (!boss->_isUpper) boss->_boss.y -= 1.5f;
			if (boss->_isUpper) boss->_boss.y += 1.5f;
		}
	}

	else
	{
		if (isRightWall)
		{
			frameCount++;
			if (frameCount >= 15)
			{
				frameCount = 0;
				if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
				{
					boss->_currentFrameX = 0;
				}
				else boss->_currentFrameX++;
				boss->_currentFrameY = 1;
			}

			boss->_boss.x += RND->getFromFloatTo(5.f, 10.f);

			if (boss->_bossShadow.rc.right > 2000)
			{
				isRightWall = false;
				isLeftWall = true;
			}
		}

		if (isLeftWall)
		{
			frameCount++;
			if (frameCount >= 15)
			{
				frameCount = 0;
				if (boss->_currentFrameX == boss->_boss.img->getMaxFrameX())
				{
					boss->_currentFrameX = 0;
				}
				else boss->_currentFrameX++;
				boss->_currentFrameY = 0;
			}

			boss->_boss.x -= RND->getFromFloatTo(5.f, 10.f);

			if (boss->_bossShadow.rc.left < 800)
			{
				isLeftWall = false;
				isRightWall = true;
			}
		}

		if (isTopWall)
		{
			boss->_boss.y -= RND->getFromFloatTo(5.f, 10.f);

			if (boss->_bossShadow.rc.top < 400)
			{
				isTopWall = false;
				isBottomWall = true;
			}
		}

		if (isBottomWall)
		{
			boss->_boss.y += RND->getFromFloatTo(5.f, 10.f);

			if (boss->_bossShadow.rc.bottom > WINSIZEY)
			{
				isBottomWall = false;
				isTopWall = true;
			}
		}
	}
}

void bossMoveState::enter(boss * boss)
{
	//boss->_stateCount = boss->_count;

	switch (boss->_bossForm)
	{
	case DEFAULT:
		boss->_boss.img = IMAGEMANAGER->findImage("boss_idle");
		boss->_imageName = "boss_idle";
		break;
	case NO_WING:
		boss->_boss.img = IMAGEMANAGER->findImage("noWing_idle");
		boss->_imageName = "noWing_idle";
		break;
	case NO_WING_PROP:
		boss->_boss.img = IMAGEMANAGER->findImage("noWingProp_idle");
		boss->_imageName = "noWingProp_idle";
		break;
	case NO_ONE_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noOneArm_idle");
		boss->_imageName = "noOneArm_idle";
		break;
	case NO_ARM:
		boss->_boss.img = IMAGEMANAGER->findImage("noArm_idle");
		boss->_imageName = "noArm_idle";
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

	boss->_isMoveState = true;

	isRightWall = true;
	isLeftWall = false;
	isTopWall = true;
	isBottomWall = false;
}

void bossMoveState::exit(boss * boss)
{
}
