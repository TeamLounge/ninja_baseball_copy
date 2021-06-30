#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"

batState * batDamagedState::inputHandle(bat * bat)
{
	return nullptr;
}

void batDamagedState::update(bat * bat)
{
	if (damageCount == 3)
	{
		//noCapMode
	}
	else if (damageCount == 4)
	{
		//noBatMode
	}
	else if (damageCount == 5)
	{
		//death
	}
	
	frameCount++;
	if (frameCount >= 8)
	{
		frameCount = 0;
		if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())
		{
			bat->setCurrentFrameX(0);
		}
		else 
		{
			bat->setCurrentFrameX(bat->getCurrentFrameX() + 1);

		}
		bat->setCurrentFrameY(1);
	}
}

void batDamagedState::enter(bat * bat)
{
	bat->isDamaged = true;
	bat->_bat.img = IMAGEMANAGER->findImage("fBat_damaged");
	bat->setCurrentFrameX(0);
	bat->setCurrentFrameY(1);

	damageCount++;		//피격 카운트(몇 대 맞는 중?)
}

void batDamagedState::exit(bat * bat)
{
}
