#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"


gloveState * gloveJumpState::inputHandle(glove * glove)
{
	if (!glove->isJump && glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())		//������ �����ϸ� move���·�
	{
		glove->isJumpState = false;

		return new gloveMoveState();		//new!!!!!!!!!new!!!!!!!!!new!!!!!!!!!!!����!!!!!!!!!!!
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
		if (!glove->isLand && glove->getCurrentFrameX() < 1)		//�� ���� �ƴ� ��
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

	//�Ϻ� ������ �����̿�
	delayCnt = 0;

	//���� �ʱ�ȭ
	jumpPower = 21.0f;		//�¾�� �� �ƿ� ī�޶� �ۿ��� ������ ����.
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

		//x��ǥ �����̱�
		if (!glove->isRight)		//����
		{
			glove->_glove.x -= 5;
		}
		if (glove->isRight)		//������
		{
			glove->_glove.x += 5;
		}

		//y��ǥ Ư����ġ������ �߷�ON
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
