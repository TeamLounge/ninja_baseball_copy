#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	setCard();
	
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	playerLocation();

	collision();	//���� vs wbŸ�ݹ�����Ʈ

	updateCard();
	WhereIsCard();
}

void enemyManager::render()
{
	renderCard();
}


void enemyManager::setWB()
{
	for (int i = 0; i < 3; i++)
	{
		whiteBaseball* _wb = new whiteBaseball;	//�����Ҵ� ���ְ�
		_wb->init(PointMake(WINSIZEX + i * 220, -50 + i * 200));			//�̴����� ��ġ ����ְ�
		_vWb.push_back(_wb);					//��ġ ����� �ָ� ���Ϳ� ����

	}
	//�� ����ġ ���� �� �������� for�� �ۿ� ���� ���ִ� �͵� ���
	//whiteBaseball* _wb1 = new whiteBaseball;	//�����Ҵ� ���ְ�
	//_wb1->init(PointMake(500, 500));			//�̴����� ��ġ ����ְ�
	//_vWb.push_back(_wb1);					//��ġ ����� �ָ� ���Ϳ� ����
}

void enemyManager::updateWB()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->update();		//�� ������Ʈ�� ��
	}
}

void enemyManager::renderWB()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->render();		//�� ������ ��
	}
}

void enemyManager::playerLocation()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if (!(*_viWb)->isJump)	//���� = true
		{
			//���ʹ̰� �÷��̾��� ������?
			if (_player->getRect().right > (*_viWb)->getRect().right)
			{
				(*_viWb)->setIsRight(true);
			}
			//���ʹ̰� �÷��̾��� ����?
			if (_player->getRect().left < (*_viWb)->getRect().left)
			{
				(*_viWb)->setIsRight(false);
			}

			//���ʹ̰� �÷��̾��� ��?
			if (_player->getRect().top > (*_viWb)->getRect().top)
			{
				(*_viWb)->setIsDown(false);
			}
			//���ʹ̰� �÷��̾��� �Ʒ�?
			if (_player->getRect().bottom > (*_viWb)->getRect().bottom)
			{
				(*_viWb)->setIsDown(true);
			}
		}
	}
}

void enemyManager::collision()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getAttackRect()))
		{
			(*_viWb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viWb)->setIsCollisionAttack(false);
		}

	}
}


//////////////////////////////////////////////////
//			ī�� ���ʹ� ����
/////////////////////////////////////////////////
void enemyManager::setCard()
{
	for (int i = 0; i < 2; i++)
	{
		card* _cd;
		_cd = new card;
		_cd->init(PointMake(-50 + i * 700, 300));
		_vCard.push_back(_cd);
	}
}


//////////////////////////////////////////////////
//			ī�� ���ʹ� ������Ʈ
/////////////////////////////////////////////////
void enemyManager::updateCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->update();
	}
}


//////////////////////////////////////////////////
//			ī�� ���ʹ� ����
/////////////////////////////////////////////////
void enemyManager::renderCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->render();
	}
}


//////////////////////////////////////////////////
//			ī�� ��ġ Ž����
/////////////////////////////////////////////////
void enemyManager::WhereIsCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if (!(*_viCard)->getIsDash() && !(*_viCard)->getIsBullet())
		{
			//�÷��̾�� ���ʿ� ������
			if (_player->getX() > (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(false);
			}

			//�÷��̾�� �����ʿ� ������
			if (_player->getX() < (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(true);
			}

			//�÷��̾�� ���� ������
			if (_player->getY() > (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(true);
			}

			//�÷��̾�� �Ʒ��� ������
			if (_player->getY() < (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(false);
			}

			RECT temp;
			if (IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc())
				&& !(*_viCard)->_isCrash)
			{
				(*_viCard)->numPattern = rand() % 3;
				(*_viCard)->setIsDash(false);
				(*_viCard)->setIsBullet(false);
				(*_viCard)->_isCrash = true;

				if ((*_viCard)->numPattern == 1)
				{
					(*_viCard)->setIsDash(true);
				}

				if ((*_viCard)->numPattern == 2)
				{
					(*_viCard)->setIsBullet(true);
				}
			}

			if (!IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc()))
			{
				(*_viCard)->_isCrash = false;
			}
		}
	}
}

