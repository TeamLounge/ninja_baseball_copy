#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"

batState * batMoveState::inputHandle(bat * bat)
{
	//���� �� ���� �ð� ������.. ���� ����
	timeCount++;
	if (timeCount >= 150)
	{
		return new batIdleState();
	}

	return nullptr;
}

void batMoveState::update(bat * bat)
{
	if (!bat->isRight)	//���� ����
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
			bat->_bat.x -= 1.2f;
		}
		//���� ���� => �������� ����
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 100, bat->_bat.y + 200, 250, 50);
	}
	if (bat->isRight)	//������ ����
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
			bat->_bat.x += 1.2f;
		}
		//���� ���� => �������� ����
		bat->_bat.rcAttackRange = RectMakeCenter(bat->_bat.x + 520, bat->_bat.y + 200, 250, 50);
	}
	//move (up, down)
	if (!bat->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!bat->isDown)	//�����̸�
		{
			bat->_bat.y -= 1.2f;
		}
		if (bat->isDown)	//�Ʒ����̸�
		{
			bat->_bat.y += 1.2f;
		}
	}
}

void batMoveState::enter(bat * bat)
{
	bat->_bat.img = IMAGEMANAGER->findImage("fBat_move");			//sBat, tBat���� ��� ������ұ�..
	if (!bat->isRight)
	{
		bat->setCurrentFrameY(1);
	}
	if (bat->isRight)
	{
		bat->setCurrentFrameY(0);
	}
	bat->setCurrentFrameX(0);

	//�ʱ� �������ڸ��� �ٷ� timeCount ����
	timeCount++;

}

void batMoveState::exit(bat * bat)
{
}
