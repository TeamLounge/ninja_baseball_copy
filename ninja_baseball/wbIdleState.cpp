#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbRollState.h"
#include "wbStopState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"

wbState * wbIdleState::inputHandle(whiteBaseball * whiteBaseball)
{
	if (whiteBaseball->isCollisionAttack)
	{
		timeCount++;
		if (timeCount >= 70)
		{
			timeCount = 0;
			return new wbAttackPunchState();
		}
	}
	else
	{	
		timeCount = 0;
	}
	return nullptr;
}

void wbIdleState::update(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
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

		//move
		if (!whiteBaseball->isXOverlap)
		{
			whiteBaseball->_whiteBaseball.x -= 0.7f;
		}
		//���� ���� => �������� ����
		whiteBaseball->_whiteBaseball.rcAttackRange = RectMakeCenter(whiteBaseball->_whiteBaseball.x, whiteBaseball->_whiteBaseball.y + 200, 250, 50);

	}
	if (whiteBaseball->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if ( _currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else 
			{
				_currentFrameX++;

			}
			_currentFrameY = 0;

		}
		//move
		if (!whiteBaseball->isXOverlap)
		{
			whiteBaseball->_whiteBaseball.x += 0.7f;
		}
		//���� ���� => ���������� ����
		whiteBaseball->_whiteBaseball.rcAttackRange = RectMakeCenter(whiteBaseball->_whiteBaseball.x + 360, whiteBaseball->_whiteBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!whiteBaseball->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!whiteBaseball->isDown)	//�����̸�
		{
			whiteBaseball->_whiteBaseball.y -= 0.7f;
		}
		if (whiteBaseball->isDown)	//�Ʒ����̸�
		{
			whiteBaseball->_whiteBaseball.y += 0.7f;
		}
	}
	


	

}

void wbIdleState::enter(whiteBaseball * whiteBaseball)		//init
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_idle");
	if (!whiteBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (whiteBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

	timeCount = 0;

}

void wbIdleState::exit(whiteBaseball * whiteBaseball)
{
}
