#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"
#include "batDeathState.h"

batState * batDeathState::inputHandle(bat * bat)
{
	return nullptr;
}

void batDeathState::update(bat * bat)
{
	
	frameCount++;
	if (frameCount >= 15)		//한 번 타죽고 끝나
	{
		frameCount = 0;
		if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())
		{
			bat->setCurrentFrameX(bat->_bat.img->getMaxFrameX());
		}
		else
		{
			bat->setCurrentFrameX(bat->getCurrentFrameX() + 1);
		}
	}
}

void batDeathState::enter(bat * bat)
{
	bat->_bat.img = IMAGEMANAGER->findImage("bat_burn");
	bat->setImageName("bat_burn");

	if (!bat->isRight)
	{
		bat->setCurrentFrameY(1);
	}
	if (bat->isRight)
	{
		bat->setCurrentFrameY(0);
	}
	bat->setCurrentFrameX(0);

	bat->isCollisionDamaged = true;
	bat->isDeath = false;
}

void batDeathState::exit(bat * bat)
{
}
