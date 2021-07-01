#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	
	//setBlueBaseball();		
	setGreenBaseball();
	//setWhiteBaseball();			
	//setYellowBaseball();		//데스로 못가네
	
	//setBat();					
	//setCard();
	//setGlove();				
	//setBoss();				

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	//updateBaseball();
	//baseballCollision();	//플레이어 vs 베이스볼타격범위렉트


	updateBat();
	batCollision();

	//updateGlove();
	//gloveCollision();
	//
	//playerLocation();

	//updateCard();
	//WhereIsCard();	

	//updateBoss();
	//assultedCollisionBoss();
}

void enemyManager::render()
{

	renderBaseball();
	//renderGlove();
	renderCard();
	//renderBoss();

	char str1[126];
	sprintf_s(str1, "맞앗써");
	char str2[125];
	sprintf_s(str2, "잡혓어");
	char str3[125];
	sprintf_s(str3, "풀렸어");

	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		if ((*_viWb)->isdamage)
		{
			TextOut(getMemDC(), (*_viWb)->getRect().left - 100, (*_viWb)->getRect().top - 100, str1, strlen(str1));
		}
		if ((*_viWb)->iscatch)
		{
			TextOut(getMemDC(), (*_viWb)->getRect().left - 100, (*_viWb)->getRect().top - 100, str2, strlen(str2));
		}
	}
}

void enemyManager::setBlueBaseball()
{
	//BLUE
	for (int i = 0; i < 2; i++)
	{
		blueBaseball* _bb = new blueBaseball;
		_bb->init(PointMake(300 + i * 100, -50 + i * 80));
		_vBb.push_back(_bb);

	}
}
void enemyManager::setGreenBaseball()
{
	//GREEN
	for (int i = 0; i < 3; i++)
	{
		greenBaseball* _gb = new greenBaseball;
		_gb->init(PointMake(400 + i * 140, -100 + i * 120));
		_vGb.push_back(_gb);

	}
}
void enemyManager::setWhiteBaseball()
{
	//WHITE
	for (int i = 0; i < 3; i++)
	{
		whiteBaseball* _wb = new whiteBaseball;	//동적할당 해주고
		_wb->init(PointMake(WINSIZEX + i * 220, BACKGROUNDY - 400 - 50 + i * 200));			//이닛으로 위치 잡아주고
		_vWb.push_back(_wb);					//위치 잡아준 애를 벡터에 넣음
	}
	//좀 일정치 않은 놈 뽑으려면 for문 밖에 빼서 해주는 것도 방법
	//whiteBaseball* _wb1 = new whiteBaseball;	//동적할당 해주고
	//_wb1->init(PointMake(500, 500));			//이닛으로 위치 잡아주고
	//_vWb.push_back(_wb1);					//위치 잡아준 애를 벡터에 넣음
}
void enemyManager::setYellowBaseball()
{
	//YELLOW
	for (int i = 0; i < 2; i++)
	{
		yellowBaseball* _yb = new yellowBaseball;
		_yb->init(PointMake(500 + i * 180, -50 + i * 160));		//x좌표 동일하게 하지 말자!!!!! 겹쳐보인다!! 0번쨰 없어보인다!!!
		_vYb.push_back(_yb);
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
	////////////////
   //   white    //
   ///////////////
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
	////////////////
   //   yellow   //
   ///////////////
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
	////////////////
   //    green   //
   ///////////////
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
	////////////////
   //    blue    //
   ///////////////
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
	////////////////
	//     bat   //
	///////////////
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		if (!(*_viBat)->isJump)	//점프 = true
		{
			//에너미가 플레이어의 오른쪽?

			if (_player->getX() > (*_viBat)->getCenterX())
			{
				(*_viBat)->setIsRight(true);
			}
			//에너미가 플레이어의 왼쪽?
			if (_player->getX() < (*_viBat)->getCenterX())
			{
				(*_viBat)->setIsRight(false);
			}
			//에너미가 플레이어의 위?
			if (_player->getY() > (*_viBat)->getCenterY())
			{
				(*_viBat)->setIsDown(true);
			}
			//에너미가 플레이어의 아래?
			if (_player->getY() < (*_viBat)->getCenterY())
			{
				(*_viBat)->setIsDown(false);
			}
		}
		//Y떨림방지
		if ((*_viBat)->getCenterY() < _player->getY() + 3 && (*_viBat)->getCenterY() > _player->getY() - 3)
		{
			(*_viBat)->setIsYOverlap(true);
		}
		if (!((*_viBat)->getCenterY() < _player->getY() + 3 && (*_viBat)->getCenterY() > _player->getY() - 3))
		{
			(*_viBat)->setIsYOverlap(false);
		}
		//X떨림방지
		if ((*_viBat)->getCenterX() < _player->getX() + 3 && (*_viBat)->getCenterX() > _player->getX() - 3)
		{
			(*_viBat)->setIsXOverlap(true);
		}
		if (!((*_viBat)->getCenterX() < _player->getX() + 3 && (*_viBat)->getCenterX() > _player->getX() - 3))
		{
			(*_viBat)->setIsXOverlap(false);
		}
	}
	//////////////////
	//    glove   ///
	/////////////////
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		if (!(*_viGlove)->isJump)	//점프 = true
		{
			//에너미가 플레이어의 오른쪽?

			if (_player->getX() > (*_viGlove)->getCenterX())
			{
				(*_viGlove)->setIsRight(true);
			}
			//에너미가 플레이어의 왼쪽?
			if (_player->getX() < (*_viGlove)->getCenterX())
			{
				(*_viGlove)->setIsRight(false);
			}
			//에너미가 플레이어의 위?
			if (_player->getY() > (*_viGlove)->getCenterY())
			{
				(*_viGlove)->setIsDown(true);
			}
			//에너미가 플레이어의 아래?
			if (_player->getY() < (*_viGlove)->getCenterY())
			{
				(*_viGlove)->setIsDown(false);
			}
		}
		//Y떨림방지
		if ((*_viGlove)->getCenterY() < _player->getY() + 3 && (*_viGlove)->getCenterY() > _player->getY() - 3)
		{
			(*_viGlove)->setIsYOverlap(true);
		}
		if (!((*_viGlove)->getCenterY() < _player->getY() + 3 && (*_viGlove)->getCenterY() > _player->getY() - 3))
		{
			(*_viGlove)->setIsYOverlap(false);
		}
		//X떨림방지
		if ((*_viGlove)->getCenterX() < _player->getX() + 3 && (*_viGlove)->getCenterX() > _player->getX() - 3)
		{
			(*_viGlove)->setIsXOverlap(true);
		}
		if (!((*_viGlove)->getCenterX() < _player->getX() + 3 && (*_viGlove)->getCenterX() > _player->getX() - 3))
		{
			(*_viGlove)->setIsXOverlap(false);
		}
	}
}

