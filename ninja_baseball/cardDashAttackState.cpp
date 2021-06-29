#include "stdafx.h"
#include "card.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardPunchAttackState.h"

cardState * cardDashAttackState::inputHandle(card * card)
{
	if (_atkCount >= 1)
	{
		card->_isDash = false;
		return new cardIdleState();
	}

	return nullptr;
}

void cardDashAttackState::update(card * card)
{
	if (!card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = card->_card.img->getMaxFrameX();
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
			frameCount++;
			if (frameCount >= 25)
			{
				frameCount = 0;
				if (card->_currentFrameX == card->_card.img->getMaxFrameX())
				{
					card->_currentFrameX = card->_card.img->getMaxFrameX();
				}
				else card->_currentFrameX++;
				card->_currentFrameY = 1;
			}
		}
	}

	dashMove(card);
}

void cardDashAttackState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_dashAttack");

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

	//공격 카운트 확인용
	_atkCount = 0;
	//대시 가속도
	_accel = 0.55;
	//대시 속도
	_speed = 5;
	//오른쪽 대쉬하기
	_isRightDash = false;
	//왼쪽 대쉬하기
	_isLeftDash = false;
	//오른쪽 벽에 닿았는지
	_isRightWall = false;
	//왼쪽 벽에 닿았는지
	_isLeftWall = false;
}

void cardDashAttackState::exit(card * card)
{
}

void cardDashAttackState::dashMove(card* card)
{
	if (!card->_isLeft && card->_card.img->getFrameX() == 0)
	{
		_isRightDash = true;
	}

	if (card->_isLeft && card->_card.img->getFrameX() == 0)
	{
		_isLeftDash = true;
	}

	if (_isRightDash && card->_card.img->getFrameX() > 0 &&
		card->_card.rc.right >= WINSIZEX)
	{
		_isRightWall = true;
	}

	if (_isLeftDash && card->_card.img->getFrameX() > 0 &&
		card->_card.rc.left <= 0)
	{
		_isLeftWall = true;
	}

	if (_isRightDash && !_isRightWall &&
		card->_card.img->getFrameX() > 0)
	{
		card->_card.x += _speed;
		_speed += _accel;
	}

	if (_isLeftDash && !_isLeftWall &&
		card->_card.img->getFrameX() > 0)
	{
		card->_card.x -= _speed;
		_speed += _accel;
	}

	if (_isRightWall || _isLeftWall)
	{
		_atkCount++;
	}
}

