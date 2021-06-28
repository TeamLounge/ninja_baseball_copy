#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbRollState.h"
#include "wbStopState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"

wbState * wbRollState::inputHandle(whiteBaseball * whiteBaseball)		//���¿� ���� ����� �߰�����. ���³��� �Դٰ��� �ۿ�
{
	//Roll���¿���!!!!! �浹 �� Stop����
	RECT temp;
	if (IntersectRect(&temp, &whiteBaseball->_whiteBaseball.rc, &whiteBaseball->_whiteBaseball.rcStop))	
	{
		return new wbStopState();
	}
	return nullptr;
}

void wbRollState::update(whiteBaseball * whiteBaseball)
{
	frameCount++;
	if (frameCount >= 8)
	{
		frameCount = 0;
		if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
		{
			whiteBaseball->setCurrentFrameX(0);
		}
		else {
			whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);
		}
		whiteBaseball->setCurrentFrameY(1);
	}

	wbMove(whiteBaseball);

}

void wbRollState::enter(whiteBaseball * whiteBaseball)	//init!!!!
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_roll");
	whiteBaseball->setCurrentFrameX(0);
	whiteBaseball->setCurrentFrameY(1);

	whiteBaseball->setImageName("wBaseball_roll");



	return;
}

void wbRollState::exit(whiteBaseball * whiteBaseball)
{
}

void wbRollState::wbMove(whiteBaseball * whiteBaseball)
{
	RECT temp;

	if (!(IntersectRect(&temp, &whiteBaseball->_whiteBaseball.rc, &whiteBaseball->_whiteBaseball.rcStop)))		//���� �浹��
	{
		whiteBaseball->_whiteBaseball.x -= speed;
	}
}
