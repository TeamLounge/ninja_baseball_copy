#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveAttackTongueState::inputHandle(glove * glove)
{
	if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())		//이미지 한번만 돌고
	{

		glove->isAttackTongueState = false;		//어택 상태 해제


		return new gloveMoveState();
	}
	if (glove->isDeath)
	{
		return new gloveDeathState();
	}
	return nullptr;
}

void gloveAttackTongueState::update(glove * glove)
{
	//frame
	frameCount++;
	if (frameCount >= 5)
	{
		frameCount = 0;
		if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())			//프레임 한 바퀴만 돌아
		{
			glove->setCurrentFrameX(glove->_glove.img->getMaxFrameX());
		}
		else
		{
			glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);
		}
	}
}

void gloveAttackTongueState::enter(glove * glove)
{
	glove->_glove.img = IMAGEMANAGER->findImage("glove_attackTongue");
	glove->setImageName("glove_attackTongue");

	if (!glove->isRight)
	{
		glove->setCurrentFrameY(1);
	}
	if (glove->isRight)
	{
		glove->setCurrentFrameY(0);
	}
	glove->setCurrentFrameX(0);

	glove->isAttackTongueState = true;
	glove->isattack = true;
}

void gloveAttackTongueState::exit(glove * glove)
{
}