void enemyManager::baseballCollision()
{
	////////////////
   //   white    //
   ///////////////

	//ATTACK//
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
	//DAMAGED//
	//for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getRect()) &&
	//		KEYMANAGER->isOnceKeyDown('M'))												//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
	//	{
	//		(*_viWb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
	//		(*_viWb)->damageCount++;

	//		if ((*_viWb)->damageCount > 5)
	//		{
	//			(*_viWb)->damageCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		(*_viWb)->setIsCollisionDamaged(false);		//아니면 false로 전환
	//	}
	//}

		////DAMAGED_(종혁씨가 만드신 거)
		//if (_player->isattack) {
		//	if (_player->_shadow->getCenterY() >= (*_viWb)->_wbShadow.rc.top && 
		//		_player->_shadow->getCenterY() <= (*_viWb)->_wbShadow.rc.bottom) {
		//		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viWb)->getRect()))
		//		{
		//			(*_viWb)->isdamage= true;
		//		}
		//	}
		//}
		//if (_player->iscrawl && !_player->isattack)
		//{
		//	if (_player->_shadow->getCenterY() >= (*_viWb)->_wbShadow.rc.top &&
		//		_player->_shadow->getCenterY() <= (*_viWb)->_wbShadow.rc.bottom) {
		//		if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getRect()))
		//		{
		//			(*_viWb)->iscatch = true;
		//		}
		//	}
		//}
	

	////////////////
   //   yellow   //
   ///////////////
	//ATTACK//
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
	//DAMAGED//
	//for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_player->getRect(), &(*_viYb)->getRect()) &&
	//		KEYMANAGER->isOnceKeyDown('M'))												//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
	//	{
	//		(*_viYb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
	//		(*_viYb)->damageCount++;

	//		if ((*_viYb)->damageCount > 5)
	//		{
	//			(*_viYb)->damageCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		(*_viYb)->setIsCollisionDamaged(false);		//아니면 false로 전환
	//	}
	//}
	////////////////
   //   green    //
   ///////////////
	//ATTACK//
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
	//DAMAGED//
	//for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_player->getRect(), &(*_viGb)->getRect()) &&
	//		KEYMANAGER->isOnceKeyDown('M'))												//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
	//	{
	//		(*_viGb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
	//		(*_viGb)->damageCount++;

	//		if ((*_viGb)->damageCount > 5)
	//		{
	//			(*_viGb)->damageCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		(*_viGb)->setIsCollisionDamaged(false);		//아니면 false로 전환
	//	}
	//}
	////////////////
   //   blue     //
   ///////////////
	//ATTACK//
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
	//DAMAGED//
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viBb)->getRect())) //플레이어 사거리와 에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
				(*_viBb)->damageCount++;
		
				if ((*_viBb)->damageCount > 5)
				{
					(*_viBb)->damageCount = 0;
				}
		}
		else (*_viBb)->setIsCollisionDamaged(false);		//아니면 false로 전환


		if (!_player->isattack) (*_viBb)->isCrash = false;
	}
}
void enemyManager::batCollision()
{
	////////////////
   //     bat    //
   ///////////////
	//Attack//
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viBat)->getAttackRect()))		//에너미 사거리에 들어오면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBat)->setIsCollisionAttack(true);		//충돌했으면 bool 값 true로 전환
		}
		else
		{
			(*_viBat)->setIsCollisionAttack(false);		//아니면 false로 전환
		}
	}
	//Damaged//
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viBat)->getRect())
			&& !(*_viBat)->isCollisionDamaged && _player->isattack && !(*_viBat)->isCrash)												//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBat)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
			(*_viBat)->isCrash = true;
			//(*_viBat)->damageCount++;				
		}
			
		if (!_player->isattack) (*_viBat)->isCrash = false;

		//else if (!(IntersectRect(&temp, &_player->getRect(), &(*_viBat)->getRect())))
		//{
		//	(*_viBat)->setIsCollisionDamaged(false);		//아니면 false로 전환
		//}
	}
}
void enemyManager::gloveCollision()
{
	////////////////
   //    glove   //
   ///////////////
    //Attack glove가 공격하면//
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viGlove)->getAttackRect()))		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viGlove)->setIsCollisionAttack(true);		//충돌했으면 bool 값 true로 전환
		}
		else
		{
			(*_viGlove)->setIsCollisionAttack(false);		//아니면 false로 전환
		}
	}
	//Damaged glove가 맞으면//
	
}

