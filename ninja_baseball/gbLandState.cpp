#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbLandState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())	//�׸��ڶ� �浹�ϸ� idle��
	{
		return new gbIdleState();
	}
	return nullptr;
}

void gbLandState::update(greenBaseball * greenBaseball)
{
	frameCount++;
	if (frameCount >= 3)
	{
		frameCount = 0;
		if (greenBaseball->getCurrentFrameX() == greenBaseball->_greenBaseball.img->getMaxFrameX())
		{
			greenBaseball->setCurrentFrameX(0);
		}
		else {
			greenBaseball->setCurrentFrameX(greenBaseball->getCurrentFrameX() + 1);
		}
		greenBaseball->setCurrentFrameY(1);
	}

	gbJump(greenBaseball);
}

void gbLandState::enter(greenBaseball * greenBaseball)
{
	greenBaseball->isLand = true;	//���������� �� �� �׸��� ������
	greenBaseball->isJump = true;

	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_roll");
	greenBaseball->setImageName("gBaseball_roll");

	if (!greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(1);
	}
	if (greenBaseball->isRight)
	{
		greenBaseball->setCurrentFrameY(0);
	}
	greenBaseball->setCurrentFrameX(0);

	//�ʱ�ȭ
	jumpPower = 19.0f;
	gravity = 1.28f;
}

void gbLandState::exit(greenBaseball * greenBaseball)
{
}

void gbLandState::gbJump(greenBaseball * greenBaseball)
{
	if (greenBaseball->isJump)
	{
		//�߷��ֱ�
		greenBaseball->_greenBaseball.y -= jumpPower;
		jumpPower -= gravity;

		//x��ǥ �����̱�
				//������
		greenBaseball->_greenBaseball.x += 5;

		//y��ǥ Ư����ġ������ �߷�ON
		if ((greenBaseball->_gbShadow.rc.bottom + greenBaseball->_gbShadow.rc.top) / 2 < greenBaseball->_greenBaseball.rc.bottom) //�׸��� �Ѿ��
		{
			greenBaseball->_greenBaseball.y -= greenBaseball->_greenBaseball.rc.bottom - (greenBaseball->_gbShadow.rc.bottom + greenBaseball->_gbShadow.rc.top) / 2;	//����ŭ ���ش�.
			jumpPower = 0;
			gravity = 0;
			greenBaseball->isJump = false;
		}
	}
}
