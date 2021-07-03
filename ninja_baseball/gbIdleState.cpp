#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbIdleState::inputHandle(greenBaseball * greenBaseball)
{
	//������
	if (greenBaseball->isCollisionAttack)
	{
		greenBaseball->timeCount++;
		if (greenBaseball->timeCount >= 60)
		{
			greenBaseball->timeCount = 0;
			return new gbAttackPunchState();
		}
	}
	else greenBaseball->timeCount = 0;

	//�±�

	if (greenBaseball->isCollisionDamaged)
	{
		greenBaseball->damagedCount++;

		return new gbDamagedState();
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
			if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				greenBaseball->setCurrentFrameX(0);
			}
			else
			{
				greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);

			}
			greenBaseball->setCurrentFrameY(1);
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
			if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
			{
				greenBaseball->setCurrentFrameX(0);
			}
			else
			{
				greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);

			}
			greenBaseball->setCurrentFrameY(0);

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
	greenBaseball->setImageName("gBaseball_idle");

	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);

	greenBaseball->timeCount = 0;

}

void gbIdleState::exit(greenBaseball * greenBaseball)
{
}
