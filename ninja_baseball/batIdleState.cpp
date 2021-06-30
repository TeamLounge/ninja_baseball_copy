#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"

batState * batIdleState::inputHandle(bat * bat)
{
	if (bat->isCollisionAttack)		//�浹������ attack��!
	{
		//bat->isCollisionAttack = true;
		
		return new batAttackState();
	}
		

	return nullptr;
}

void batIdleState::update(bat * bat)
{
	if (!bat->isRight)
	{
		frameCount++;
		if (frameCount >= 8)
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
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 100, bat->_bat.y + 200, 250, 50);
	}

	if (bat->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 8)
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
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 460, bat->_bat.y + 200, 250, 50);
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

void batIdleState::enter(bat * bat)
{
	bat->_bat.img = IMAGEMANAGER->findImage("fBat_idle");
	if (!bat->isRight)
	{
		bat->setCurrentFrameY(1);
	}
	if (bat->isRight)
	{
		bat->setCurrentFrameY(0);
	}
	bat->setCurrentFrameX(0);

	timeCount = 0;
}

void batIdleState::exit(bat * bat)
{
}
