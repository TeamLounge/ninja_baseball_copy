#include "stdafx.h"
#include "card.h"
#include "cardPunchAttackState.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"

cardState * cardPunchAttackState::inputHandle(card * card)
{
	if (card->_currentFrameX == card->_card.img->getMaxFrameX())
	{
		card->_isPunchBullet = false;
		return new cardIdleState();
	}
	return S_OK;
}

void cardPunchAttackState::update(card * card)
{
	if (!card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = card->_card.img->getMaxFrameX();
			}
			else card->_currentFrameX++;
			card->_currentFrameY = 0;
			//�Ѿ��� ���ϴ� �����ӿ��� �߻��ϱ� ���� ���ǹ�
			if (card->_currentFrameX == 1)
			{
				card->fireBullet(card->_card.rc.right, card->getCenterY(), PI-PI);
				card->setBullet(1, WINSIZEX);
			}
		}
	}

	else if (card->_isLeft)
	{
		frameCount++;
		if (frameCount >= 25)
		{
			frameCount = 0;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = card->_card.img->getMaxFrameX();
			}
			else card->_currentFrameX++;
			card->_currentFrameY = 1;
			//�Ѿ��� ���ϴ� �����ӿ��� �߻��ϱ� ���� ���ǹ�
			if (card->_currentFrameX == 1)
			{
				card->fireBullet(card->_card.rc.left, card->getCenterY(), PI);
				card->setBullet(1, WINSIZEX);
			}
		}
	}
}

void cardPunchAttackState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_attack");

	//�̹��� ������ ���� ����

	if (!card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 0;
	}

	if (card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 1;
	}
}

void cardPunchAttackState::exit(card * card)
{
}
