#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"
#include "bbAttackPunchState.h"
#include "bbDamagedState.h"
#include "bbDeathState.h"




bbState * bbDamagedState::inputHandle(blueBaseball * blueBaseball)
{
	if (blueBaseball->isDeath)
	{
		return new bbDeathState();
	}
	return nullptr;
}

void bbDamagedState::update(blueBaseball * blueBaseball)
{

	if (!blueBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				blueBaseball->setCurrentFrameX(0);
			}
			else
			{
				blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);

			}
			blueBaseball->setCurrentFrameY(1);
		}

		//move
		if (!blueBaseball->isXOverlap)
		{
			blueBaseball->_blueBaseball.x -= 0.7f;
		}
		//���� ���� => �������� ����
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x, blueBaseball->_blueBaseball.y + 200, 250, 50);

	}
	if (blueBaseball->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())
			{
				blueBaseball->setCurrentFrameX(0);
			}
			else
			{
				blueBaseball->setCurrentFrameX(blueBaseball->getCurrentFrameX() + 1);

			}
			blueBaseball->setCurrentFrameY(0);

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

void bbDamagedState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_damaged");
	blueBaseball->setImageName("bBaseball_damaged");

	
	frameCount = 0;


	if (!blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(1);
	}
	if (blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(0);
	}
	blueBaseball->setCurrentFrameX(0);
}

void bbDamagedState::exit(blueBaseball * blueBaseball)
{
}
