#include "stdafx.h"
#include "blueBaseball.h"
#include "bbIdleState.h"
#include "bbLandState.h"
#include "bbAttackPunchState.h"
#include "bbDamagedState.h"
#include "bbDeathState.h"

bbState * bbAttackPunchState::inputHandle(blueBaseball * blueBaseball)
{
	if (blueBaseball->getCurrentFrameX() == blueBaseball->_blueBaseball.img->getMaxFrameX())	//��ġ �������� �� ���� ����		//���߿� Ư�� ���� �� �߰������� ex) ��ġ ���Ȱ� + ������, �ȸ�����
	{
		blueBaseball->isattack = false;
		return new bbIdleState();	//����Ʈ(�ȸ�����)�� idle ����
	}

	return nullptr;
}

void bbAttackPunchState::update(blueBaseball * blueBaseball)
{
	if (!blueBaseball->isRight)		//���� ���� ������
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
			blueBaseball->setCurrentFrameY(1);
		}

		//�������� �̵�
		blueBaseball->_blueBaseball.x -= 0.7f;
		//Ž�� ���� ��������
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}
	if (blueBaseball->isRight)			//������ ����
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
		blueBaseball->_blueBaseball.x += 0.7f;
		//���� ���� => ���������� ����
		blueBaseball->_blueBaseball.rcAttackRange = RectMakeCenter(blueBaseball->_blueBaseball.x + 360, blueBaseball->_blueBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!blueBaseball->isDown)	//�����̸�
	{
		blueBaseball->_blueBaseball.y -= 0.7f;
	}
	if (blueBaseball->isDown)	//�Ʒ����̸�
	{
		blueBaseball->_blueBaseball.y += 0.7f;
	}
}

void bbAttackPunchState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->isattack = true;
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_punch");
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

void bbAttackPunchState::exit(blueBaseball * blueBaseball)
{
}
