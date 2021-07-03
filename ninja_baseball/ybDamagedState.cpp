#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"
#include "ybDamagedState.h"
#include "ybDeathState.h"

ybState * ybDamagedState::inputHandle(yellowBaseball * yellowBaseball)
{
	if (yellowBaseball->damagedCount == 5)
	{
		yellowBaseball->damagedCount = 0;
		return new ybDeathState();
	}
	if (yellowBaseball->damagedCount < 5 && yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
	{
		yellowBaseball->setCurrentFrameX(0);
		yellowBaseball->isCollisionDamaged = false;
		return new ybIdleState();
	}
	return nullptr;
}

void ybDamagedState::update(yellowBaseball * yellowBaseball)
{
	if (!yellowBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 10)
		{
			frameCount = 0;
			if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				yellowBaseball->setCurrentFrameX(0);
			}
			else
			{
				yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);

			}
			yellowBaseball->setCurrentFrameY(1);
		}

		//move
		if (!yellowBaseball->isXOverlap)
		{
			yellowBaseball->_yellowBaseball.x -= 0.7f;
		}
		//���� ���� => �������� ����
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x, yellowBaseball->_yellowBaseball.y + 200, 250, 50);

	}
	if (yellowBaseball->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 10)
		{
			frameCount = 0;
			if (yellowBaseball->getCurrentFrameX() == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				yellowBaseball->setCurrentFrameX(0);
			}
			else
			{
				yellowBaseball->setCurrentFrameX(yellowBaseball->getCurrentFrameX() + 1);

			}
			yellowBaseball->setCurrentFrameY(0);

		}
		//move
		if (!yellowBaseball->isXOverlap)
		{
			yellowBaseball->_yellowBaseball.x += 0.7f;
		}
		//���� ���� => ���������� ����
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x + 360, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!yellowBaseball->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!yellowBaseball->isDown)	//�����̸�
		{
			yellowBaseball->_yellowBaseball.y -= 0.7f;
		}
		if (yellowBaseball->isDown)	//�Ʒ����̸�
		{
			yellowBaseball->_yellowBaseball.y += 0.7f;
		}
	}
}

void ybDamagedState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_damaged");
	yellowBaseball->setImageName("yBaseball_damaged");

	if (!yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(1);
	}
	if (yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(0);
	}
	yellowBaseball->setCurrentFrameX(0);
}

void ybDamagedState::exit(yellowBaseball * yellowBaseball)
{
}
