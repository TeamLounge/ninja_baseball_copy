#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"


gloveState * gloveJumpState::inputHandle(glove * glove)
{
	if (!glove->isJump && glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())		//떨어져 도착하면 move상태로
	{
		glove->isJumpState = false;

		return new gloveMoveState();		//new!!!!!!!!!new!!!!!!!!!new!!!!!!!!!!!적어!!!!!!!!!!!
	}
	if (glove->isDeath)
	{
		return new gloveDeathState();
	}
	return nullptr;
}

void gloveJumpState::update(glove * glove)
{
	frameCount++;
	if (frameCount >= 10)
	{
		frameCount = 0;
		if (!glove->isLand && glove->getCurrentFrameX() < 1)		//땅 도착 아닐 때
		{
			glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);
		}

		if (glove->isLand && glove->getCurrentFrameX() == 1)
		{
			glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);
		}

		if (glove->getCurrentFrameX() == 2)
		{
			delayCnt++;
		}

		if (delayCnt >= 4) glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);

		glove->setCurrentFrameY(1);
	}

	jumpAppear(glove);
	
}

void gloveJumpState::enter(glove * glove)
{
	glove->_glove.img = IMAGEMANAGER->findImage("glove_jump");
	glove->setCurrentFrameX(0);
	glove->setCurrentFrameY(1);

	//glove->isJump = true;
	glove->isJumpState = true;

	//일부 프레임 딜레이용
	delayCnt = 0;

	//점프 초기화
	jumpPower = 21.0f;		//태어나는 걸 아예 카메라 밖에서 나오게 하자.
	gravity = 0.58f;
}

void gloveJumpState::exit(glove * glove)
{
}

void gloveJumpState::jumpAppear(glove* glove)
{
	if (glove->isJump)
	{
		glove->_glove.y -= jumpPower;
		jumpPower -= gravity;

		//x좌표 움직이기
		if (!glove->isRight)		//왼쪽
		{
			glove->_glove.x -= 5;
		}
		if (glove->isRight)		//오른쪽
		{
			glove->_glove.x += 5;
		}

		//y좌표 특정위치까지만 중력ON
		if ((glove->_gloveShadow.rc.bottom + glove->_gloveShadow.rc.top) / 2 < glove->_glove.rc.bottom)
		{
			glove->_glove.y -= glove->_glove.rc.bottom - (glove->_gloveShadow.rc.bottom + glove->_gloveShadow.rc.top) / 2;
			jumpPower = 0;
			gravity = 0;
			glove->isJump = false;
			glove->isLand = true;
		}
	}
}
