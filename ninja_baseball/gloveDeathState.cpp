#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveDeathState::inputHandle(glove * glove)
{
	//���� ����
	//���� �̹��� ���ķ���
	//���� deathRing ����
	return nullptr;
}

void gloveDeathState::update(glove * glove)
{
	frameCount++;
	if (frameCount >= 15)		//�� �� ��� �ְ� ����
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

void gloveDeathState::enter(glove * glove)
{
	glove->_glove.img = IMAGEMANAGER->findImage("glove_death");

	if (!glove->isRight)
	{
		glove->setCurrentFrameY(1);
	}
	if (glove->isRight)
	{
		glove->setCurrentFrameY(0);
	}
	glove->setCurrentFrameX(0);


	glove->isCollisionDamaged = true;
	glove->isDeath = false;
}

void gloveDeathState::exit(glove * glove)
{
}
