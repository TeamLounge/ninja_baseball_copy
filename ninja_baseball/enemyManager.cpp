#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "time.h"

HRESULT enemyManager::init()
{
	setBaseball();
	setCard();
	

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	updateBaseball();
	playerLocation();

	baseballCollision();	//플레이어 vs wb타격범위렉트

	updateCard();
	WhereIsCard();	
}

void enemyManager::render()
{

	renderBaseball();
	renderCard();
}


void enemyManager::setBaseball()
{
	//whiteBaseball
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

	//yellowBaseball
	for (int i = 0; i < 2; i++)
	{
		yellowBaseball* _yb = new yellowBaseball;
		_yb->init(PointMake(500 + i * 180, -50 + i * 160));		//x좌표 동일하게 하지 말자!!!!! 겹쳐보인다!! 0번쨰 없어보인다!!!
		_vYb.push_back(_yb);
	}
	//greenBaseball
	for (int i = 0; i < 2; i++)
	{
		greenBaseball* _gb = new greenBaseball;
		_gb->init(PointMake(400 + i * 140, -50 + i * 120));
		_vGb.push_back(_gb);					

	}
	//blueBaseball
	for (int i = 0; i < 2; i++)
	{
		blueBaseball* _bb = new blueBaseball;
		_bb->init(PointMake(300 + i * 100, -50 + i * 80));
		_vBb.push_back(_bb);

	}
}

void enemyManager::updateBaseball()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->update();		//너 업데이트로 가
	}
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		(*_viYb)->update();
	}
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		(*_viGb)->update();
	}
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		(*_viBb)->update();
	}

}

void enemyManager::renderBaseball()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->render();		//너 렌더로 가
	}
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		(*_viYb)->render();
	}
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		(*_viGb)->render();
	}
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		(*_viBb)->render();
	}
}

