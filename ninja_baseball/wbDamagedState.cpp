#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"
#include "wbDamagedState.h"
#include "wbDeathState.h"

wbState * wbDamagedState::inputHandle(whiteBaseball * whiteBaseball)
{
	return nullptr;
}

void wbDamagedState::update(whiteBaseball * whiteBaseball)
{
	if (!whiteBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameX(0);
			}
			else
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);

			}
			whiteBaseball->setCurrentFrameY(1);
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
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameX(0);
			}
			else
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);

			}
			whiteBaseball->setCurrentFrameY(0);

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

void wbDamagedState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball-> _whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_damaged");
	if (!whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(1);
	}
	if (whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(0);
	}
	whiteBaseball->setCurrentFrameX(0);

}

void wbDamagedState::exit(whiteBaseball * whiteBaseball)
{
}