void enemyManager::setBat()
{
	for (int i = 0; i < 3; i++)
	{
		bat* _bat = new bat;
		_bat->init(PointMake(470 + i * 130, WINSIZEY - 300 - i * 150));
		_vBat.push_back(_bat);
	}
}
void enemyManager::updateBat()
{
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		(*_viBat)->update();
	}
}
void enemyManager::renderBat()
{
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		(*_viBat)->render();
	}
}

void enemyManager::setGlove()	//태어나는 좌표
{
	for (int i = 0; i < 2; i++)
	{
		glove* _glove = new glove;
		_glove->init(PointMake(470 + i * 30, WINSIZEY - 500 - i * 150));
		_vGlove.push_back(_glove);
	}
}
void enemyManager::updateGlove()
{
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		(*_viGlove)->update();
	}
}
void enemyManager::renderGlove()
{
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		(*_viGlove)->render();
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


//////////////////////////////////////////////////
//			카드 피격 충돌
/////////////////////////////////////////////////
void enemyManager::assultedCollisionCard()
{
	/*for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if ((*_viCard)->_isMoveState && _player->isattack)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
			{
				if (_player->_isGreenAttack1 || _player->_isGreenAttack2 ||
					_player->_isGreenAttack3 || _player->_isGreenDashAttack ||
					_player->_isGreenJumpAttack)
				{
					_boss->_isSmallDamaged = true;
				}

				if (_player->_isGreenDashAlt || _player->_isGreenJumpPowerAttack)
				{
					_boss->_isDamaged = true;
				}
			}
		}

		if (_boss->_isSmallDamagedState && _player->isattack)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
			{
				if (_player->_isGreenAttack1)
				{
					_boss->_isSmallDamaged = true;
				}

				if (_player->_isGreenAttack2 || _player->_isGreenAttackFrontCombo1)
				{
					_boss->_isGreenAttack12 = true;
				}

				if (_player->_isGreenAttack3 || _player->_isGreenAttackFrontCombo2)
				{
					_boss->_isGreenAttack3 = true;
				}
			}
		}

		if (_boss->_isMoveState && _player->iscrawl)
		{
			RECT temp;
			if (IntersectRect(&temp, &_boss->_assultedRect, &_player->getRect()))
			{
				_player->iscatch = true;
				_boss->_isGreenCatch = true;
				_boss->_isSmallDamaged = true;
			}
		}

		if (!_player->iscatch)
		{
			_boss->_isGreenCatch = false;
		}

		if (_player->_isGreenCatchAttack && _player->iscatch)
		{
			_boss->_isGreenCatchAttack = true;
			_player->_isGreenCatchAttack = false;
			_player->_isGreenCatchBackAttack = false;
		}

		if (_player->_isGreenCatchBackAttack && _player->iscatch)
		{
			_boss->_isGreenCatchBackAttack = true;
			_player->_isGreenCatchAttack = false;
		}

		if (_player->_isGreenCatchFrontCombo && _player->iscatch)
		{
			_boss->_isGreenCatchFrontCombo = true;
			_player->_isGreenCatchFrontCombo = false;
		}
	}*/

}


/////////////////////////////////
//  ######보스 위치 선정 ########
/////////////////////////////////
void enemyManager::setBoss()
{
	_boss = new boss;
	_boss->init(PointMake(700, WINSIZEY / 2 - 200));
}


/////////////////////////////////
// ######보스 업데이트 항목 ########
/////////////////////////////////
void enemyManager::updateBoss()
{
	_boss->update();
	WhereIsBoss();				//보스<->플레이어 위치 확인용
	attackCollision();
}


/////////////////////////////////
//  ######보스 그리기 ########
/////////////////////////////////
void enemyManager::renderBoss()
{
	_boss->render();
}


/////////////////////////////////
//  ######보스 위치잡기 ########
/////////////////////////////////
void enemyManager::WhereIsBoss()
{
	//플레이어보다 왼쪽에 있을때
	if (_player->_shadow->getCenterX() > _boss->_bossShadow.x)
	{
		_boss->_isLeft = false;
	}

	//플레이어보다 오른쪽에 있을때
	if (_player->_shadow->getCenterX() < _boss->_bossShadow.x)
	{
		_boss->_isLeft = true;
	}

	//플레이어보다 위에 있을때
	if (_player->_shadow->getCenterY() > _boss->_bossShadow.y)
	{
		_boss->_isUpper = true;
	}

	//플레이어보다 아래에 있을때
	if (_player->_shadow->getCenterY() < _boss->_bossShadow.y)
	{
		_boss->_isUpper = false;
	}
	
	//범위 안에 들어오면 흔들림 스탑핏

	if (_player->_shadow->getCenterX() + 150 > _boss->_bossShadow.x && _player->_shadow->getCenterX() - 150 < _boss->_bossShadow.x)
	{
		_boss->_isMoveStopRangeX = true;
	}

	if (!(_player->_shadow->getCenterX() + 150 > _boss->_bossShadow.x && _player->_shadow->getCenterX() - 150 < _boss->_bossShadow.x))
	{
		_boss->_isMoveStopRangeX = false;
	}

	if (_player->_shadow->getCenterY() + 10 > _boss->_bossShadow.y && _player->_shadow->getCenterY() - 10 < _boss->_bossShadow.y)
	{
		_boss->_isMoveStopRangeY = true;
	}

	if (!(_player->_shadow->getCenterY() + 10 > _boss->_bossShadow.y &&_player->_shadow->getCenterY() - 10 < _boss->_bossShadow.y))
	{
		_boss->_isMoveStopRangeY = false;
	}
}



/////////////////////////////////
//  ######보스 공격충돌 ########
/////////////////////////////////
void enemyManager::attackCollision()
{
	///////////////////////////////////////////
	// #######   보스 원거리 공격   ##########
	/////////////////////////////////////////// 원거리 공격 성공신호는  isSucceedShootingAttack 입니다.

	_boss->_numAtkPattern = RND->getFromIntTo(0, 4);

	if (PtInRect(&_boss->_longRangeAtkRc,
		PointMake(_player->getX(), _player->getRect().bottom)) &&
		!_boss->_isLongRangeCrash && !_boss->_isShootingAttack &&
		!_boss->_isJabAttack)
	{

		int Num = _boss->_numAtkPattern;

		_boss->_isLongRangeCrash = true;

		if (Num == 3)
		{
			_boss->_isShootingAttack = true; //이건 그냥 상태를 보내기위한 스위치 
		}
	}

	if (!PtInRect(&_boss->_longRangeAtkRc,
		PointMake(_player->getX(), _player->getRect().bottom)))
	{
		_boss->_isLongRangeCrash = false;
	}

	//원거리 공격 성공했을때요
	if (_boss->_isTrigger && (PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->getX(), _player->_shadow->getY() + _player->_shadow->getHeight())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY() + _player->_shadow->getHeight()))))
	{
		_boss->_isSucceedShootingAttack = true;
	}

	//원거리 공격 실패했을때요~
	if (!(_boss->_isTrigger && (PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->getX(), _player->_shadow->getY() + _player->_shadow->getHeight())) ||
		PtInRect(&_boss->_longRangeAtkRc, PointMake(_player->_shadow->getX() + _player->_shadow->getWidth(), _player->_shadow->getY() + _player->_shadow->getHeight())))))
	{
		_boss->_isSucceedShootingAttack = false;
	}

	///////////////////////////////////////////
	// #######   보스 jab 공격, straight 공격   ##########
	/////////////////////////////////////////// 잽공격 성공신호는 _isSucceedJabAttack 입니다. 스트레이트공격 성공신호는 _isSucceedStraightAttack 입니다.

	RECT temp;
	if (IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect()) && _boss->_isMoveState &&
		!_boss->_isCrash)
	{
		int randNum = rand() % 6;
		if (randNum != 1) _boss->_missCount++;
		_boss->_isCrash = true;

		if (randNum == 1 || _boss->_missCount > 3)
		{
			_boss->_missCount = 0;
			_boss->_isJabAttack = true;
		}

		if (randNum == 2)
		{
			_boss->_isStraightAttack = true;
		}
	}

	if (!(IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect())))
	{
		_boss->_isCrash = false;
	}

	RECT rc = RectMake(_player->_shadow->getX(), _player->_shadow->getY(),
		_player->_shadow->getWidth(), _player->_shadow->getHeight());

	//잽 공격 성공했을때요~
	if (_boss->_isJabAttack && IntersectRect(&temp, &_boss->_boss.rc, &rc))
	{
		_boss->_isSucceedJabAttack = true;
	}
	//잽 공격 실패했을때요~
	if (!(_boss->_isJabAttack && IntersectRect(&temp, &_boss->_boss.rc, &rc)))
	{
		_boss->_isSucceedJabAttack = false;
	}

	/////////////////////////////////////////////
	// #######  보스 어퍼컷 공격 ##########     //
	/////////////////////////////////////////////
	if (_boss->_isDamagedState)
	{
		if (IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect()))
		{
			_boss->_isUpperCut = true;
			_boss->_isCrash = false;
		}

		if (!(IntersectRect(&temp, &_boss->_boss.rc, &_player->getRect())))
		{
			_boss->_isUpperCut = false;
		}
	}
}

