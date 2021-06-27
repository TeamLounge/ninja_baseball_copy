#include "stdafx.h"
#include "yellowBaseball.h"
#include "ybMoveState.h"
#include "ybIdleState.h"
#include "ybAttackPunchState.h"

ybState * ybAttackPunchState::inputHandle(yellowBaseball * yellowBaseball)
{
	if (_currentFrameX == yellowBaseball->_yellowBaseball.img->getMaxFrameX())	//��ġ �������� �� ���� ����		//���߿� Ư�� ���� �� �߰������� ex) ��ġ ���Ȱ� + ������, �ȸ�����
	{
		return new ybIdleState();	//����Ʈ(�ȸ�����)�� idle ����
	}
	return nullptr;
}

void ybAttackPunchState::update(yellowBaseball * yellowBaseball)
{
	if (!yellowBaseball->isRight)		//���� ���� ������
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else {
				_currentFrameX++;

			}
			_currentFrameY = 1;
		}

		//�������� �̵�
		yellowBaseball->_yellowBaseball.x -= 0.7f;
		//Ž�� ���� ��������
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}
	if (yellowBaseball->isRight)			//������ ����
	{
		frameCount++;
		if (frameCount >= 15)
		{
			frameCount = 0;
			if (_currentFrameX == yellowBaseball->_yellowBaseball.img->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			else
			{
				_currentFrameX++;

			}
			_currentFrameY = 0;

		}
		//move
		yellowBaseball->_yellowBaseball.x += 0.7f;
		//���� ���� => ���������� ����
		yellowBaseball->_yellowBaseball.rcAttackRange = RectMakeCenter(yellowBaseball->_yellowBaseball.x + 360, yellowBaseball->_yellowBaseball.y + 200, 250, 50);
	}

	//move (up, down)
	if (!yellowBaseball->isDown)	//�����̸�
	{
		yellowBaseball->_yellowBaseball.y -= 0.7f;
	}
	if (yellowBaseball->isDown)	//�Ʒ����̸�
	{
		yellowBaseball->_yellowBaseball.y += 0.7f;
	}
}

void ybAttackPunchState::enter(yellowBaseball * yellowBaseball)
{
	yellowBaseball->_yellowBaseball.img = IMAGEMANAGER->findImage("yBaseball_punch");
	if (!yellowBaseball->isRight)
	{
		_currentFrameY = 1;
	}
	if (yellowBaseball->isRight)
	{
		_currentFrameY = 0;
	}
	_currentFrameX = 0;

}

void ybAttackPunchState::exit(yellowBaseball * yellowBaseball)
{
}
