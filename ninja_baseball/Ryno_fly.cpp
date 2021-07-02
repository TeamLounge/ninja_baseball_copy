#include "stdafx.h"
#include "Ryno_fly.h"
#include "Ryno_fall.h"
playerstate * Ryno_fly::handleInput(player * player)
{
	if (isend)
	{
		player->isattack = false;
		player->_isGreenJumpPowerAttack = false;
		return new Ryno_fall;
	}
	return nullptr;
}

void Ryno_fly::update(player * player)
{

	//날다가
	if (_index < 2)
	{
		_count++;
		_commandTime++;
		if (_count % 2 == 0)
		{
			_index++;
			if (_index > 1) _index = 0;
			//커맨드 시간안에 공격키누르면 쏜다! 근데 아직 렉트는 안띄워봣음 ㅋㅋ..
			if (_commandTime < 50)
			{
				if (KEYMANAGER->isOnceKeyDown('X')&& (player->getY() < _top))
				{
					player->isfly = true;
					player->_isGreenJumpPowerAttack = true;
				}
			}
			//커맨드 시간안에 공격키 안누르면 끝!
			else if (_commandTime > 50 && !next)
				isend = true;
			_count = 0;

		}
		//이 행동안에 지정해둔 천장까지 계속 올라가게 천장 기준은 그림자로 잡았어요 
		if (player->getY() >= _top)
		{
			if (player->isRight) {
				player->setY(player->getY() - 20);
				player->setX(player->getX() - 2);
			}
			else
			{
				player->setY(player->getY() - 20);
				player->setX(player->getX() + 2);
			}

		}
	}

	//이거는 공격했다면 공격렉트를 쏠겁니다
	if (_index<2 && player->isfly)
	{
		_actiontime++;
		next = true;
		second += TIMEMANAGER->getElapsedTime();
		if (second >= 0.05f)
		{
			player->isattack = true;
			second -= 0.06f;
		}
		else
			player->isattack = false;
		
		

		if(player->isRight)
		{
			player->_effect->setCenter((player->getX() + (player->getRect().right - player->getRect().left) / 2) + cosf(0.75) * 20, (player->getY() + (player->getRect().bottom - player->getRect().top) / 2) + sinf(0.75) * 2);
			player->_effect1->setCenter(player->_effect->getCenterX()+ cosf(0.75) * 40 , player->_effect->getY() + player->_effect->getHeight() +sinf(0.75) * 10);
			player->_effect2->setCenter(player->_effect1->getCenterX()  + cosf(0.75) * 60, player->_effect1->getY() + player->_effect1->getHeight() + sinf(0.75) * 15);
			player->_effect3->setCenter(player->_effect2->getCenterX() + cosf(0.75) * 90, player->_effect2->getY() + player->_effect2->getHeight() + sinf(0.75) * 20);
			player->_attack_rc = RectMakeCenter(player->getX() + cosf(0.75) * 300, player->getY() + sinf(0.75) * 440, 150, 150);
		}
		else
		{
			player->_effect->setCenter((player->getX() - (player->getRect().right - player->getRect().left) / 2) + cosf(2.35) * 20, (player->getY() + (player->getRect().bottom - player->getRect().top) / 2) + sinf(2.32) * 2);
			player->_effect1->setCenter(player->_effect->getCenterX() + cosf(2.35) * 40, player->_effect->getY() + player->_effect->getHeight() + sinf(2.32) * 10);
			player->_effect2->setCenter(player->_effect1->getCenterX() + cosf(2.35) * 60, player->_effect1->getY() + player->_effect1->getHeight() + sinf(2.32) * 15);
			player->_effect3->setCenter(player->_effect2->getCenterX() + cosf(2.35) * 90, player->_effect2->getY() + player->_effect2->getHeight() + sinf(2.32) * 20);
			player->_attack_rc = RectMakeCenter(player->getX() + cosf(2.32) * 300, player->getY() + sinf(2.32) * 400, 150, 150);
		}
		//공격렉트를 이정도 시간동안 띄우고  시간이 지나면 다음 행동으로 넘어가게 합니다. 나머지 안쓸것도 다 0으로 초기화 해주구요
		if (_actiontime > 50)
		{
			player->isfly = false;
			player->isattack = false;
			_index = 2;
			_actiontime = 0;
			_commandTime = 0;
			_count = 0;
		}
	}

	//그다음 내리찍기부분
	if (_index == 2)
	{
		if(player->isRight)
			player->_attack_rc = RectMakeCenter(player->getX()+90, player->getY() + (player->getImage()->getFrameHeight() / 2), 80, 50);
		else
			player->_attack_rc = RectMakeCenter(player->getX() - 90, player->getY() + (player->getImage()->getFrameHeight() / 2), 80, 50);

		//여기는 카운트를 할 필요가 없었어요 바닥에 닿을때까지 가게합니다
		//찍을때 아마 공격렉트부분을 또 만들껍니다.
		if (player->getY()+(player->getImage()->getFrameHeight()/2) < player->_shadow->getY())
		{
			if (player->isRight) 
			{
				player->setX(player->getX() + cosf(0.75) * 30);
				player->setY(player->getY() + sinf(0.75) * 40);
			}
			else
			{
				player->setX(player->getX() + cosf(0.75) * -30);
				player->setY(player->getY() + sinf(0.75) * 40);
			}
		}
		else
		{
			//바닥찍으면 다음단계로
			_index++;
		}
	}


	//마지막단계  
	if (_index == 3)
	{
		player->isattack = false;
		_actiontime++;
		//마무리를 일단 액션시간으로 가게 했어요 이다음을 어떻게 해야할지모르겟네요
		//새롭게 falling 상태를 만들어서 떨어지게 하려구요
		if(_actiontime < 30)
		{
			if (player->isRight)
			{
				player->setX(player->getX() + 2);
				player->setY(player->getY() - 5);
			}
			else
			{
				player->setX(player->getX() - 2);
				player->setY(player->getY() - 5);
			}
		}
		//바닥에 닿으면 끝
		else if (player->getY() + (player->getImage()->getFrameHeight() / 2) < player->_shadow->getY())
		{
			if (player->isRight)
			{
				player->setX(player->getX() + 2);
				player->setY(player->getY() + 10);
			}
			else
			{
				player->setX(player->getX() - 2);
				player->setY(player->getY() + 10);
			}
		}
		else
			isend = true;
	}



	if (player->isRight)
	{
		player->getImage()->setFrameY(0);
	}
	else
	{
		player->getImage()->setFrameY(1);
	}

	player->getImage()->setFrameX(_index);

	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX() - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
}

void Ryno_fly::enter(player * player)
{
	_count = _index = 0;
	_actiontime = _commandTime = second=  0;

	next = false;
	player->isattack = false;
	isend = false;
	//플레이어의 이미지,렉트,그림자 초기화
	player->setImage(IMAGEMANAGER->findImage("Ryno_fly"));
	rc = RectMakeCenter(player->getX(), player->getY(), 140, 197);
	player->setRect(rc);
	player->_shadow->setX(player->getX()  - (player->_shadow->getWidth() / 2));

	player->setShadowX(player->getX() - (player->_shadow->getWidth() / 2) + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);

	//어디까지 올라가는지 항상 일정하게 하기위해  xx 천장 변수를 만들엇습니다
	_top = player->_shadow->getY()-350;
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

	player->setImageName("Ryno_fly");
}
