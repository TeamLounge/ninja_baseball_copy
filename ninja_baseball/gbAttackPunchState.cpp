#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbAttackPunchState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())	//��ġ �������� �� ���� ����		//���߿� Ư�� ���� �� �߰������� ex) ��ġ ���Ȱ� + ������, �ȸ�����
	{
		greenBaseball->isattack = false;
		return new gbIdleState();	//����Ʈ(�ȸ�����)�� idle ����
	}

	if (greenBaseball->isDeath)
	{
		return new gbDeathState();
	}

	return nullptr;
}

void gbAttackPunchState::update(greenBaseball * greenBaseball)
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
		greenBaseball->_greenBaseball.x -= 0.7f;
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
		greenBaseball->_greenBaseball.x += 0.7f;
		//���� ���� => ���������� ����
		greenBaseball->_greenBaseball.rcAttackRange = RectMakeCenter(greenBaseball->_greenBaseball.x + 360, greenBaseball->_greenBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!greenBaseball->isDown)	//�����̸�
	{
		greenBaseball->_greenBaseball.y -= 0.7f;
	}
	if (greenBaseball->isDown)	//�Ʒ����̸�
	{
		greenBaseball->_greenBaseball.y += 0.7f;
	}
}

void gbAttackPunchState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->isattack = true;
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_punch");
	greenBaseball->setImageName("gBaseball_punch");

	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);

	greenBaseball->isattack = true;
}

void gbAttackPunchState::exit(greenBaseball * greenBaseball)
{
}
