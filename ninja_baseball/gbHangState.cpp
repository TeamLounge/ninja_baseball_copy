#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbHangState::inputHandle(greenBaseball * greenBaseball)
{
	if (greenBaseball->_greenBaseball.rc.bottom >= greenBaseball->_greenBaseball.rcStop.top)
	{
		return new gbLandState();
	}
	return nullptr;
}

void gbHangState::update(greenBaseball * greenBaseball)
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

	gbStart(greenBaseball);
}

void gbHangState::enter(greenBaseball * greenBaseball)
{
	//�÷��̾ Ư�� ��ǥ�� ���� �� ��, ���͹� �ְ� ����
	if (true)
	{

	}
	greenBaseball->_greenBaseball.img = IMAGEMANAGER->findImage("gBaseball_hang");
	greenBaseball->setImageName("gBaseball_hang");

	greenBaseball->setCurrentFrameX(0);
	greenBaseball->setCurrentFrameY(1);

	//greenBaseball->isattack = false;	//�������� ������ �� �°� ���⼭ ������
}

void gbHangState::exit(greenBaseball * greenBaseball)
{
}

void gbHangState::gbStart(greenBaseball * greenBaseball)
{
	RECT temp;

	if (!(IntersectRect(&temp, &greenBaseball->_greenBaseball.rc, &greenBaseball->_greenBaseball.rcStop)))		//���� �浹��
	{
		greenBaseball->_greenBaseball.y += speed;
	}
}
