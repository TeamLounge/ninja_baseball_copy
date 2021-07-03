#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"
#include "ybDamagedState.h"
#include "ybDeathState.h"

ybState * ybIdleState::inputHandle(yellowBaseball * yellowBaseball)
{
	//������
	if (yellowBaseball->isCollisionAttack)
	{
		yellowBaseball->timeCount++;
		if (yellowBaseball->timeCount >= 60)
		{
			yellowBaseball->timeCount = 0;
			return new ybAttackPunchState();
		}
	}
	else yellowBaseball->timeCount = 0;

	//�±�

	if (yellowBaseball->isCollisionDamaged)
	{
		yellowBaseball->damagedCount++;
		
		return new ybDamagedState();
	}
	return nullptr;
}

void ybIdleState::update(yellowBaseball * yellowBaseball)
{

	if (!yellowBaseball->isRight)		//���� ���� ������
	{
		frameCount++;
		if (frameCount >= 15)
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

		//�������� �̵�
		if (!yellowBaseball->isXOverlap)
		{
			yellowBaseball->_yellowBaseball.x -= 0.7f;
		}
		//Ž�� ���� ��������
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}
	if (yellowBaseball->isRight)			//������ ����
	{
		frameCount++;
		if (frameCount >= 15)
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

void ybIdleState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_idle");
	yellowBaseball->setImageName("yBaseball_idle");

	if (!yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(1);
	}
	if (yellowBaseball->isRight)
	{
		yellowBaseball->setCurrentFrameY(0);
	}
	yellowBaseball->setCurrentFrameX(0);

	yellowBaseball->timeCount = 0;
}

void ybIdleState::exit(yellowBaseball * yellowBaseball)
{
}
