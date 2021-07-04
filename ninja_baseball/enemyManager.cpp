#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

//ver.9 에너미 삭제 gogo(07/03, 21:48)
HRESULT enemyManager::init()
{
	
	//setBlueBaseball();		
	//setGreenBaseball();
	//setWhiteBaseball();			
	//setYellowBaseball();		
	
	//setBat1();
	//setBat2();
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
	//baseballCollision();	

	//updateBat();
	//batCollision();

	//updateGlove();
	//gloveCollision();
	
	//playerLocation();

	//updateCard();
	//WhereIsCard();	

	//updateBoss();
	//assultedCollisionBoss();
}

void enemyManager::render()
{

	//renderGlove();

	renderCard();
	//renderBoss();

	char str1[126];
	sprintf_s(str1, "맞앗써");
	char str2[125];
	sprintf_s(str2, "잡혓어");
	char str3[125];
	sprintf_s(str3, "풀렸어");

	//renderBoss();
	
}

//SET BaseBall
void enemyManager::setBlueBaseball()
{
	//BLUE
	for (int i = 0; i < 2; i++)
	{
		blueBaseball* _bb = new blueBaseball;
		_bb->init(PointMake(1200, 450 - i * 400));
		_vBb.push_back(_bb);

	}
}
void enemyManager::setGreenBaseball()
{
	//GREEN
	for (int i = 0; i < 2; i++)
	{
		greenBaseball* _gb = new greenBaseball;
		_gb->init(PointMake(2500 + i * 400, -100));		//2500, -200
		_vGb.push_back(_gb);

	}
}
void enemyManager::setWhiteBaseball()
{
	//WHITE
	for (int i = 0; i < 3; i++)
	{
		whiteBaseball* _wb = new whiteBaseball;	//동적할당 해주고
		_wb->init(PointMake(1900 + i * 100, 150 + i * 150));			//이닛으로 위치 잡아주고
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
		_yb->init(PointMake(850 + i * 180, 150 + i * 160));		//x좌표 동일하게 하지 말자!!!!! 겹쳐보인다!! 0번쨰 없어보인다!!!
		_vYb.push_back(_yb);
	}
}

//UPDATE BaseBall
void enemyManager::updateBlueBaseball()
{
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		(*_viBb)->update();
	}
}
void enemyManager::updateGreenBaseball()
{

	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		(*_viGb)->update();
	}
}
void enemyManager::updateWhiteBaseball()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->update();		//너 업데이트로 가
	}
}
void enemyManager::updateYellowBaseball()
{
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		(*_viYb)->update();
	}
}

