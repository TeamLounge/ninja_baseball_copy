#include "stdafx.h"
#include "card.h"
#include "cardPunchAttackState.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"

cardState * cardPunchAttackState::inputHandle(card * card)
{
	return S_OK;
}

void cardPunchAttackState::update(card * card)
{
	if (!card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_card.img->getFrameX() == card->_card.img->getMaxFrameX())
			{
				card->_card.img->setFrameX(card->_card.img->getMaxFrameX());
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
				card->_card.img->setFrameX(card->_card.img->getMaxFrameX());
			}
			card->_card.img->setFrameX(card->_card.img->getFrameX() + 1);
			card->_card.img->setFrameY(1);
		}
	}
}

void cardPunchAttackState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_attack");

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
}

void cardPunchAttackState::exit(card * card)
{
}
