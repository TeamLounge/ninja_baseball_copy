#include "stdafx.h"
#include "enemyManager.h"
#include "rectPlayer.h"
#include "time.h"

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
	updateCard();
	WhereIsCard();
}

void enemyManager::render()
{
	renderCard();
}

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

void enemyManager::updateCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->update();
	}
}

void enemyManager::renderCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->render();
	}
}

void enemyManager::WhereIsCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if (!(*_viCard)->getIsDash() && !(*_viCard)->getIsBullet())
		{
			//플레이어보다 왼쪽에 있을때
			if (_rp->getCenterX() > (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(false);
			}

			//플레이어보다 오른쪽에 있을때
			if (_rp->getCenterX() < (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(true);
			}

			//플레이어보다 위에 있을때
			if (_rp->getCenterY() > (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(true);
			}

			//플레이어보다 아래에 있을때
			if (_rp->getCenterY() < (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(false);
			}

			RECT temp;
			if (IntersectRect(&temp, &_rp->getRPRc(), &(*_viCard)->getAtkCardRc()))
			{
				srand(time(NULL));
				int Num = 0;
				Num = rand() % 3;

				if (Num == 1)
				{
					(*_viCard)->setIsDash(true);
				}

				if (Num == 2)
				{
					(*_viCard)->setIsBullet(true);
				}
			}
		}
	}
}