//RENDER BaseBall
void enemyManager::renderBlueBaseball()
{
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		(*_viBb)->render();
	}
}
void enemyManager::renderGreenBaseball()
{
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		(*_viGb)->render();
	}
}
void enemyManager::renderWhiteBaseball()
{
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		(*_viWb)->render();		//너 렌더로 가
	}
}
void enemyManager::renderYellowBaseball()
{
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		(*_viYb)->render();
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
		if (IntersectRect(&temp, &_player->getRect(), &(*_viWb)->getAttackRect()))		//에너미 사거리에 들어오면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viWb)->setIsCollisionAttack(true);		//충돌했으면 bool 값 true로 전환
		}
		else
		{
			(*_viWb)->setIsCollisionAttack(false);		//아니면 false로 전환
		}
	}
	//Damaged//
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viWb)->getRect())
			&& !(*_viWb)->isCollisionDamaged && _player->isattack && !(*_viWb)->isCrash)	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viWb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
			(*_viWb)->isCrash = true;
		}

		if (!_player->isattack) (*_viWb)->isCrash = false;
	}
	//죽은 애들 지워주자
	if (!_vWb.empty())
	{
		for (int i = 0; i < _vWb.size(); ++i)
		{
			if (_vWb[i]->isDeathDeleteState)	//죽었고 신호 들어오면
			{
				RENDERMANAGER->deleteObj("whiteBaseball", i);
				_vWb.erase(_vWb.begin() + i);	//딜리트하자
				break;
			}
		}
	}

	//노란색 베이스볼끼리 충돌
	if (!_vWb.empty())
	{
		for (int i = 0; i < _vWb.size() - 1; i++)
		{
			if (_vWb[i]->isJump) continue;
			for (int j = i + 1; j < _vWb.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vWb[i]->getShadowRect(), &_vWb[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vWb[i]->getShadowY() < _vWb[j]->getShadowY())
						{
							_vWb[i]->setShadowY(_vWb[i]->getShadowY() - height);
							_vWb[i]->setY(_vWb[i]->getShadowY() - 295);
							_vWb[i]->setRc(RectMakeCenter(_vWb[i]->getX() + 200, _vWb[i]->getY() + 200, 300, 230));
							_vWb[i]->setShadowRc(RectMakeCenter(_vWb[i]->getShadowX(), _vWb[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vWb[i]->setShadowY(_vWb[i]->getShadowY() + height);
							_vWb[i]->setY(_vWb[i]->getShadowY() - 295);
							_vWb[i]->setRc(RectMakeCenter(_vWb[i]->getX() + 200, _vWb[i]->getY() + 200, 300, 230));
							_vWb[i]->setShadowRc(RectMakeCenter(_vWb[i]->getShadowX(), _vWb[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vWb[i]->getShadowX() < _vWb[j]->getShadowX())
						{
							_vWb[i]->setShadowX(_vWb[i]->getShadowX() - width);
							_vWb[i]->setX(_vWb[i]->getShadowX() - 200);
							_vWb[i]->setRc(RectMakeCenter(_vWb[i]->getX() + 200, _vWb[i]->getY() + 200, 300, 230));
							_vWb[i]->setShadowRc(RectMakeCenter(_vWb[i]->getShadowX(), _vWb[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vWb[i]->setShadowX(_vWb[i]->getShadowX() + width);
							_vWb[i]->setX(_vWb[i]->getShadowX() - 200);
							_vWb[i]->setRc(RectMakeCenter(_vWb[i]->getX() + 200, _vWb[i]->getY() + 200, 300, 230));
							_vWb[i]->setShadowRc(RectMakeCenter(_vWb[i]->getShadowX(), _vWb[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}

	////////////////
   //   yellow   //
   ///////////////
	//ATTACK//
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viYb)->getAttackRect()))		//에너미 사거리에 들어오면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viYb)->setIsCollisionAttack(true);		//충돌했으면 bool 값 true로 전환
		}
		else
		{
			(*_viYb)->setIsCollisionAttack(false);		//아니면 false로 전환
		}
	}

	//Damaged//
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viYb)->getRect())
			&& !(*_viYb)->isCollisionDamaged && _player->isattack && !(*_viYb)->isCrash)	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viYb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
			(*_viYb)->isCrash = true;
		}

		if (!_player->isattack) (*_viYb)->isCrash = false;
	}
	//죽은 애들 지워주자
	if (!_vYb.empty())
	{
		for (int i = 0; i < _vYb.size(); ++i)
		{
			if (_vYb[i]->isDeathDeleteState)	//죽었고 신호 들어오면
			{
				RENDERMANAGER->deleteObj("yellowBaseball", i);	
				_vYb.erase(_vYb.begin() + i);	//딜리트하자
				break;
			}
		}
	}

	//노란색 베이스볼끼리 충돌
	if(!_vYb.empty())
	{
		for (int i = 0; i < _vYb.size() - 1; i++)
		{
			for (int j = i + 1; j < _vYb.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vYb[i]->getShadowRect(), &_vYb[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vYb[i]->getShadowY() < _vYb[j]->getShadowY())
						{
							_vYb[i]->setShadowY(_vYb[i]->getShadowY() - height);
							_vYb[i]->setY(_vYb[i]->getShadowY() - 295);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vYb[i]->setShadowY(_vYb[i]->getShadowY() + height);
							_vYb[i]->setY(_vYb[i]->getShadowY() - 295);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vYb[i]->getShadowX() < _vYb[j]->getShadowX())
						{
							_vYb[i]->setShadowX(_vYb[i]->getShadowX() - width);
							_vYb[i]->setX(_vYb[i]->getShadowX() - 200);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vYb[i]->setShadowX(_vYb[i]->getShadowX() + width);
							_vYb[i]->setX(_vYb[i]->getShadowX() - 200);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}
	

	////////////////
   //   green    //
   ///////////////
	//ATTACK//
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viGb)->getAttackRect()))		//에너미 사거리에 들어오면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viGb)->setIsCollisionAttack(true);		//충돌했으면 bool 값 true로 전환
		}
		else
		{
			(*_viGb)->setIsCollisionAttack(false);		//아니면 false로 전환
		}
	}
	//Damaged//
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viGb)->getRect())
			&& !(*_viGb)->isCollisionDamaged && _player->isattack && !(*_viGb)->isCrash)	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viGb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
			(*_viGb)->isCrash = true;
		}

		if (!_player->isattack) (*_viGb)->isCrash = false;
	}
	//죽은 애들 지워주자
	if (!_vGb.empty())
	{
		for (int i = 0; i < _vGb.size(); ++i)
		{
			if (_vGb[i]->isDeathDeleteState)	//죽었고 신호 들어오면
			{
				RENDERMANAGER->deleteObj("greenBaseball", i);
				_vGb.erase(_vGb.begin() + i);	//딜리트하자
				break;
			}
		}
	}

	//초록이들끼리 충돌
	if (!_vGb.empty())
	{
		for (int i = 0; i < _vGb.size() - 1; i++)
		{
			for (int j = i + 1; j < _vGb.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vGb[i]->getShadowRect(), &_vGb[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vGb[i]->getShadowY() < _vGb[j]->getShadowY())
						{
							_vGb[i]->setShadowY(_vGb[i]->getShadowY() - height);
							_vGb[i]->setY(_vGb[i]->getShadowY() - 295);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vGb[i]->setShadowY(_vGb[i]->getShadowY() + height);
							_vGb[i]->setY(_vGb[i]->getShadowY() - 295);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vGb[i]->getShadowX() < _vGb[j]->getShadowX())
						{
							_vGb[i]->setShadowX(_vGb[i]->getShadowX() - width);
							_vGb[i]->setX(_vGb[i]->getShadowX() - 200);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vGb[i]->setShadowX(_vGb[i]->getShadowX() + width);
							_vGb[i]->setX(_vGb[i]->getShadowX() - 200);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}

	////////////////
   //   blue     //
   ///////////////
	//ATTACK//
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getRect(), &(*_viBb)->getAttackRect()))		//에너미 사거리에 들어오면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBb)->setIsCollisionAttack(true);		//충돌했으면 bool 값 true로 전환
		}
		else
		{
			(*_viBb)->setIsCollisionAttack(false);		//아니면 false로 전환
		}
	}
	//Damaged//
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viBb)->getRect())
			&& !(*_viBb)->isCollisionDamaged && _player->isattack && !(*_viBb)->isCrash)	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBb)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
			(*_viBb)->isCrash = true;
		}

		if (!_player->isattack) (*_viBb)->isCrash = false;
	}
	//죽은 애들 지워주자
	if (!_vBb.empty())
	{
		for (int i = 0; i < _vBb.size(); ++i)
		{
			if (_vBb[i]->isDeathDeleteState)	//죽었고 신호 들어오면
			{
				RENDERMANAGER->deleteObj("blueBaseball", i);
				_vBb.erase(_vBb.begin() + i);	//딜리트하자
				break;
			}
		}
	}

	//파랑이들끼리 충돌
	if (!_vBb.empty())
	{
		for (int i = 0; i < _vBb.size() - 1; i++)
		{
			for (int j = i + 1; j < _vBb.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vBb[i]->getShadowRect(), &_vBb[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vBb[i]->getShadowY() < _vBb[j]->getShadowY())
						{
							_vBb[i]->setShadowY(_vBb[i]->getShadowY() - height);
							_vBb[i]->setY(_vBb[i]->getShadowY() - 295);
							_vBb[i]->setRc(RectMakeCenter(_vBb[i]->getX() + 200, _vBb[i]->getY() + 200, 300, 230));
							_vBb[i]->setShadowRc(RectMakeCenter(_vBb[i]->getShadowX(), _vBb[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vBb[i]->setShadowY(_vBb[i]->getShadowY() + height);
							_vBb[i]->setY(_vBb[i]->getShadowY() - 295);
							_vBb[i]->setRc(RectMakeCenter(_vBb[i]->getX() + 200, _vBb[i]->getY() + 200, 300, 230));
							_vBb[i]->setShadowRc(RectMakeCenter(_vBb[i]->getShadowX(), _vBb[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vBb[i]->getShadowX() < _vBb[j]->getShadowX())
						{
							_vBb[i]->setShadowX(_vBb[i]->getShadowX() - width);
							_vBb[i]->setX(_vBb[i]->getShadowX() - 200);
							_vBb[i]->setRc(RectMakeCenter(_vBb[i]->getX() + 200, _vBb[i]->getY() + 200, 300, 230));
							_vBb[i]->setShadowRc(RectMakeCenter(_vBb[i]->getShadowX(), _vBb[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vBb[i]->setShadowX(_vBb[i]->getShadowX() + width);
							_vBb[i]->setX(_vBb[i]->getShadowX() - 200);
							_vBb[i]->setRc(RectMakeCenter(_vBb[i]->getX() + 200, _vBb[i]->getY() + 200, 300, 230));
							_vBb[i]->setShadowRc(RectMakeCenter(_vBb[i]->getShadowX(), _vBb[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}

	//노랑이랑 파랑이 충돌 처리
	if (!_vYb.empty() && !_vBb.empty())
	{
		for (int i = 0; i < _vYb.size(); i++)
		{
			for (int j = 0; j < _vBb.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vYb[i]->getShadowRect(), &_vBb[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vYb[i]->getShadowY() < _vBb[j]->getShadowY())
						{
							_vYb[i]->setShadowY(_vYb[i]->getShadowY() - height);
							_vYb[i]->setY(_vYb[i]->getShadowY() - 295);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vYb[i]->setShadowY(_vYb[i]->getShadowY() + height);
							_vYb[i]->setY(_vYb[i]->getShadowY() - 295);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vYb[i]->getShadowX() < _vBb[j]->getShadowX())
						{
							_vYb[i]->setShadowX(_vYb[i]->getShadowX() - width);
							_vYb[i]->setX(_vYb[i]->getShadowX() - 200);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vYb[i]->setShadowX(_vYb[i]->getShadowX() + width);
							_vYb[i]->setX(_vYb[i]->getShadowX() - 200);
							_vYb[i]->setRc(RectMakeCenter(_vYb[i]->getX() + 200, _vYb[i]->getY() + 200, 300, 230));
							_vYb[i]->setShadowRc(RectMakeCenter(_vYb[i]->getShadowX(), _vYb[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}

	//초록이랑 글러브 충돌
	if (!_vGb.empty() && !_vGlove.empty())
	{
		for (int i = 0; i < _vGb.size(); i++)
		{
			for (int j = 0; j < _vGlove.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vGb[i]->getShadowRect(), &_vGlove[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vGb[i]->getShadowY() < _vGlove[j]->getShadowY())
						{
							_vGb[i]->setShadowY(_vGb[i]->getShadowY() - height);
							_vGb[i]->setY(_vGb[i]->getShadowY() - 295);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vGb[i]->setShadowY(_vGb[i]->getShadowY() + height);
							_vGb[i]->setY(_vGb[i]->getShadowY() - 295);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vGb[i]->getShadowX() < _vGlove[j]->getShadowX())
						{
							_vGb[i]->setShadowX(_vGb[i]->getShadowX() - width);
							_vGb[i]->setX(_vGb[i]->getShadowX() - 200);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vGb[i]->setShadowX(_vGb[i]->getShadowX() + width);
							_vGb[i]->setX(_vGb[i]->getShadowX() - 200);
							_vGb[i]->setRc(RectMakeCenter(_vGb[i]->getX() + 200, _vGb[i]->getY() + 200, 300, 230));
							_vGb[i]->setShadowRc(RectMakeCenter(_vGb[i]->getShadowX(), _vGb[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
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
	//죽은 애들 지워주자
	if (!_vBat.empty())
	{
		for (int i = 0; i < _vBat.size(); ++i)
		{
			if (_vBat[i]->isDeathDeleteState)	//죽었고 신호 들어오면
			{
				RENDERMANAGER->deleteObj("bat", i);
				_vBat.erase(_vBat.begin() + i);	//딜리트하자
				break;
			}
		}
	}

	//배트들끼리 충돌
	if (!_vBat.empty())
	{
		for (int i = 0; i < _vBat.size() - 1; i++)
		{
			for (int j = i + 1; j < _vBat.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vBat[i]->getShadowRect(), &_vBat[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vBat[i]->getShadowY() < _vBat[j]->getShadowY())
						{
							_vBat[i]->setShadowY(_vBat[i]->getShadowY() - height);
							_vBat[i]->setY(_vBat[i]->getShadowY() - 295);
							_vBat[i]->setRc(RectMakeCenter(_vBat[i]->getX() + 200, _vBat[i]->getY() + 200, 300, 230));
							_vBat[i]->setShadowRc(RectMakeCenter(_vBat[i]->getShadowX(), _vBat[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vBat[i]->setShadowY(_vBat[i]->getShadowY() + height);
							_vBat[i]->setY(_vBat[i]->getShadowY() - 295);
							_vBat[i]->setRc(RectMakeCenter(_vBat[i]->getX() + 200, _vBat[i]->getY() + 200, 300, 230));
							_vBat[i]->setShadowRc(RectMakeCenter(_vBat[i]->getShadowX(), _vBat[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vBat[i]->getShadowX() < _vBat[j]->getShadowX())
						{
							_vBat[i]->setShadowX(_vBat[i]->getShadowX() - width);
							_vBat[i]->setX(_vBat[i]->getShadowX() - 200);
							_vBat[i]->setRc(RectMakeCenter(_vBat[i]->getX() + 200, _vBat[i]->getY() + 200, 300, 230));
							_vBat[i]->setShadowRc(RectMakeCenter(_vBat[i]->getShadowX(), _vBat[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vBat[i]->setShadowX(_vBat[i]->getShadowX() + width);
							_vBat[i]->setX(_vBat[i]->getShadowX() - 200);
							_vBat[i]->setRc(RectMakeCenter(_vBat[i]->getX() + 200, _vBat[i]->getY() + 200, 300, 230));
							_vBat[i]->setShadowRc(RectMakeCenter(_vBat[i]->getShadowX(), _vBat[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}
}
void enemyManager::gloveCollision()
{
	////////////////
   //    glove   //
   ///////////////
    
   //Attack glove가 공격하는 모션 취하기 위함//
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
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->_attack_rc, &(*_viGlove)->getRect())
			&& !(*_viGlove)->isCollisionDamaged && _player->isattack && !(*_viGlove)->isCrash)												//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viGlove)->setIsCollisionDamaged(true);		//충돌했으면 bool 값 true로 전환
			(*_viGlove)->isCrash = true;
		}
		if (!_player->isattack) (*_viGlove)->isCrash = false;
	}
	//죽은 애들 지워주자
	if (!_vGlove.empty())
	{
		for (int i = 0; i < _vGlove.size(); ++i)
		{
			if (_vGlove[i]->isDeathDeleteState)	//죽었고 신호 들어오면
			{
				RENDERMANAGER->deleteObj("glove", i);
				_vGlove.erase(_vGlove.begin() + i);	//딜리트하자
				break;
			}
		}
	}

	//글러브들끼리 충돌
	if (!_vGlove.empty())
	{
		for (int i = 0; i < _vGlove.size() - 1; i++)
		{
			for (int j = i + 1; j < _vGlove.size(); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &_vGlove[i]->getShadowRect(), &_vGlove[j]->getShadowRect()))	//에너미 몸과 충돌하면.. 다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
				{
					float width = temp.right - temp.left;
					float height = temp.bottom - temp.top;
					//상하충돌
					if (width > height)
					{
						//i 가 j 위에서 충돌
						if (_vGlove[i]->getShadowY() < _vGlove[j]->getShadowY())
						{
							_vGlove[i]->setShadowY(_vGlove[i]->getShadowY() - height);
							_vGlove[i]->setY(_vGlove[i]->getShadowY() - 295);
							_vGlove[i]->setRc(RectMakeCenter(_vGlove[i]->getX() + 200, _vGlove[i]->getY() + 200, 300, 230));
							_vGlove[i]->setShadowRc(RectMakeCenter(_vGlove[i]->getShadowX(), _vGlove[i]->getShadowY(), 215, 50));
						}
						else //아래에서 충돌
						{
							_vGlove[i]->setShadowY(_vBat[i]->getShadowY() + height);
							_vGlove[i]->setY(_vBat[i]->getShadowY() - 295);
							_vGlove[i]->setRc(RectMakeCenter(_vGlove[i]->getX() + 200, _vGlove[i]->getY() + 200, 300, 230));
							_vGlove[i]->setShadowRc(RectMakeCenter(_vGlove[i]->getShadowX(), _vGlove[i]->getShadowY(), 215, 50));
						}
					}
					else
					{
						//왼쪽에서 충돌
						if (_vGlove[i]->getShadowX() < _vGlove[j]->getShadowX())
						{
							_vGlove[i]->setShadowX(_vGlove[i]->getShadowX() - width);
							_vGlove[i]->setX(_vGlove[i]->getShadowX() - 200);
							_vGlove[i]->setRc(RectMakeCenter(_vGlove[i]->getX() + 200, _vGlove[i]->getY() + 200, 300, 230));
							_vGlove[i]->setShadowRc(RectMakeCenter(_vGlove[i]->getShadowX(), _vGlove[i]->getShadowY(), 215, 50));
						}
						else //오른쪽에서 충돌
						{
							_vGlove[i]->setShadowX(_vGlove[i]->getShadowX() + width);
							_vGlove[i]->setX(_vGlove[i]->getShadowX() - 200);
							_vGlove[i]->setRc(RectMakeCenter(_vGlove[i]->getX() + 200, _vGlove[i]->getY() + 200, 300, 230));
							_vGlove[i]->setShadowRc(RectMakeCenter(_vGlove[i]->getShadowX(), _vGlove[i]->getShadowY(), 215, 50));
						}
					}
				}
			}
		}
	}

}

void enemyManager::setBat1()
{
	//STAGE1
	for (int i = 0; i < 2; i++)
	{
		bat* _bat = new bat;
		_bat->init(PointMake(1150 + i * 300, 220 + i * 100));
		_vBat.push_back(_bat);
	}
	////이렇게 나눠줄 순 없나..
	//for (int i = 0; i < 5; i++)
	//{
	//	bat* _bat1 = new bat;
	//	bat* _bat3 = new bat;
	//	
	//	_bat1->init(PointMake(1150 + i * 300, 220 + i * 100));
	//	_vBat.push_back(_bat1);
	//
	//	_bat3->init(PointMake(1150 + i * 300, 220 + i * 100));
	//	_vBat.push_back(_bat3);
	//}
}
void enemyManager::setBat2()
{
	//STAGE3
	for (int i = 0; i < 3; i++)
	{
		bat* _bat = new bat;
		_bat->init(PointMake(650 + i * 50, 150 + i * 150));
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
		_glove->init(PointMake(3500 + i * 300, 250 + i * 100));	//스테이지1 제일 우측 끝에서 나옴		//x : 3500
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

//카메라 밖 나가지 않게
void enemyManager::wallLocation()
{
	////////////////
   //   blue      //
   /////////////////
	for (_viBb = _vBb.begin(); _viBb != _vBb.end(); ++_viBb)
	{
		//위
		if ((*_viBb)->getY() <= 162)		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBb)->setY(162);
		}
		//아래
		if ((*_viBb)->getY() >= CAMERAMANAGER->getCameraBOTTOM())
		{
			(*_viBb)->setY((*_viBb)->getY() - 3);
		}
		//좌
		if ((*_viBb)->getX() <= CAMERAMANAGER->getCameraLEFT())
		{
			(*_viBb)->setX((*_viBb)->getX() + 3);
		}
		//우
		if ((*_viBb)->getRect().right >= CAMERAMANAGER->getCameraRIGHT())
		{
			(*_viBb)->setX((*_viBb)->getX() - 3);
		}
	}


	////////////////
   //   green    //
   ///////////////
	for (_viGb = _vGb.begin(); _viGb != _vGb.end(); ++_viGb)
	{
		//위
		if ((*_viGb)->getY() <= 162)		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viGb)->setY(162);
		}
		//아래
		if ((*_viGb)->getY() >= CAMERAMANAGER->getCameraBOTTOM())
		{
			(*_viGb)->setY((*_viGb)->getY() - 3);
		}
		//좌
		if ((*_viGb)->getX() <= CAMERAMANAGER->getCameraLEFT())
		{
			(*_viGb)->setX((*_viGb)->getX() + 3);
		}
		//우
		if ((*_viGb)->getRect().right >= CAMERAMANAGER->getCameraRIGHT())
		{
			(*_viGb)->setX((*_viGb)->getX() - 3);
		}
	}

	////////////////
   //   yellow   //
   ///////////////
	for (_viYb = _vYb.begin(); _viYb != _vYb.end(); ++_viYb)
	{
		//위
		if ((*_viYb)->getY() <= 162)		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viYb)->setY(162);
		}
		//아래
		if ((*_viYb)->getY() >= CAMERAMANAGER->getCameraBOTTOM())
		{
			(*_viYb)->setY((*_viYb)->getY() - 3);
		}
		//좌
		if ((*_viYb)->getX() <= CAMERAMANAGER->getCameraLEFT())
		{
			(*_viYb)->setX((*_viYb)->getX() + 3);
		}
		//우
		if ((*_viYb)->getRect().right >= CAMERAMANAGER->getCameraRIGHT())
		{
			(*_viYb)->setX((*_viYb)->getX() - 3);
		}
	}

	////////////////
   //   white    //
   ///////////////
	for (_viWb = _vWb.begin(); _viWb != _vWb.end(); ++_viWb)
	{
		//위
		if ((*_viWb)->getY() <= 162)		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viWb)->setY(162);
		}
		//아래
		if ((*_viWb)->getY() >= CAMERAMANAGER->getCameraBOTTOM())
		{
			(*_viWb)->setY((*_viWb)->getY() - 3);
		}
		//좌
		if ((*_viWb)->getX() <= CAMERAMANAGER->getCameraLEFT())
		{
			(*_viWb)->setX((*_viWb)->getX() + 3);
		}
		//우
		if ((*_viWb)->getRect().right >= CAMERAMANAGER->getCameraRIGHT())
		{
			(*_viWb)->setX((*_viWb)->getX() - 3);
		}
	}

	////////////////
   //   bat      //
   ///////////////
	for (_viBat = _vBat.begin(); _viBat != _vBat.end(); ++_viBat)
	{
		//위
		if ((*_viBat)->getY() <= CAMERAMANAGER->getCameraTOP())		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viBat)->setY((*_viBat)->getY() + 3);
		}
		//아래
		if ((*_viBat)->getY() >= CAMERAMANAGER->getCameraBOTTOM())
		{
			(*_viBat)->setY((*_viBat)->getY() - 3);
		}
		//좌
		if ((*_viBat)->getX() <= CAMERAMANAGER->getCameraLEFT())
		{
			(*_viBat)->setX((*_viBat)->getX() + 3);
		}
		//우
		if ((*_viBat)->getRect().right >= CAMERAMANAGER->getCameraRIGHT())
		{
			(*_viBat)->setX((*_viBat)->getX() - 3);
		}
	}

	////////////////
   //   glove    //
   ///////////////
	for (_viGlove = _vGlove.begin(); _viGlove != _vGlove.end(); ++_viGlove)
	{
		//위
		if ((*_viGlove)->getY() <= CAMERAMANAGER->getCameraTOP())		//충돌하면..	다른 상태에서 충돌 여부 판별하여 상태 변경하기 위함
		{
			(*_viGlove)->setY((*_viGlove)->getY() + 3);
		}
		//아래
		if ((*_viGlove)->getY() >= CAMERAMANAGER->getCameraBOTTOM())
		{
			(*_viGlove)->setY((*_viGlove)->getY() - 3);
		}
		//좌
		if ((*_viGlove)->getX() <= CAMERAMANAGER->getCameraLEFT())
		{
			(*_viGlove)->setX((*_viGlove)->getX() + 3);
		}
		//우
		if ((*_viGlove)->getRect().right >= CAMERAMANAGER->getCameraRIGHT())
		{
			(*_viGlove)->setX((*_viGlove)->getX() - 3);
		}
	}
	
}

//플레이어 위치 찾는 함수
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

//////////////////////////////////////////////////
//			카드 에너미 세팅
//////////////////////////////////////////////////
void enemyManager::setCard()
{
	for (int i = 0; i < 2; i++)
	{
		card* _cd;
		_cd = new card;
		_cd->init(PointMake(2650 + i * 120, 220 + i * 100));
		_vCard.push_back(_cd);
	}
}


//////////////////////////////////////////////////
//			카드 에너미 업데이트
//////////////////////////////////////////////////
void enemyManager::updateCard()
{
	//카드 업데이트
	WhereIsCard();
	assultedCollisionCard();

	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		(*_viCard)->update();
	}
}


//////////////////////////////////////////////////
//			카드 에너미 렌더
//////////////////////////////////////////////////
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
			if (_player->_shadow->getCenterX() > (*_viCard)->getShadowX())
			{
				(*_viCard)->setIsLeft(false);
			}

			//플레이어보다 오른쪽에 있을때
			if (_player->_shadow->getCenterX() < (*_viCard)->getShadowX())
			{
				(*_viCard)->setIsLeft(true);
			}

			//플레이어보다 위에 있을때
			if (_player->_shadow->getCenterY() > (*_viCard)->getShadowY())
			{
				(*_viCard)->setIsUpper(true);
			}

			//플레이어보다 아래에 있을때
			if (_player->_shadow->getCenterY() < (*_viCard)->getShadowY())
			{
				(*_viCard)->setIsUpper(false);
			}

			RECT temp;
			if (IntersectRect(&temp, &_player->getRect(), &(*_viCard)->getAtkCardRc())
				&& !(*_viCard)->_isCrash)
			{
				(*_viCard)->numPattern = rand() % 5;
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
	for (_viCard = _vCard.begin(); _viCard != _vCard.end(); ++_viCard)
	{
		if ((*_viCard)->_isCardMoveState && _player->isattack)
		{
			RECT temp;
			if (IntersectRect(&temp, &(*_viCard)->_assultedRect, &_player->_attack_rc))
			{
				//그린
				if (_player->_isGreenAttack1 || _player->_isGreenAttack2 ||
					_player->_isGreenAttack3 || _player->_isGreenDashAttack ||
					_player->_isGreenJumpAttack)
				{
					(*_viCard)->_isCardSmallDamaged = true;
				}

				if (_player->_isGreenDashAlt || _player->_isGreenJumpPowerAttack)
				{
					(*_viCard)->_isCardHeavyDamaged = true;
				}

				//레드
				if (_player->_isRedAttack1 || _player->_isRedAttack2 ||
					_player->_isRedAttack3 || _player->_isRedJumpAttack || 
					_player->_isRedSliding)
				{
					(*_viCard)->_isCardSmallDamaged = true;
				}

				if (_player->_isRedHomeRunAttack)
				{
					(*_viCard)->_isRedHomeRunAttack = true;
					(*_viCard)->_isCardHeavyDamaged = true;
				}

				if (_player->_isRedDashAttack || _player->_isRedLegKickAttack)
				{
					(*_viCard)->_isCardHeavyDamaged = true;
				}

				if (_player->_isRedDynamiteDance)
				{
					(*_viCard)->_isRedDynamiteDance = true;
					(*_viCard)->_isCardSmallDamaged = true;
				}
			}
		}

		//필살기 종료 신호 보내기
		if (!_player->_isRedDynamiteDance) (*_viCard)->_isRedDynamiteDance = false;

		if ((*_viCard)->_isCardSmallDamagedState && _player->isattack)
		{
			RECT temp;
			if (IntersectRect(&temp, &(*_viCard)->_assultedRect, &_player->_attack_rc))
			{
				//그린
				if (_player->_isGreenAttack1)
				{
					(*_viCard)->_isCardSmallDamaged = true;
					(*_viCard)->_isGreenAttack1 = true;
				}

				if (_player->_isGreenAttack2 || _player->_isGreenAttackFrontCombo1)
				{
					(*_viCard)->_isGreenAttack2 = true;
				}

				if (_player->_isGreenAttack3 || _player->_isGreenAttackFrontCombo2)
				{
					(*_viCard)->_isGreenAttack3 = true;
				}

				//레드
				if (_player->_isRedAttack1)
				{
					(*_viCard)->_isCardSmallDamaged = true;
					(*_viCard)->_isRedAttack1 = true;
				}

				if (_player->_isRedAttack2)
				{
					(*_viCard)->_isRedAttack2 = true;
				}

				if (_player->_isRedAttack3)
				{
					(*_viCard)->_isRedAttack3 = true;
				}

				if (_player->_isRedHomeRunAttack)
				{
					(*_viCard)->_isRedHomeRunAttack = true;
				}
			}
		}
		//레드 지지고 볶기 (다운어택 아직 구현못하신듯)
		//if ((*_viCard)->_isCardLandState && _player->)

		//레드가 캐치하기위한
		if ((*_viCard)->_isCardMoveState && _player->_isRedGrip)
		{
			RECT temp;
			if (IntersectRect(&temp, &(*_viCard)->_assultedRect, &_player->getRect()))
			{
				_player->iscatch = true;
				(*_viCard)->_isRedCatch = true;
				(*_viCard)->_isCardSmallDamaged = true;
			}
		}

		if ((*_viCard)->_isCardSmallDamagedState && _player->iscatch)
		{
			if (_player->_isRedCatchAttack && !_player->_isRedCatchAttackOn)
			{
				(*_viCard)->_isRedCatchAttack = true;
				_player->_isRedCatchAttackOn = true;
			}

			if (_player->_isRedHomeRunAttack &&
				!(*_viCard)->_isRedHomeRunAttack)
			{
				(*_viCard)->_isRedHomeRunAttack = true;
				_player->_isRedHomeRunAttack = false;
			}

			if (_player->_isRedThrow &&
				!(*_viCard)->_isRedThrow)
			{
				(*_viCard)->_isRedThrow = true;
				_player->_isRedThrow = false;
			}
		}

		//그린이 캐치하기 위한
		if ((*_viCard)->_isCardMoveState && _player->iscrawl)
		{
			RECT temp;
			if (IntersectRect(&temp, &(*_viCard)->_assultedRect, &_player->getRect()))
			{
				_player->iscatch = true;
				(*_viCard)->_isGreenCatch = true;
				(*_viCard)->_isCardSmallDamaged = true;
			}
		}

		if ((*_viCard)->_isCardSmallDamagedState && _player->iscatch)
		{
			if (_player->_isGreenCatchAttack)
			{
				(*_viCard)->_isGreenCatchAttack = true;
				_player->_isGreenCatchAttack = false;
			}

			if (_player->_isGreenCatchBackAttack &&
				!(*_viCard)->_isGreenCatchBackAttack)
			{
				(*_viCard)->_isGreenCatchBackAttack = true;
				_player->_isGreenCatchBackAttack = false;
			}

			if (_player->_isGreenCatchFrontCombo &&
				!(*_viCard)->_isGreenCatchFrontCombo)
			{
				(*_viCard)->_isGreenCatchFrontCombo = true;
				_player->_isGreenCatchFrontCombo = false;
			}
		}

		if (!_player->iscatch)
		{
			(*_viCard)->_isGreenCatch = false;
			(*_viCard)->_isRedCatch = false;
		}
	}

	if (!_vCard.empty())
	{
		//사라져라 카드여//
		for (int i = 0; i < _vCard.size(); ++i)
		{
			if (_vCard[i]->_isDeathState)
			{
				RENDERMANAGER->deleteObj("card", i);
				_vCard.erase(_vCard.begin() + i);
				break;
			}
		}
	}
}


/////////////////////////////////
//  ######보스 위치 선정 ########
/////////////////////////////////
void enemyManager::setBoss()
{
	_boss = new boss;
	_boss->init(PointMake(1300, 150));
}

/////////////////////////////////
// ######보스 업데이트 항목 ########
/////////////////////////////////
void enemyManager::updateBoss()
{
	_boss->update();
	WhereIsBoss();				//보스<->플레이어 위치 확인용
	attackCollision();
	assultedCollisionBoss();
}

/////////////////////////////////
//  ######보스 그리기 ########
/////////////////////////////////
void enemyManager::renderBoss()
{
	_boss->render();
}

void enemyManager::pinRender()
{
	_boss->pinRender();
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

	/////////////////////////////////////////////
	// #######  보스 wind 바람등장 ##########   //
	/////////////////////////////////////////////
	if (_boss->_isWindState)
	{
		_boss->_windCnt++;
		_boss->_windPower += _boss->_windInerita;

		if (_boss->_windCnt <= 20)
		{
			_player->setX(_player->getX() - _boss->_windPower);
			_player->setShadowX(_player->getX());
		}

		if (_boss->_windCnt > 22)
		{
			_boss->_windPower = 5.5f;
			_boss->_windCnt = 0;
		}

		if (_player->getX() < CAMERAMANAGER->getCameraLEFT())
		{
			_player->setX(CAMERAMANAGER->getCameraLEFT() + 65);
			_player->setShadowX(_player->getX());
		}

		if (_player->getRect().left < 100)
		{
			_boss->_isWindState = false;
			_player->setX(_player->getX() + _boss->_windPower);
			_player->setShadowX(_player->getX());
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
			//그린이
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

			//레드
			if (_player->_isRedAttack1 || _player->_isRedAttack2 ||
				_player->_isRedAttack3 || _player->_isRedJumpAttack ||
				_player->_isRedSliding)
			{
				_boss->_isSmallDamaged = true;
			}

			if (_player->_isRedHomeRunAttack)
			{
				_boss->_isRedHomeRunAttack = true;
				_boss->_isDamaged = true;
			}

			if (_player->_isRedDashAttack || _player->_isRedLegKickAttack)
			{
				_boss->_isDamaged = true;
			}

			if (_player->_isRedDynamiteDance)
			{
				_boss->_isRedDynamiteDance = true;
				_boss->_isSmallDamaged = true;
			}
		}
	}

	//필살기 종료 신호 보내기
	if (!_player->_isRedDynamiteDance) _boss->_isRedDynamiteDance = false;

	if (_boss->_isSmallDamagedState && _player->isattack)
	{
		RECT temp;
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->_attack_rc))
		{
			// 그린이
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

			//레드
			if (_player->_isRedAttack1)
			{
				_boss->_isSmallDamaged = true;
				_boss->_isRedAttack1 = true;
			}

			if (_player->_isRedAttack2)
			{
				_boss->_isRedAttack2 = true;
			}

			if (_player->_isRedAttack3)
			{
				_boss->_isRedAttack3 = true;
			}

			if (_player->_isRedHomeRunAttack)
			{
				_boss->_isRedHomeRunAttack = true;
			}
		}
	}

	//그린좌 잡기
	RECT temp;
	if (IntersectRect(&temp, &_boss->_assultedRect, &_player->getRect()))
	{
		if (_boss->_isMoveState && _player->iscrawl)
		{
			_player->iscatch = true;
			_boss->_isGreenCatch = true;
			_boss->_isSmallDamaged = true;
		}
	}

	//그린좌 잡기 공격
	if (_boss->_isSmallDamagedState && _player->iscatch)
	{
		if (_player->_isGreenCatchAttack &&
			!_boss->_isGreenCatchAttack)
		{
			_boss->_isGreenCatchAttack = true;
			_player->_isGreenCatchAttack = false;
		}

		if (_player->_isGreenCatchBackAttack &&
			!_boss->_isGreenCatchBackAttack)
		{
			_boss->_isGreenCatchBackAttack = true;
			_player->_isGreenCatchBackAttack = false;
		}

		if (_player->_isGreenCatchFrontCombo && 
			!_boss->_isGreenCatchFrontCombo)
		{
			_boss->_isGreenCatchFrontCombo = true;
			_player->_isGreenCatchFrontCombo = false;
		}
	}

	//레드좌 잡기
	if (_boss->_isMoveState && _player->_isRedGrip)
	{
		if (IntersectRect(&temp, &_boss->_assultedRect, &_player->getGripRect()))
		{
			_player->iscatch = true;
			_boss->_isRedCatch = true;
			_boss->_isSmallDamaged = true;
		}
	}


	if (_boss->_isSmallDamagedState && _player->iscatch)
	{
		if (_player->_isRedCatchAttack && !_player->_isRedCatchAttackOn &&
			!_boss->_isRedCatchAttack)
		{
			_boss->_isRedCatchAttack = true;
			_player->_isRedCatchAttackOn = true;
		}

		if (_player->_isRedHomeRunAttack &&
			!_boss->_isRedHomeRunAttack)
		{
			_boss->_isRedHomeRunAttack = true;
			_player->_isRedHomeRunAttack = false;
		}

		if (_player->_isRedThrow &&
			!_boss->_isRedThrow)
		{
			_boss->_isRedThrow = true;
			_player->_isRedThrow = false;
		}
	}

	//레드좌 잡기공격

	//잡기 풀면 다풀려요
	if (!_player->iscatch)
	{
		_boss->_isGreenCatch = false;
		_boss->_isRedCatch = false;
	}
}

bool enemyManager::isAllDead()
{
	if (_vWb.empty() && _vYb.empty() && _vGb.empty() && _vBb.empty() && _vBat.empty() && _vGlove.empty() && _vCard.empty())
	{
		return true;
	}
	return false;
}