void enemyManager::playerLocation()
{
	//white
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if (!(*_viWb)->isJump)	//점프 = true
		{
			//에너미가 플레이어의 오른쪽?
			if (_player->getX() > (*_viWb)->getCenterX())
			{
				(*_viWb)->setIsRight(true);
			}
			//에너미가 플레이어의 왼쪽?
			if (_player->getX() < (*_viWb)->getCenterX())
			{
				(*_viWb)->setIsRight(false);
			}
			//에너미가 플레이어의 위?
			if (_player->getY() > (*_viWb)->getCenterY())
			{
				(*_viWb)->setIsDown(true);
			}
			//에너미가 플레이어의 아래?
			if (_player->getY() < (*_viWb)->getCenterY())
			{
				(*_viWb)->setIsDown(false);
			}
		}
		//Y떨림방지
		if ((*_viWb)->getCenterY() < _player->getY() + 3 && (*_viWb)->getCenterY() > _player->getY() - 3)
		{
			(*_viWb)->setIsYOverlap(true);
		}
		if (!((*_viWb)->getCenterY() < _player->getY() + 3 && (*_viWb)->getCenterY() > _player->getY() - 3))
		{
			(*_viWb)->setIsYOverlap(false);
		}
		//X떨림방지
		if ((*_viWb)->getCenterX() < _player->getX() + 3 && (*_viWb)->getCenterX() > _player->getX() - 3)
		{
			(*_viWb)->setIsXOverlap(true);
		}
		if (!((*_viWb)->getCenterX() < _player->getX() + 3 && (*_viWb)->getCenterX() > _player->getX() - 3))
		{
			(*_viWb)->setIsXOverlap(false);
		}

	}
	//yellow
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		//에너미가 플레이어의 오른쪽?
		if (_player->getX() > (*_viYb)->getCenterX())
		{
			(*_viYb)->setIsRight(true);
		}
		//에너미가 플레이어의 왼쪽?
		if (_player->getX() < (*_viYb)->getCenterX())
		{
			(*_viYb)->setIsRight(false);
		}
		//에너미가 플레이어의 위?
		if (_player->getY() > (*_viYb)->getCenterY())
		{
			(*_viYb)->setIsDown(true);
		}
		//에너미가 플레이어의 아래?
		if (_player->getY() < (*_viYb)->getCenterY())
		{
			(*_viYb)->setIsDown(false);
		}
		//Y떨림방지
		if ((*_viYb)->getCenterY() < _player->getY() + 3 && (*_viYb)->getCenterY() > _player->getY() - 3)
		{
			(*_viYb)->setIsYOverlap(true);
		}
		if (!((*_viYb)->getCenterY() < _player->getY() + 3 && (*_viYb)->getCenterY() > _player->getY() - 3))
		{
			(*_viYb)->setIsYOverlap(false);
		}
		//X떨림방지
		if ((*_viYb)->getCenterX() < _player->getX() + 3 && (*_viYb)->getCenterX() > _player->getX() - 3)
		{
			(*_viYb)->setIsXOverlap(true);
		}
		if (!((*_viYb)->getCenterX() < _player->getX() + 3 && (*_viYb)->getCenterX() > _player->getX() - 3))
		{
			(*_viYb)->setIsXOverlap(false);
		}
	}
	//green
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		//에너미가 플레이어의 오른쪽?
		if (_player->getX() > (*_viGb)->getCenterX())
		{
			(*_viGb)->setIsRight(true);
		}
		//에너미가 플레이어의 왼쪽?
		if (_player->getX() < (*_viGb)->getCenterX())
		{
			(*_viGb)->setIsRight(false);
		}
		//에너미가 플레이어의 위?
		if (_player->getY() > (*_viGb)->getCenterY())
		{
			(*_viGb)->setIsDown(true);
		}
		//에너미가 플레이어의 아래?
		if (_player->getY() < (*_viGb)->getCenterY())
		{
			(*_viGb)->setIsDown(false);
		}
		//Y떨림방지
		if ((*_viGb)->getCenterY() < _player->getY() + 3 && (*_viGb)->getCenterY() > _player->getY() - 3)
		{
			(*_viGb)->setIsYOverlap(true);
		}
		if (!((*_viGb)->getCenterY() < _player->getY() + 3 && (*_viGb)->getCenterY() > _player->getY() - 3))
		{
			(*_viGb)->setIsYOverlap(false);
		}
		//X떨림방지
		if ((*_viGb)->getCenterX() < _player->getX() + 3 && (*_viGb)->getCenterX() > _player->getX() - 3)
		{
			(*_viGb)->setIsXOverlap(true);
		}
		if (!((*_viGb)->getCenterX() < _player->getX() + 3 && (*_viGb)->getCenterX() > _player->getX() - 3))
		{
			(*_viGb)->setIsXOverlap(false);
		}
	}
	//blue
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		//에너미가 플레이어의 오른쪽?
		if (_player->getX() > (*_viBb)->getCenterX())
		{
			(*_viBb)->setIsRight(true);
		}
		//에너미가 플레이어의 왼쪽?
		if (_player->getX() < (*_viBb)->getCenterX())
		{
			(*_viBb)->setIsRight(false);
		}
		//에너미가 플레이어의 위?
		if (_player->getY() > (*_viBb)->getCenterY())
		{
			(*_viBb)->setIsDown(true);
		}
		//에너미가 플레이어의 아래?
		if (_player->getY() < (*_viBb)->getCenterY())
		{
			(*_viBb)->setIsDown(false);
		}
		//Y떨림방지
		if ((*_viBb)->getCenterY() < _player->getY() + 3 && (*_viBb)->getCenterY() > _player->getY() - 3)
		{
			(*_viBb)->setIsYOverlap(true);
		}
		if (!((*_viBb)->getCenterY() < _player->getY() + 3 && (*_viBb)->getCenterY() > _player->getY() - 3))
		{
			(*_viBb)->setIsYOverlap(false);
		}
		//X떨림방지
		if ((*_viBb)->getCenterX() < _player->getX() + 3 && (*_viBb)->getCenterX() > _player->getX() - 3)
		{
			(*_viBb)->setIsXOverlap(true);
		}
		if (!((*_viBb)->getCenterX() < _player->getX() + 3 && (*_viBb)->getCenterX() > _player->getX() - 3))
		{
			(*_viBb)->setIsXOverlap(false);
		}
	}
}

void enemyManager::baseballCollision()
{
	//white
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getAttackRect()))		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viWb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viWb)->setIsCollisionAttack(false);
		}
	}
	//yellow
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viYb)->getAttackRect()))
		{
			(*_viYb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viYb)->setIsCollisionAttack(false);
		}
	}
	//green
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viGb)->getAttackRect()))
		{
			(*_viGb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viGb)->setIsCollisionAttack(false);
		}
	}
	//blue
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viBb)->getAttackRect()))
		{
			(*_viBb)->setIsCollisionAttack(true);
		}
		else
		{
			(*_viBb)->setIsCollisionAttack(false);
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
			if (IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc()))
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

