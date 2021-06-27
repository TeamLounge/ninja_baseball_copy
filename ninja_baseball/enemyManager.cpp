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

	collision();	//레드 vs wb타격범위렉트

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
		whiteBaseball* _wb = new whiteBaseball;	//동적할당 해주고
		_wb->init(PointMake(WINSIZEX + i * 220, -50 + i * 200));			//이닛으로 위치 잡아주고
		_vWb.push_back(_wb);					//위치 잡아준 애를 벡터에 넣음

	}
	//좀 일정치 않은 놈 뽑으려면 for문 밖에 빼서 해주는 것도 방법
	//whiteBaseball* _wb1 = new whiteBaseball;	//동적할당 해주고
	//_wb1->init(PointMake(500, 500));			//이닛으로 위치 잡아주고
	//_vWb.push_back(_wb1);					//위치 잡아준 애를 벡터에 넣음
}

void enemyManager::updateWB()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->update();		//너 업데이트로 가
	}
}

void enemyManager::renderWB()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->render();		//너 렌더로 가
	}
}

void enemyManager::playerLocation()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if (!(*_viWb)->isJump)	//점프 = true
		{
			//에너미가 플레이어의 오른쪽?
			if (_player->getRect().right > (*_viWb)->getRect().right)
			{
				(*_viWb)->setIsRight(true);
			}
			//에너미가 플레이어의 왼쪽?
			if (_player->getRect().left < (*_viWb)->getRect().left)
			{
				(*_viWb)->setIsRight(false);
			}

			//에너미가 플레이어의 위?
			if (_player->getRect().top > (*_viWb)->getRect().top)
			{
				(*_viWb)->setIsDown(false);
			}
			//에너미가 플레이어의 아래?
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
//			카드 에너미 세팅
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
//			카드 에너미 업데이트
/////////////////////////////////////////////////
void enemyManager::updateCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->update();
	}
}


//////////////////////////////////////////////////
//			카드 에너미 렌더
/////////////////////////////////////////////////
void enemyManager::renderCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->render();
	}
}


//////////////////////////////////////////////////
//			카드 위치 탐색용
/////////////////////////////////////////////////
void enemyManager::WhereIsCard()
{
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if (!(*_viCard)->getIsDash() && !(*_viCard)->getIsBullet())
		{
			//플레이어보다 왼쪽에 있을때
			if (_player->getX() > (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(false);
			}

			//플레이어보다 오른쪽에 있을때
			if (_player->getX() < (*_viCard)->getCenterX())
			{
				(*_viCard)->setIsLeft(true);
			}

			//플레이어보다 위에 있을때
			if (_player->getY() > (*_viCard)->getCenterY())
			{
				(*_viCard)->setIsUpper(true);
			}

			//플레이어보다 아래에 있을때
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

