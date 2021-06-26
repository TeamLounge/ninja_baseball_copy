#include "stdafx.h"
#include "Ryno_jump.h"
#include "player.h"
#include "Ryno_idle.h"
#include "Ryno_fly.h"
playerstate * Ryno_jump::handleInput(player * player)
{
	//이부분도 나중에 바꿔야할것같음..
	if (_jumpPower < -10)
	{
		return new Ryno_idle;
	}   
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&&KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new Ryno_fly;
	}
 	return nullptr;
}

void Ryno_jump::update(player * player)
{
	//랜더 카운터
	_count++;
	//점프중력
	player->setY(player->getY() - _jumpPower);
	_jumpPower -= _gravity;

	//움직이기
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setX(player->getX() - 5);
		player->isRight = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + 5);
		player->isRight = true;
	} 
	//z키누르면 공격상태
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		isattack = true;
	}
	//좌우 구분하기위해서
	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else if(!player->isRight)
	{
		player->getImage()->setFrameY(1);
	}

	//공격키를 눌렀을때 공격상태로  아직 렉트는 씌우지않음
	//공격일때 플레이어의 공격렉트를 따로 띄울생각입니다
	//마지막인덱스일떄 공격렉트를 띄우는거죠
 	if (isattack)
	{
		if (_count % 4 == 0)
		{
			_index++;
			//여기부터가 마지막 인덱스 공격렉트를 띄울부분
			if (_index >= 4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				_index = 6;
			}
			else if (_index > 5)
			{
				_index = 5;
			}
			//여기까지
			player->getImage()->setFrameX(_index);
		}
	}

	//그림자 위치조정
	//그림자는 점프했을때 x로만 움직이게 해놨어요
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	
	
}

void Ryno_jump::enter(player * player)
{

	_count = _index = 0;
	
	_jumpPower = 10.0f;
	_gravity = 0.2f;

	isattack = false;
	
	//플레이어의 이미지,렉트,그림자 초기화
	player->setImage(IMAGEMANAGER->findImage("Ryno_jumpAttack"));
	rc = RectMakeCenter(player->getX(), player->getY(), player->getImage()->getFrameWidth(), player->getImage()->getFrameHeight());
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90 );

	//좌우구분
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