/////////////////////////////////
//  ######보스 피격충돌 ########
///////////////////////////////// 공격 당했을때 //
void enemyManager::assultedCollisionBoss()
{
	//타격 z연습하기zzz 위한 것입니다^^//
	if (_boss->_isMoveState && _player->isattack)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
		{
			if (_player->_isGreenAttack1 ||	_player->_isGreenAttack2 ||
				_player->_isGreenAttack3 || _player->_isGreenDashAttack ||
				_player->_isGreenJumpAttack)
			{
				_boss->_isSmallDamaged = true;
			}

			if (_player->_isGreenDashAlt || _player->_isGreenJumpPowerAttack)
			{
				_boss->_isDamaged = true;
			}
		}
	}

	if (_boss->_isSmallDamagedState && _player->isattack)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
		{
			if (_player->_isGreenAttack1)
			{
				_boss->_isSmallDamaged = true;
			}

			if (_player->_isGreenAttack2 || _player->_isGreenAttackFrontCombo1)
			{
				_boss->_isGreenAttack12 = true;
			}

			if (_player->_isGreenAttack3 || _player->_isGreenAttackFrontCombo2)
			{
				_boss->_isGreenAttack3 = true;
			}
		}
	}

	if (_boss->_isMoveState && _player->iscrawl)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->getRect()))
		{
			_player->iscatch = true;
			_boss->_isGreenCatch = true;
			_boss->_isSmallDamaged = true;
		}
	}

	if (!_player->iscatch)
	{
		_boss->_isGreenCatch = false;
	}

	if (_player->_isGreenCatchAttack && _player->iscatch)
	{
		_boss->_isGreenCatchAttack = true;
		_player->_isGreenCatchAttack = false;
		_player->_isGreenCatchBackAttack = false;
	}

	if (_player->_isGreenCatchBackAttack && _player->iscatch)
	{
		_boss->_isGreenCatchBackAttack = true;
		_player->_isGreenCatchAttack = false;
	}

	if (_player->_isGreenCatchFrontCombo && _player->iscatch)
	{
		_boss->_isGreenCatchFrontCombo = true;
		_player->_isGreenCatchFrontCombo = false;
	}
}
