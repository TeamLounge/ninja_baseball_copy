#include "stdafx.h"
#include "cardSmallDamagedState.h"
#include "card.h"
#include "cardPunchAttackState.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardDeathState.h"
#include "cardHeavyDamagedState.h"

cardState * cardSmallDamagedState::inputHandle(card * card)
{

	return nullptr;
}

void cardSmallDamagedState::update(card * card)
{
	frameCount++;
	if (frameCount >= 5)
	{
		frameCount = 0;
		if (card->_currentFrameX == card->_card.img->getMaxFrameX())
		{
			readyCount++;
			if (readyCount >= 2)
			{
				card->_currentFrameX = card->_card.img->getMaxFrameX();
			}

		}

		else card->_currentFrameX++;
	}
}

void cardSmallDamagedState::enter(card * card)
{
	if (!card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 1;
	}

	if (card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 0;
	}

	readyCount = 0;
}

void cardSmallDamagedState::exit(card * card)
{

}
