#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"
#include "batDeathState.h"

batState * batDamagedState::inputHandle(bat * bat)
{
	


	return nullptr;
}

void batDamagedState::update(bat * bat)
{
	if (!bat->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())
			{
				bat->setCurrentFrameX(0);
			}
			else
			{
				bat->setCurrentFrameX(bat->getCurrentFrameX() + 1);

			}
			bat->setCurrentFrameY(1);
		}

		//move
		if (!bat->isXOverlap)
		{
			bat->_bat.x -= 0.7f;
		}
		//���� ���� => �������� ����
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x, bat->_bat.y + 200, 250, 50);

	}
	if (bat->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (bat->getCurrentFrameX() == bat->_bat.img->getMaxFrameX())
			{
				bat->setCurrentFrameX(0);
			}
			else
			{
				bat->setCurrentFrameX(bat->getCurrentFrameX() + 1);

			}
			bat->setCurrentFrameY(0);

		}
		//move
		if (!bat->isXOverlap)
		{
			bat->_bat.x += 0.7f;
		}
		//���� ���� => ���������� ����
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 360, bat->_bat.y + 200, 250, 50);
	}

	//move (up, down)
	if (!bat->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!bat->isDown)	//�����̸�
		{
			bat->_bat.y -= 0.7f;
		}
		if (bat->isDown)	//�Ʒ����̸�
		{
			bat->_bat.y += 0.7f;
		}
	}
}

void batDamagedState::enter(bat * bat)
{
	bat->_bat.img = IMAGEMANAGER->findImage("fBat_damaged");
	if (!bat->isRight)
	{
		bat->setCurrentFrameY(1);
	}
	if (bat->isRight)
	{
		bat->setCurrentFrameY(0);
	}
	bat->setCurrentFrameX(0);

}

void batDamagedState::exit(bat * bat)
{
}
