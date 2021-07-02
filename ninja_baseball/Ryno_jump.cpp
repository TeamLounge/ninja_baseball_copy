#include "stdafx.h"
#include "Ryno_jump.h"
#include "player.h"
#include "Ryno_fall.h"
#include "Ryno_damage.h"
#include "Ryno_fly.h"
playerstate * Ryno_jump::handleInput(player * player)
{
	//이부분도 나중에 바꿔야할것같음..
	if (_jumpPower < 0 && player->getY() + (player->getImage()->getFrameHeight() / 2) > player->_shadow->getY())
	{
		player->_isGreenJumpAttack = false;
		return new Ryno_fall;
	}   
	if (KEYMANAGER->isOnceKeyDown('X')&&KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->_isGreenJumpAttack = false;
		return new Ryno_fly;
	}
	if (player->isdamage)
	{
		return new Ryno_damage;
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
		player->setX(player->getX() - 7);
		player->isRight = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setX(player->getX() + 7);
		player->isRight = true;
	} 
	//z키누르면 공격상태
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		player->isattack = true;
		player->_isGreenJumpAttack = true;
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
 	if (player->isattack)
	{
		if (_count % 3 == 0)
		{
			_index++;
			//여기부터가 마지막 인덱스 공격렉트를 띄울부분
			if (_index >= 4 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY(), 50, 50);
				_index = 6;
			}
			else if (_index > 5)
			{
				player->_attack_rc = RectMakeCenter(player->getX(), player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				_index = 5;
			}
			//여기까지
			if (_index < 4)
				player->_attack_rc = RectMakeCenter(player->getX(), player->getY(), 50, 50);
			if (_index == 5) {
				if (player->isRight)
				{
					player->_attack_rc = RectMakeCenter(player->getX() + 30, player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				}
				else
				{
					player->_attack_rc = RectMakeCenter(player->getX() - 30, player->getY() + (player->getImage()->getFrameHeight() / 2), 50, 50);
				}
			}
			if (_index == 6) {
				if (player->isRight)
				{
					player->_attack_rc = RectMakeCenter(player->getX() + (player->getImage()->getFrameWidth() / 2), player->getY()+80, 50, 50);
				}
				else
				{
					player->_attack_rc = RectMakeCenter(player->getX() - (player->getImage()->getFrameWidth() / 2), player->getY()+80, 50, 50);
				}
			}
		}
	}
	player->getImage()->setFrameX(_index);
	//그림자 위치조정
	//그림자는 점프했을때 x로만 움직이게 해놨어요
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	
}

void Ryno_jump::enter(player * player)
{

	_count = _index = 0;
	
	_jumpPower = 10.0f;
	_gravity = 0.25f;

	player->isattack = false;
	//플레이어의 이미지,렉트,그림자 초기화
	player->setImage(IMAGEMANAGER->findImage("Ryno_jumpAttack"));
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));
	player->_shadow->setY(player->getY() + 90 );

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
	player->setShadowY(player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);

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

	player->setImageName("Ryno_jumpAttack");
}
