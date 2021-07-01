#include "stdafx.h"
#include "playerUI.h"

HRESULT playerUI::init(float x, float y, int playerSelect, int maxHP, int currentHP, int life)
{
	IMAGEMANAGER->addImage("playerUIBackground", "image/6_UI/inGame/player.bmp", 213, 96, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_red_name", "image/6_UI/inGame/red_nameJOSE.bmp", 114, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_green_name", "image/6_UI/inGame/green_nameRYNO.bmp", 114, 24, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("ui_red_attacked", "image/6_UI/inGame/red_attack_frame.bmp", 126, 72, 2, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("ui_green_attacked", "image/6_UI/inGame/green_attack_frame.bmp", 126, 72, 2, 1, true, RGB(255, 0, 255), false);

	_x = x;
	_y = y;
	_playerSelect = playerSelect;
	_maxHP = maxHP;
	_currentHP = currentHP;
	_life = life;

	_rc = RectMake(_x, _y, IMAGEMANAGER->findImage("playerUIBackground")->getWidth(), 
		IMAGEMANAGER->findImage("playerUIBackground")->getHeight());
	_hpBar = new progressBar;
	
	_hpBar->init(_rc.left + 69, _rc.bottom - 24,
		"image/6_UI/inGame/hp_yellow.bmp", "image/6_UI/inGame/hp_red.bmp", 144, 24);

	return S_OK;
}

void playerUI::release()
{
}

void playerUI::update(float x, float y, int currentHP, int life)
{
	_x = x;
	_y = y;
	if (_currentHP > currentHP)
	{
		_isAttacked = true;
	}
	_currentHP = currentHP;
	_life = life;
	
	_rc = RectMake(_x, _y, IMAGEMANAGER->findImage("playerUIBackground")->getWidth(), 
		IMAGEMANAGER->findImage("playerUIBackground")->getHeight());

	_hpBar->setX(_rc.left + 69);
	_hpBar->setY(_rc.bottom - 24);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
	/*
	if (_isAttacked)
	{
		_elapsedSec += TIMEMANAGER->getElapsedTime();
		if (_elapsedSec >= 0.2f)
		{
			if (_playerSelect == 1)
			{
				if (IMAGEMANAGER->findImage("ui_red_attacked")->getFrameX() >= IMAGEMANAGER->findImage("ui_red_attacked")->getMaxFrameX())
				{
					_count++;
					IMAGEMANAGER->findImage("ui_red_attacked")->setFrameX(0);
				}
				else
				{
					IMAGEMANAGER->findImage("ui_red_attacked")->setFrameX(IMAGEMANAGER->findImage("ui_red_attacked")->getFrameX() + 1);
				}
			}
			else if (_playerSelect == 2)
			{
				if (IMAGEMANAGER->findImage("ui_green_attacked")->getFrameX() >= IMAGEMANAGER->findImage("ui_red_attacked")->getMaxFrameX())
				{
					_count++;
					IMAGEMANAGER->findImage("ui_green_attacked")->setFrameX(0);
				}
				else
				{
					IMAGEMANAGER->findImage("ui_green_attacked")->setFrameX(IMAGEMANAGER->findImage("ui_red_attacked")->getFrameX() + 1);
				}
			}
		}

		if (_count >= 3)
		{
			_isAttacked = false;
		}
	}
	*/
}

void playerUI::render()
{
	IMAGEMANAGER->findImage("playerUIBackground")->render(getMemDC(), _rc.left, _rc.top);

	if (_playerSelect == 1)
	{
		if (_isAttacked)
		{
			IMAGEMANAGER->findImage("ui_red_attacked")->frameRender(getMemDC(), _rc.left + 3, _rc.top + 24);
		}
		else
		{
			IMAGEMANAGER->findImage("ui_red")->render(getMemDC(), _rc.left + 3, _rc.top + 24);
		}
		
		IMAGEMANAGER->findImage("ui_red_name")->render(getMemDC(), _rc.left + 72, _rc.top);
	}
	else if(_playerSelect ==2)
	{
		if (_isAttacked)
		{
			IMAGEMANAGER->findImage("ui_green_attacked")->frameRender(getMemDC(), _rc.left + 3, _rc.top + 24);
		}
		else
		{
			IMAGEMANAGER->findImage("ui_green")->render(getMemDC(), _rc.left + 3, _rc.top + 24);
		}
		IMAGEMANAGER->findImage("ui_green_name")->render(getMemDC(), _rc.left + 72, _rc.top);
	}

	char str[128];
	sprintf_s(str, "yellow_%d", _life);
	IMAGEMANAGER->findImage(str)->render(getMemDC(), _rc.right - IMAGEMANAGER->findImage(str)->getWidth(), 
		_rc.bottom - 24 - IMAGEMANAGER->findImage(str)->getHeight());
	_hpBar->render();

	
}
