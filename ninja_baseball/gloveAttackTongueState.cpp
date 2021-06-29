#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveAttackTongueState::inputHandle(glove * glove)
{
	if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
	{
		glove->isAttackTongueState = false;

		return new gloveMoveState();
	}
	return nullptr;
}

void gloveAttackTongueState::update(glove * glove)
{
	//frame
	frameCount++;
	if (frameCount >= 15)
	{
		frameCount = 0;
		if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
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
}

void gloveAttackTongueState::exit(glove * glove)
{
}
