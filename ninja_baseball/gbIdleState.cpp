#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"

gbState * gbIdleState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->isCollisionAttack)
	{
		timeCount++;
		if (timeCount >= 60)
		{
			timeCount = 0;
			return new gbAttackPunchState();
		}
	}
	else
	{
		timeCount = 0;
	}
	return nullptr;
}

void gbIdleState::update(greenBaseball * greenBaseball)
{
	if (!greenBaseball->isRight)		//���� ���� ������
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else {
				_currentFrameX++;

			}
			_currentFrameY = 1;
		}

		//�������� �̵�
		if (!greenBaseball->isXOverlap)
		{
			greenBaseball->_greenBaseball.x -= 0.7f;
		}
		//Ž�� ���� ��������
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}
	if (greenBaseball->isRight)			//������ ����
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == greenBaseball->_greenBaseball.img->getMaxFrameX())
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
		if (!greenBaseball->isXOverlap)
		{
			greenBaseball->_greenBaseball.x += 0.7f;
		}
		//���� ���� => ���������� ����
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x + 360, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!greenBaseball->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!greenBaseball->isDown)	//�����̸�
		{
			greenBaseball->_greenBaseball.y -= 0.7f;
		}
		if (greenBaseball->isDown)	//�Ʒ����̸�
		{
			greenBaseball->_greenBaseball.y += 0.7f;
		}
	}
}

void gbIdleState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_idle");
	if (!greenBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (greenBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

	timeCount = 0;
}

void gbIdleState::exit(greenBaseball * greenBaseball)
{
}
