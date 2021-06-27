#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
//이거 지워보면 

HRESULT enemyManager::init()
{
	setWB();

	

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	updateWB();
	playerLocation();

	collision();	//레드 vs wb타격범위렉트
}

void enemyManager::render()
{
	renderWB();
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
			if (_red->getRect().right > (*_viWb)->getRect().right)
			{
				(*_viWb)->setIsRight(true);
			}
			//에너미가 플레이어의 왼쪽?
			if (_red->getRect().left < (*_viWb)->getRect().left)
			{
				(*_viWb)->setIsRight(false);
			}

			//에너미가 플레이어의 위?
			if (_red->getRect().top > (*_viWb)->getRect().top)
			{
				(*_viWb)->setIsDown(false);
			}
			//에너미가 플레이어의 아래?
			if (_red->getRect().bottom > (*_viWb)->getRect().bottom)
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
		if (IntersectRect(&temp, &_red->getRect(), &(*_viWb)->getAttackRect()))
		{
			(*_viWb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viWb)->setIsCollisionAttack(false);
		}

	}
}

