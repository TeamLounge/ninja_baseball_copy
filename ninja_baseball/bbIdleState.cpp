#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"
#include "bbLandState.h"
#include "bbAttackPunchState.h"

bbState * bbIdleState::inputHandle(blueBaseball * blueBaseball)
{
	if (blueBaseball->isCollisionAttack)
	{
		timeCount++;
		if (timeCount >= 60)
		{
			timeCount = 0;
			return new bbAttackPunchState();
		}
	}
	else
	{
		timeCount = 0;
	}
	return nullptr;
}

void bbIdleState::update(blueBaseball * blueBaseball)
{
	if (!blueBaseball->isRight)		//���� ���� ������
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else {
				_currentFrameX++;

			}
			_currentFrameY = 1;
		}

		//�������� �̵�
		if (!blueBaseball->isXOverlap)
		{
			blueBaseball->_blueBaseball.x -= 0.7f;
		}
		//Ž�� ���� ��������
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}
	if (blueBaseball->isRight)			//������ ����
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == blueBaseball->_blueBaseball.img->getMaxFrameX())
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
		if (!blueBaseball->isXOverlap)
		{
			blueBaseball->_blueBaseball.x += 0.7f;
		}
		//���� ���� => ���������� ����
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x + 360, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!blueBaseball->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!blueBaseball->isDown)	//�����̸�
		{
			blueBaseball->_blueBaseball.y -= 0.7f;
		}
		if (blueBaseball->isDown)	//�Ʒ����̸�
		{
			blueBaseball->_blueBaseball.y += 0.7f;
		}
	}
}

void bbIdleState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_idle");
	if (!blueBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (blueBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

	timeCount = 0;
}

void bbIdleState::exit(blueBaseball * blueBaseball)
{
}