#include "stdafx.h"
#include "Ryno_frontCombo.h"
#include "Ryno_idle.h"
#include "player.h"
playerstate * Ryno_frontCombo::handleInput(player * player)
{
	if (isend)
	{
		return new Ryno_idle;
	}

	return nullptr;
}

void Ryno_frontCombo::update(player * player)
{

	if (_index < 5) {
		
		_count++;
		if (_count % 5 == 0) {
			//마찬가지로 인덱스를 0~4까지만돌려요
			if (_index < 4) _index++;
			//여기가 인덱스 5일때 결정하는 시간입니다.
			//이떄도 랜더용 카운트를 시간으로 썻습니다..
			if (_count < 50) {
				if (_index==4 && KEYMANAGER->isOnceKeyDown('Z'))
				{
					_index++;
					_count = 0;
				}
			}
			else isend = true;
			//결정했다면 공격을 계속 이어나갑니다.
		}
	}
	if (_index == 5)
	{
		_count++;
		if (_count %  12== 0) {
			_index++;
			//인덱스가 총프레임에 넘어가면 없애버리기 
			_count = 0;
		}
	}
	//인덱스가 총프레임에 넘어가면 없애버리기 
	if (_index >= 6)
	{
		_count++;
		if (_count % 15 == 0)
		{
			_index++;
		}
		if(player->isRight) player->setX(player->getX() + 3);
		else player->setX(player->getX() - 3);
		if (_index > 7)
		isend = true;

	}

	player->getImage()->setFrameX(_index);
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
}

void Ryno_frontCombo::enter(player * player)
{

	_count = _index = 0;
	//이 bool변수가 공격이끝났는지를 체크합니다.
	isend = false;

	player->setImage(IMAGEMANAGER->findImage("Ryno_attack_front"));
	_rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(_rc);
	//여기player->setY해라
	player->setY(player->_shadow->getY() - 120);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 120);

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
