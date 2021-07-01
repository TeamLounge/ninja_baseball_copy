#include "stdafx.h"
#include "player.h"
#include "Ryno_start.h"
#include "red_idleState.h"
#include "red_moveState.h"
#include "enemyManager.h"

HRESULT player::init(int character)
{

	addImage();
	_character = character;
	_runtime = 0;
	//이건 하나씩 풀꺼입니다.
	if (character == 1) {
		_shadow = IMAGEMANAGER->findImage("red_shadow");
		_state = new red_idleState;
	}

	if (character == 2) {
		_shadow = IMAGEMANAGER->findImage("green_shadow");
		_state = new Ryno_start;
	}

	isRight = true;
	isattack = isdamage = iscrawl = iscatch = false;
	_x = 200;
	_y = WINSIZEY - 200;
	_playerrc = RectMakeCenter(_x, _y, 80, 77);
	_state->enter(this);

	_em = new enemyManager;

	isattack = false;
	isdamage = false;
	iscatch = false;
	iscrawl = false;
	isfly = false;
	if (character == 1)
	{
		RENDERMANAGER->addObj("player", _playerImgName.c_str(), "red_shadow", &_x, &_y, &_shadowX, &_shadowY);
	}
	else if (character == 2)
	{
		RENDERMANAGER->addObj("player", _playerImgName.c_str(), "green_shadow", &_x, &_y, &_shadowX, &_shadowY);
	}

	_hp = 5;
	_life = 3;

	_effect = IMAGEMANAGER->findImage("effect");
	_effect1 = IMAGEMANAGER->findImage("effect1");
	_effect2 = IMAGEMANAGER->findImage("effect2");
	_effect3 = IMAGEMANAGER->findImage("effect3");

	return S_OK;
}

void player::update()
{
	if (_isrun)
	{
		_runtime+=0.1;

		if (_runtime <2)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				_runtime = 0;
				_run = true;
			}
		}
		else
		{
			_runtime = 0;
			_run = false;
			_isrun = false;
		}
	}

	handleInput();
	_state->update(this);

	collision();
}

void player::release()
{
	//RENDERMANAGER->deleteObj("player", 0);
}

void player::render()
{
	char str[128];

	sprintf_s(str, "hp : %d , life : %d",_hp , _life);
	char str2[128];
	sprintf_s(str2, "공격!");
	char str1[128];
	sprintf_s(str1, "x: %f , y: %f", _x , _y);
	TextOut(getMemDC(), _x - (_playerimg->getFrameWidth() / 2) - 100, _shadow->getCenterY() + 40, str1, strlen(str1));
	TextOut(getMemDC(), _x - (_playerimg->getFrameWidth() / 2) - 120, _shadow->getCenterY() + 20, str, strlen(str));
	Rectangle(getMemDC(), _playerrc);

	//이미지랜더
	//_shadow->render(getMemDC());
	//_playerimg->frameRender(getMemDC(), _x - (_playerimg->getFrameWidth() / 2), _y - (_playerimg->getFrameHeight() / 2) );

	TextOut(getMemDC(), _x - (_playerimg->getFrameWidth() / 2)-100, _shadow->getCenterY()+40 , str1, strlen(str1));

	if (isattack)
	{
		Rectangle(getMemDC(), _attack_rc);
		TextOut(getMemDC(), _x - 100, _y - 100, str2, strlen(str2));
	}
	if (isfly)
	{
		_effect->render(getMemDC());
		_effect1->render(getMemDC());
		_effect2->render(getMemDC());
		_effect3->render(getMemDC());
	}
	if (isdamage)
	{
		TextOut(getMemDC(), _x - 100, _y - 100, str, strlen(str));
	}
}

void player::handleInput()
{
	playerstate* state = _state->handleInput(this);
	if (state != nullptr) 
	{
		SAFE_DELETE(_state);
		_state = state;
		_state->enter(this);
	}
}

