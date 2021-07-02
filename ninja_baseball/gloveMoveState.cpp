#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveMoveState::inputHandle(glove * glove)
{	
	//glove�� ������
	if (glove->isCollisionAttack)
	{
		glove->timeCount++;
		if (glove->timeCount >= 65)
		{
			glove->timeCount = 0;
			return new gloveAttackTongueState();		//�׷� ������ ���� ��� �����ٰŰ�, �ൿ�� player�ʿ��� �ϰ�
		}
	}
	else glove->timeCount = 0;

	//glove�� ������
	if (glove->isCollisionDamaged)
	{
		glove->damagedCount++;
		
		return new gloveDamagedState();
	}
		return nullptr;
}

void gloveMoveState::update(glove * glove)
{
	if (!glove->isRight)		//���� �ٶ󺸸�
	{
		//frame
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
			{
				glove->setCurrentFrameX(0);
			}
			else
			{
				glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);

			}
			glove->setCurrentFrameY(1);
		}

		//move
		if (!glove->isXOverlap)
		{
			glove->_glove.x -= 0.7f;
		}
		//���� ���� => �������� ����
		glove->_glove.rcAttackRange = RectMakeCenter(glove->_glove.x, glove->_glove.y + 200, 250, 50);

	}
	if (glove->isRight)			//������ �ٶ󺸸�
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
			{
				glove->setCurrentFrameX(0);
			}
			else
			{
				glove->setCurrentFrameX(glove->getCurrentFrameX() + 1);
			}
			glove->setCurrentFrameY(0);
		}
		//move
		if (!glove->isXOverlap)
		{
			glove->_glove.x += 0.7f;
		}
		//���� ���� => ���������� ����
		glove->_glove.rcAttackRange = RectMakeCenter(glove->_glove.x + 360, glove->_glove.y + 200, 250, 50);
	}

	//move (up, down)
	if (!glove->isYOverlap)//��������	//isOverlap�� false�� ��.. ��, ���� ���� ��(���)	//�ݴ�� ������ ���� ����� �� �� y��ǥ�� �������� �ʴ´�.
	{
		if (!glove->isDown)	//�����̸�
		{
			glove->_glove.y -= 0.7f;
		}
		if (glove->isDown)	//�Ʒ����̸�
		{
			glove->_glove.y += 0.7f;
		}
	}
}

void gloveMoveState::enter(glove * glove)
{
	glove->_glove.img = IMAGEMANAGER->findImage("glove_move");
	glove->setImageName("glove_move");

	if (!glove->isRight)
	{
		glove->setCurrentFrameY(1);
	}
	if (glove->isRight)
	{
		glove->setCurrentFrameY(0);
	}
	glove->setCurrentFrameX(0);

	glove->timeCount = 0;

}

void gloveMoveState::exit(glove * glove)
{
}
