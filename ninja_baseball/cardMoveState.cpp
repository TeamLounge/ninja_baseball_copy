#include "stdafx.h"
#include "card.h"
#include "cardMoveState.h"
#include "cardIdleState.h"
#include "cardDashAttackState.h"
#include "cardPunchAttackState.h"
#include "cardDeathState.h"
#include "cardSmallDamagedState.h"
#include "cardHeavyDamagedState.h"
#include "time.h"

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
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = 0;
			}
			else card->_currentFrameX++;
			card->_currentFrameY = 0;
		}
	}

	else if (card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 10)
		{
			frameCount = 0;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = 0;
			}
			else card->_currentFrameX++;
			card->_currentFrameY = 1;
		}
	}

	isSide(card);
	move(card);
}

void cardMoveState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_move");
	card->_imageName = "card_move";

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

	if (card->_card.rc.top <= 200)
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
		if (card->_card.rc.right < BACKGROUNDX) card->_card.x += 3.5f;
	}

	if (!card->_isLeft)
	{
		if (card->_card.rc.left > BACKGROUNDX - CAMERAX) card->_card.x -= 3.5f;
	}

	if (card->_isUpper && !card->_isTopWall && !card->_isBottomWall)
	{
		if (card->_card.rc.top > 200) card->_card.y -= 2.5f;
	}

	if (!card->_isUpper && !card->_isTopWall && !card->_isBottomWall)
	{
		if (card->_card.rc.bottom < WINSIZEY) card->_card.y += 2.5f;
	}

	if (card->_isTopWall && !card->_isBottomWall) card->_card.y += 2.7f;
	if (!card->_isTopWall && card->_isBottomWall) card->_card.y -= 2.7f;
}