void player::addImage()
{
	//플레이어(레드) 프레임 이미지
	IMAGEMANAGER->addFrameImage("red_idle", "image/2_player/red/red_idle.bmp", 0, 0, 240, 462, 1, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("red_walk", "image/2_player/red/red_walk.bmp", 0, 0, 1440, 522, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_jump", "image/2_player/red/red_jump.bmp", 0, 0, 231, 498, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_attack", "image/2_player/red/red_attack.bmp", 0, 0, 7344, 630, 16, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_run", "image/2_player/red/red_run.bmp", 0, 0, 768, 480, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_grip2", "image/2_player/red/red_grip2.bmp", 0, 0, 666, 444, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_jumpAttack", "image/2_player/red/red_jumpAttack.bmp", 0, 0, 588, 750, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_idle2", "image/2_player/red/red_idle2.bmp", 0, 0, 396, 510, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_sliding", "image/2_player/red/red_sliding.bmp", 0, 0, 288, 366, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_dashAttack", "image/2_player/red/red_dashAttack.bmp", 0, 0, 192, 444, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_homerun", "image/2_player/red/red_homerun.bmp", 0, 0, 2520, 522, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_damage1", "image/2_player/red/red_damage.bmp", 0, 0, 666, 462, 2, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_damage2", "image/2_player/red/red_damage2.bmp", 0, 0, 234, 396, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_downAttack", "image/2_player/red/red_downAttack.bmp", 0, 0, 792, 480, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_standUp", "image/2_player/red/red_standUp.bmp", 0, 0, 2016, 576, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_legKick", "image/2_player/red/red_legKick.bmp", 0, 0, 3420, 522, 10, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_throw", "image/2_player/red/red_throw.bmp", 0, 0, 2250, 642, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_dynamiteDance", "image/2_player/red/red_dynamiteDance.bmp", 0, 0, 19440, 780, 36, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_damage3", "image/2_player/red/red_damage3.bmp", 0, 0, 855, 462, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("red_die", "image/2_player/red/red_die.bmp", 0, 0, 333, 576, 1, 2, true, RGB(255, 0, 255), false);
	//플레이어(레드) 그림자 이미지
	IMAGEMANAGER->addImage("red_shadow", "image/2_Player/red/redShadow.bmp", 170, 60, true, RGB(255, 0, 255), false);
	
	//이건  Ryno이미지입니다 하나씩 풀꺼입니다.
	IMAGEMANAGER->addFrameImage("Ryno_idle", "image/2_Player/green/green_idle.bmp", 1020, 432, 5, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_move", "image/2_Player/green/green_move.bmp", 1101, 432, 6, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_attack", "image/2_Player/green/green_attack_normal.bmp", 2163, 432, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_attack_front", "image/2_Player/green/green_attack_frontCombo.bmp", 2352, 576, 8, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_jumpAttack", "image/2_Player/green/green_jumpAttack.bmp", 1680, 432, 7, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_dash", "image/2_Player/green/green_dash.bmp", 768, 360, 4, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_dashAttack_alt", "image/2_Player/green/green_dashAttack_alt.bmp", 549, 432, 3, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_dashAttack_ctrl", "image/2_Player/green/green_dashAttack_ctrl.bmp", 219, 330, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_crawl", "image/2_Player/green/green_crawl.bmp", 1008, 294, 4, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_catch", "image/2_Player/green/green_catch.bmp", 2784, 576, 8, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_catch_frontCombo", "image/2_Player/green/green_catch_frontCombo.bmp", 1410, 438, 5, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_fly", "image/2_Player/green/green_fly.bmp", 1332, 378, 4, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_damage", "image/2_Player/green/green_damage.bmp", 192, 420, 1, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_death", "image/2_Player/green/green_death.bmp", 888, 444, 4, 2, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("Ryno_death2", "image/2_Player/green/green_death2.bmp", 216, 396, 1, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_give_up", "image/2_Player/green/green_giveUp.bmp", 234, 564, 1, 2, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addFrameImage("Ryno_start", "image/2_Player/green/green_start.bmp", 138 ,216, 1 , 1, true, RGB(255, 0, 255),false);
	IMAGEMANAGER->addImage("green_shadow", "image/2_Player/green/shadow.bmp", 100, 35, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("effect" , "image/2_Player/green/effect.bmp", 150, 150, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("effect1", "image/2_Player/green/effect.bmp", 150, 150, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("effect2", "image/2_Player/green/effect.bmp", 150, 150, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("effect3", "image/2_Player/green/effect.bmp", 150, 150, true, RGB(255, 0, 255), false);
}

void player::collision()
{
	//whiteBaseball 충돌
	for (int i = 0; i <_em->getVWb().size(); i++)
	{
		RECT temp;
	
		//플레이어가 whiteBaseball한테 맞을때 충돌함수
		if (_em->getVWb()[i]->isattack)
		{
			if (_shadow->getCenterY() >= _em->getVWb()[i]->_wbShadow.rc.top&&
				_shadow->getCenterY() <= _em->getVWb()[i]->_wbShadow.rc.bottom)
			{
				if (IntersectRect(&temp, &_playerrc, &_em->getVWb()[i]->getRect()))
				{
					isdamage = true;
				}
			}
		}
	
		//whiteBaseball와 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVWb()[i]->_wbShadow.rc.top&&
				_shadow->getCenterY() <= _em->getVWb()[i]->_wbShadow.rc.bottom)
			{
				if (IntersectRect(&temp, &_playerrc, &_em->getVWb()[i]->getRect()))
				{
					iscatch = true;
				}
			}
		}
	}
	
	//blueBaseball 충돌
	for (int i = 0; i < _em->getVBb().size(); i++)
	{
		RECT temp;
	
		//플레이어가 blueBaseball한테 맞을때 충돌함수
		if (_em->getVBb()[i]->isattack)
		{
			if (_shadow->getCenterY() >= _em->getVBb()[i]->_bbShadow.rc.top&&
				_shadow->getCenterY() <= _em->getVBb()[i]->_bbShadow.rc.bottom)
			{
				if (IntersectRect(&temp, &_playerrc, &_em->getVBb()[i]->getRect()))
				{
					isdamage = true;
				}
			}
		}
	
		//blueBaseball과 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVBb()[i]->_bbShadow.rc.top&&
				_shadow->getCenterY() <= _em->getVBb()[i]->_bbShadow.rc.bottom)
			{
				if (IntersectRect(&temp, &_playerrc, &_em->getVBb()[i]->getRect()))
				{
					iscatch = true;
				}
			}
		}
	}
	
	//===========================================
	//여기부터 작업했음....
	// =========================================
	
	//yellowBaseball 충돌
	for (int i = 0; i < _em->getVBb().size(); i++)
	{
		RECT temp;
	
		//플레이어가 yellowBaseball한테 맞을때 충돌함수
		if (_em->getVYb()[i]->isattack)
		{
			if (_shadow->getCenterY() >= _em->getVYb()[i]->_ybShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVYb()[i]->_ybShadow.rc.bottom)
			{
				RECT t1 = _playerrc;
				RECT t2 = _em->getVYb()[i]->getRect();
				if (IntersectRect(&temp, &t1, &t2))
				{
					isdamage = true;
				}
			}
		}
	
		//yellowBaseball과 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVYb()[i]->_ybShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVYb()[i]->_ybShadow.rc.bottom)
			{
				RECT t3 = _playerrc;
				RECT t4 = _em->getVYb()[i]->getRect();
				if (IntersectRect(&temp, &t3, &t4))
				{
					iscatch = true;
				}
			}
		}
	}
	
	//greenBaseball 충돌
	for (int i = 0; i < _em->getVGb().size(); i++)
	{
		RECT temp;
	
		//플레이어가 greenBaseball한테 맞을때 충돌함수
		if (_em->getVGb()[i]->isattack)
		{
			if (_shadow->getCenterY() >= _em->getVGb()[i]->_gbShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVGb()[i]->_gbShadow.rc.bottom)
			{
				RECT t1 = _playerrc;
				RECT t2 = _em->getVGb()[i]->getRect();
				if (IntersectRect(&temp, &t1, &t2))
				{
					isdamage = true;
				}
			}
		}
	
		//greenBaseball과 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVGb()[i]->_gbShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVGb()[i]->_gbShadow.rc.bottom)
			{
				RECT t3 = _playerrc;
				RECT t4 = _em->getVGb()[i]->getRect();
				if (IntersectRect(&temp, &t3, &t4))
				{
					iscatch = true;
				}
			}
		}
	}
	
	//batMan 충돌
	for (int i = 0; i < _em->getVBat().size(); i++)
	{
		RECT temp;
	
		//플레이어가 batMan한테 맞을때 충돌함수
		if (_em->getVBat()[i]->isAttack)
		{
			if (_shadow->getCenterY() >= _em->getVBat()[i]->_batShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVBat()[i]->_batShadow.rc.bottom)
			{
				RECT t1 = _playerrc;
				RECT t2 = _em->getVBat()[i]->getRect();
				if (IntersectRect(&temp, &t1, &t2))
				{
					isdamage = true;
				}
			}
		}
	
		//batMan과 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVBat()[i]->_batShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVBat()[i]->_batShadow.rc.bottom)
			{
				RECT t3 = _playerrc;
				RECT t4 = _em->getVBat()[i]->getRect();
				if (IntersectRect(&temp, &t3, &t4))
				{
					iscatch = true;
				}
			}
		}
	}
	
	//card 충돌
	for (int i = 0; i < _em->getVCard().size(); i++)
	{
		RECT temp;
	
		//플레이어가 card한테 맞을때 충돌함수
		if (_em->getVCard()[i]->isattack)
		{
			if (_shadow->getCenterY() >= _em->getVCard()[i]->_cardShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVCard()[i]->_cardShadow.rc.bottom)
			{
				RECT t1 = _playerrc;
				RECT t2 = _em->getVCard()[i]->getAtkCardRc();
				if (IntersectRect(&temp, &t1, &t2))
				{
					isdamage = true;
				}
			}
		}
	
		//card과 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVCard()[i]->_cardShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVCard()[i]->_cardShadow.rc.bottom)
			{
				RECT t3 = _playerrc;
				RECT t4 = _em->getVCard()[i]->getAtkCardRc();
				if (IntersectRect(&temp, &t3, &t4))
				{
					iscatch = true;
				}
			}
		}
	}
	
	//glove 충돌
	for (int i = 0; i < _em->getVGlove().size(); i++)
	{
		RECT temp;
	
		//플레이어가 glove한테 맞을때 충돌함수
		if (_em->getVGlove()[i]->isattack)
		{
			if (_shadow->getCenterY() >= _em->getVGlove()[i]->_gloveShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVGlove()[i]->_gloveShadow.rc.bottom)
			{
				RECT t1 = _playerrc;
				RECT t2 = _em->getVGlove()[i]->getAttackRect();
				if (IntersectRect(&temp, &t1, &t2))
				{
					isdamage = true;
				}
			}
		}
	
		//glove과 잡기상태 충돌처리함수
		if (iscrawl && !isattack)
		{
			if (_shadow->getCenterY() >= _em->getVGlove()[i]->_gloveShadow.rc.top &&
				_shadow->getCenterY() <= _em->getVGlove()[i]->_gloveShadow.rc.bottom)
			{
				RECT t3 = _playerrc;
				RECT t4 = _em->getVGlove()[i]->getAttackRect();
				if (IntersectRect(&temp, &t3, &t4))
				{
					iscatch = true;
				}
			}
		}
	}
}
