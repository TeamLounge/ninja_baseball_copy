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
		return new gloveAttackTongueState();		//�׷� ������ ���� ��� �����ٰŰ�, �ൿ�� player�ʿ��� �ϰ�
	}
	//glove�� ������
	if (glove->isCollisionDamaged)
	{
		if (glove->damageCount < 5)
		{
			return new gloveDamagedState();
		}
		if (glove->damageCount == 5)
		{
			return new gloveDeathState();
		}
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
	if (!glove->isRight)
	{
		glove->setCurrentFrameY(1);
	}
	if (glove->isRight)
	{
		glove->setCurrentFrameY(0);
	}
	glove->setCurrentFrameX(0);

}

void gloveMoveState::exit(glove * glove)
{
}
