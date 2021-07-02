#include "stdafx.h"
#include "cardLandState.h"
#include "card.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardPunchAttackState.h"
#include "cardDeathState.h"
#include "cardSmallDamagedState.h"
#include "cardHeavyDamagedState.h"
#include "cardLandState.h"

cardState * cardLandState::inputHandle(card * card)
{
	if (card->_currentFrameX == card->_card.img->getMaxFrameX() + 1 &&
		card->_deathCount < 4)
	{
		card->_isCardLandState = false;
		return new cardIdleState();
	}

	if (card->_currentFrameX == card->_card.img->getMaxFrameX() + 1 &&
		card->_deathCount >= 4)
	{
		card->_isCardLandState = false;
		return new cardDeathState();
	}

	return nullptr;
}

void cardLandState::update(card * card)
{
	frameCount++;
	if (frameCount >= 15)
	{
		if (card->_currentFrameX == card->_card.img->getMaxFrameX())
		{
			readyCount++;
			if (readyCount >= 2)
			{
				card->_currentFrameX = card->_card.img->getMaxFrameX() + 1;
			}
		}

		if (card->_currentFrameX < card->_card.img->getMaxFrameX())
		{
			card->_currentFrameX++;
		}
	}
}

void cardLandState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_stun");
	card->_imageName = "card_stun";

	if (!card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 0;
	}

	if (card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 1;
	}

	card->_isCardLandState = true;
	card->_isCardMoveState = false;

	card->_isCardSmallDamagedState = false;
	card->_isCardSmallDamaged = false;
	card->_isGreenCatch = false;
	card->_isGreenCatchAttack = false;

	deathCount = 0;
	frameCount = 0;
	readyCount = 0;
}

void cardLandState::exit(card * card)
{
}
