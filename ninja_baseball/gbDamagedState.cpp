#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbDamagedState::inputHandle(greenBaseball * greenBaseball)
{
	return nullptr;
}

void gbDamagedState::update(greenBaseball * greenBaseball)
{
	if (!greenBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
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

		//move
		if (!greenBaseball->isXOverlap)
		{
			greenBaseball->_greenBaseball.x -= 0.7f;
		}
		//���� ���� => �������� ����
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x, greenBaseball->_greenBaseball.y + 200, 250, 50);

	}
	if (greenBaseball->isRight)			//������ �ٶ󺸸�
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

void gbDamagedState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_damaged");
	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);
}

void gbDamagedState::exit(greenBaseball * greenBaseball)
{
}
