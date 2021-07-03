#include "stdafx.h"
#include "card.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardDashAttackState.h"
#include "cardPunchAttackState.h"
#include "cardDeathState.h"
#include "cardSmallDamagedState.h"
#include "cardHeavyDamagedState.h"
#include "cardLandState.h"

cardState * cardIdleState::inputHandle(card * card)
{
	if ((!card->_isDash && !card->_isPunchBullet) || card->numPattern == 0)
	{
		if (readyCount >= 1)
		{
			readyCount = 0;
			return new cardMoveState();
		}
	}
	return nullptr;
}

void cardIdleState::update(card * card)
{
	if (!card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = 0;
				readyCount++;
			}
			else card->_currentFrameX++;
			card->_currentFrameY = 0;
		}
	}

	else if (card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = 0;
				readyCount++;
			}
			else card->_currentFrameX++;
			card->_currentFrameY = 1;
		}
	}

	card->_isDash = false;
	card->_isPunchBullet = false;
}

void cardIdleState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_idle");
	card->_imageName = "card_idle";

	//이미지 프레임 방향 결정

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
	readyCount = 0;

	return;
}

void cardIdleState::exit(card * card)
{
}
