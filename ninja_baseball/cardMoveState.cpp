#include "stdafx.h"
#include "card.h"
#include "cardMoveState.h"
#include "cardIdleState.h"
#include "cardDashAttackState.h"
#include "cardPunchAttackState.h"

cardState * cardMoveState::inputHandle(card * card)
{
	if (card->_isDash)
	{
		return new cardDashAttackState();
	}

	if (card->_isPunchBullet)
	{
		return new cardPunchAttackState();
	}
	return nullptr;
}

void cardMoveState::update(card * card)
{
	if (!card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 10)
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
		if (frameCount >= 10)
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

	isSide(card);
	move(card);
}

void cardMoveState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_move");

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

void cardMoveState::exit(card * card)
{
}


//////////////////////////////////////////
//    카드 벽에 부딪혔을때 반대움직임     //
/////////////////////////////////////////
void cardMoveState::isSide(card* card)
{
	if (card->_card.rc.bottom >= WINSIZEY)
	{
		card->_isBottomWall = true;
		card->_isTopWall = false;
	}

	if (card->_card.rc.top <= 0)
	{
		card->_isBottomWall = false;
		card->_isTopWall = true;
	}
}

//////////////////////////////////////////
//         카드 범위내 움직임            //
/////////////////////////////////////////
void cardMoveState::move(card* card)
{
	if (card->_isLeft)
	{
		if (card->_card.rc.right < WINSIZEX) card->_card.x += 5;
	}

	if (!card->_isLeft)
	{
		if (card->_card.rc.left > 0) card->_card.x -= 5;
	}

	if (card->_isUpper && !card->_isTopWall && !card->_isBottomWall)
	{
		if (card->_card.rc.top > 0) card->_card.y -= 3;
	}

	if (!card->_isUpper && !card->_isTopWall && !card->_isBottomWall)
	{
		if (card->_card.rc.bottom < WINSIZEY) card->_card.y += 3;
	}

	if (card->_isTopWall && !card->_isBottomWall) card->_card.y += 3;
	if (!card->_isTopWall && card->_isBottomWall) card->_card.y -= 3;
}
