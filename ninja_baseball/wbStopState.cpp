#include "stdafx.h"
#include "whiteBaseball.h"
#include "wbStopState.h"
#include "wbRollState.h"
#include "wbIdleState.h"
#include "wbAttackJumpState.h"
#include "wbAttackPunchState.h"

wbState * wbStopState::inputHandle(whiteBaseball * whiteBaseball)
{
	if (speed <= friction)
	{
		return new wbIdleState();
	}

	return nullptr;
}

void wbStopState::update(whiteBaseball * whiteBaseball)
{

	if (!whiteBaseball->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 4)
		{
			frameCount = 0;
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameY(whiteBaseball->_whiteBaseball.img->getMaxFrameX());
			}
			else 
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);


			}
			whiteBaseball->setCurrentFrameY(1);
		}
	}
	if (whiteBaseball->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 4)
		{
			frameCount = 0;
			if (whiteBaseball->getCurrentFrameX() == whiteBaseball->_whiteBaseball.img->getMaxFrameX())
			{
				whiteBaseball->setCurrentFrameY(whiteBaseball->_whiteBaseball.img->getMaxFrameX());
			}
			else 
			{
				whiteBaseball->setCurrentFrameX(whiteBaseball->getCurrentFrameX() + 1);

			}
			whiteBaseball->setCurrentFrameY(0);
		}
	}

	//�ڷ� ���� �и�
	if (speed > friction)
	{
		if (whiteBaseball->isRight)
		{
			whiteBaseball->_whiteBaseball.x -= speed;
			speed -= friction;

		}
		if (!whiteBaseball->isRight)
		{
			whiteBaseball->_whiteBaseball.x += speed;
			speed -= friction;
		}
	}



}
void wbStopState::enter(whiteBaseball * whiteBaseball)
{
	whiteBaseball->_whiteBaseball.img = IMAGEMANAGER->findImage("wBaseball_stop");
	if (!whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(1);
	}
	if (whiteBaseball->isRight)
	{
		whiteBaseball->setCurrentFrameY(0);
	}
	whiteBaseball->setCurrentFrameX(0);

	speed = 3.0f;
	friction = 0.07f;

	whiteBaseball->setImageName("wBaseball_stop");
}

void wbStopState::exit(whiteBaseball * whiteBaseball)
{
}
