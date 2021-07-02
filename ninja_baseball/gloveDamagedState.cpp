#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveDamagedState::inputHandle(glove * glove)
{
	if (glove->damagedCount == 5)
	{
		glove->damagedCount = 0;
		return new gloveDeathState();
	}
	if (glove->damagedCount < 5 && glove->getCurrentFrameX() == glove->_glove.img->getMaxFrameX())
	{
		glove->setCurrentFrameX(0);
		glove->isCollisionDamaged = false;
		return new gloveMoveState();
	}
	  
	return nullptr;
}

void gloveDamagedState::update(glove * glove)
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

void gloveDamagedState::enter(glove * glove)
{
	glove->_glove.img = IMAGEMANAGER->findImage("glove_damaged");
	glove->setImageName("glove_damaged");

	if (!glove->isRight)
	{
		glove->setCurrentFrameY(1);
	}
	if (glove->isRight)
	{
		glove->setCurrentFrameY(0);
	}
	glove->setCurrentFrameX(0);

	//glove->isCollisionDamaged = true;

}

void gloveDamagedState::exit(glove * glove)
{
}







////////////////////////////////////////
//move->Ž������ON->���͹�->��� Ž������->attack(����)
//->���͹�->��밡 ����->����->isCollisionDamaged = true
//->damageCount++;
//if (damageCount < 5)
//	return new Damaged();->damageCount == 5 �� �� Death�� / ->�ƴϰ� 5 �Ʒ��� move��
//	if (damageCount == 5)
//	{
//		return new Death();
//	}
//	else return new Move();
//
//Ž������OFF->��� �پ� ���Ű�
//
//
//
//
//
//<����> //��� ���� �ø� �����ϰ� ��𼭳� ���� �� �ִ�(move�� ��.. jump �浹�� ����)
//1. �÷��̾� ���� �浹 + M
//->isCollisionDamaged = true
//->damageCount++;
//if (damageCount == 5)
//{
//	return new Death();
//}
//else	return new Move();
//
//<����>
//
