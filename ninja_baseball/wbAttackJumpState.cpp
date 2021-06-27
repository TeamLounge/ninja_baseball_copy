#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"

wbState * wbAttackJumpState::inputHandle(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isJump)
	{
		return new wbStopState();
	}


	return nullptr;
}

void wbAttackJumpState::update(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 4)
		{
			frameCount = 0;
			if (_currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else {
				_currentFrameX++;

			}
			_currentFrameY = 1;
		}
	}
	if (whiteBaseball->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 4)
		{
			frameCount = 0;
			if (_currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else
			{
				_currentFrameX++;

			}
			_currentFrameY = 0;
		}
	}

	jump(whiteBaseball);


}

void wbAttackJumpState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_roll");
	if (!whiteBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (whiteBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

	//�ʱ�ȭ
	jumpPower =21.0f;
	gravity = 0.58f;
	
}

void wbAttackJumpState::exit(whiteBaseball * whiteBaseball)
{
}

void wbAttackJumpState::jump(whiteBaseball * whiteBaseball)
{
	if (whiteBaseball->isJump)
	{
		//�߷��ֱ�
		whiteBaseball->_whiteBaseball.y -= jumpPower;
		jumpPower -= gravity;

		//x��ǥ �����̱�
		if (!whiteBaseball->isRight)	//����
		{
			whiteBaseball->_whiteBaseball.x -= 5;
		}
		if (whiteBaseball->isRight)		//������
		{
			whiteBaseball->_whiteBaseball.x += 5;
		}

		//y��ǥ Ư����ġ������ �߷�ON
		if ((whiteBaseball->_wbShadow.rc.bottom + whiteBaseball->_wbShadow.rc.top) / 2 < whiteBaseball->_whiteBaseball.rc.bottom)
		{
			whiteBaseball->_whiteBaseball.y -= whiteBaseball->_whiteBaseball.rc.bottom - (whiteBaseball->_wbShadow.rc.bottom + whiteBaseball->_wbShadow.rc.top) / 2;
			jumpPower = 0;
			gravity = 0;
			whiteBaseball->isJump = false;
		}
	}
	
}
