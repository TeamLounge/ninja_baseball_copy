#include "stdafx.h"
#include "cardDeathState.h"
#include "card.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardPunchAttackState.h"
#include "cardSmallDamagedState.h"
#include "cardHeavyDamagedState.h"
#include "cardLandState.h"

cardState * cardDeathState::inputHandle(card * card)
{
	if (card->_currentFrameX == card->_card.img->getMaxFrameX() + 1)
	{
		count++;
		if (count >= 30)
		{
			card->_isDeathState = true;
			RENDERMANAGER->deleteObj("card", 0);
		}
	}
	return nullptr;
}

void cardDeathState::update(card * card)
{
	frameCount++;
	if (frameCount >= 15)
	{
		if (card->_currentFrameX == card->_card.img->getMaxFrameX())
		{
	
			card->_currentFrameX = card->_card.img->getMaxFrameX() + 1;
		}

		else if (card->_currentFrameX < card->_card.img->getMaxFrameX())
		{
			card->_currentFrameX++;
		}
			
	}
}

void cardDeathState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_death");
	card->_imageName = "card_death";

	readyCount = 0;
	deathCount = 0;
	frameCount = 0;
	count = 0;
	card->_currentFrameX = 0;
}

void cardDeathState::exit(card * card)
{
}

