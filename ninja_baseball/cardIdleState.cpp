#include "stdafx.h"
#include "card.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardDashAttackState.h"
#include "cardPunchAttackState.h"

cardState * cardIdleState::inputHandle(card * card)
{
	if (!card->_isDash && !card->_isPunchBullet)
	{
		return new cardMoveState();
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
			if (card->_card.img->getFrameX() == card->_card.img->getMaxFrameX())
			{
				card->_card.img->setFrameX(-1);
			}
			card->_card.img->setFrameX(card->_card.img->getFrameX() + 1);
			card->_card.img->setFrameY(0);
		}
	}

	else if (card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_card.img->getFrameX() == card->_card.img->getMaxFrameX())
			{
				card->_card.img->setFrameX(-1);
			}
			card->_card.img->setFrameX(card->_card.img->getFrameX() + 1);
			card->_card.img->setFrameY(1);
		}
	}
}

void cardIdleState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_idle");

	//이미지 프레임 방향 결정

	if (!card->_isLeft)
	{
		card->_card.img->setFrameX(0);
		card->_card.img->setFrameY(0);
	}

	if (card->_isLeft)
	{
		card->_card.img->setFrameX(0);
		card->_card.img->setFrameY(1);
	}


	return;
}

void cardIdleState::exit(card * card)
{
}
