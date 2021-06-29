#include "stdafx.h"
#include "Ryno_attack.h"
#include "Ryno_idle.h"
#include "Ryno_frontCombo.h"
#include "player.h"
playerstate * Ryno_attack::handleInput(player * player)
{
	
	if (isend)
	{
		player->isattack = false;
		return new Ryno_idle;
	}

	if (isfront)
	{
		player->isattack = false;
		return new Ryno_frontCombo;
	}
	return nullptr;
}

void Ryno_attack::update(player * player)
{
	//처음공격할때 현재인덱스가 0이겠죠?
	if (_index < 3) {
		//카운터를 돌려서 프레임인덱스를 다음분기 프레임까지 증가시킵니다
		_count++;
		if (_count % 3 == 0)
		{
			//인덱스는 처음에 0~2까지만올려요
			if(_index<2) _index++;

			//인덱스가 2일때 다음공격분기를 결정해야되요
			//저는 지금 _count변수를 랜더용으로도, 분기마다 시간으로 같이 써버려서 보다가 헷갈리실 수 있어요.
			//사실 이부분은 시간체크용 변수를 따로 생성 한 다음에 
			//if(_index==2) 일때 시간체크변수++ 형식으로 시간체크를 하셔도됩니다.
		
			if (_index==2)
			{
				player->isattack = true;
				if (player->isRight) {
					player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY()-40, 50, 80);
				}
				else
					player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY()-40, 50, 80);
			}
			//현재 인덱스가 2임
			if (_count < 30) {
				//z키를누르면서 앞키를 누르면 새로운 공격패턴으로 갑니다.
				//이것도 상태클래스를 새로 정의하는게 정신건강에 이로워요 ㅋㅋ  저는 안햇는데.. 이거 수정하려구요
				if ((KEYMANAGER->isStayKeyDown(VK_RIGHT)||(KEYMANAGER->isStayKeyDown(VK_LEFT))) && KEYMANAGER->isOnceKeyDown('Z'))
				{

					isfront = true;
					//새로운 공격패턴을 주기위해 이미지를 새로주고 인덱스, 카운터도 처음으로 되돌립니다.
				
				}
				//그냥 z키를 누르면 기본공격만
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
					_count = 0;
					player->isattack = false;
				}
			}
			//결정할 시간이 지났다면 공격을 끝내버려요 
			else
				isend = true;
		}
	}
	//처음공격부분에서 그대로 기본공격을결정했다면
	//다음 기본공격 분기로 옵니다.
	//이 분기에 키를 또 입력하면 계속 공격을 진행해요.
	if (_index == 3)
	{
		_count++;
		player->isattack = true;
		if (player->isRight) {
			player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		}
		else
			player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		//지금도 랜더용카운트를 시간으로 줬는데 어쳐피 지금 상황에선 프레임랜더를 안돌려서도 되서..
		if (_count < 30)
		{
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_index++;
				player->isattack = false;
				//제가 랜더용카운터를 시간으로 썻기 떄문에 항상 랜더용카운터는 0으로 초기화
				_count = 0;
			}
		}
		//시간이 끝나면 공격취소
		else
			isend = true;
	}

	//마지막 분기 
	if (_index > 3)
	{
		//랜더용 카운트
		_count++;
		if (_index == 6) player->isattack = true;
		if (player->isRight) {
			player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		}
		else
			player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
		if (_count % 8 == 0)
		{
			_index++;
			//계속 돌리다가 총프레임의 바깥으로 인덱스가 나가면 공격 끝
			if (_index > 6)
				isend = true;
		}
	}

	
	player->getImage()->setFrameX(_index);
}

void Ryno_attack::enter(player * player)
{
	_count = _index = 0;
	//이 bool변수가 공격이끝났는지를 체크합니다.
	isend = false;
	isfront = false;
	player->setImage(IMAGEMANAGER->findImage("Ryno_attack"));
	_rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(_rc);

	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90);

	if (player->isRight)
	{
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameX(0);
		player->getImage()->setFrameY(1);
	}
}