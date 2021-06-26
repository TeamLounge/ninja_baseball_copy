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
		if (_currentFrameX == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else {
			_currentFrameX++;

		}
		_currentFrameY = 1;
	}

	wbMove(whiteBaseball);

}

void wbRollState::enter(whiteBaseball * whiteBaseball)	//init!!!!
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_roll");
	_currentFrameX = 0;
	_currentFrameY = 1;





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
