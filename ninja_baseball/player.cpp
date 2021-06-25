#include "stdafx.h"
#include "player.h"
#include "Ryno_idle.h"
HRESULT player::init()
{	
	//이건 하나씩 풀꺼입니다.
	IMAGEMANAGER->addFrameImage("Ryno_idle", "image/2_Player/green/green_idle.bmp", 1020, 432, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ryno_move", "image/2_Player/green/green_move.bmp", 1101, 432, 6, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_attack", "image/2_Player/green/green_attack_normal.bmp", 2163, 432, 7, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_attack_front", "image/2_Player/green/green_attack_frontCombo.bmp", 2352, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ryno_jumpAttack", "image/2_Player/green/green_jumpAttack.bmp", 1680, 432, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ryno_start", "image/2_Player/green/green_start.bmp", 138, 216, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_hold", "image/2_Player/green/green_hold.bmp", 495, 546, 3, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_dash", "image/2_Player/green/green_dash.bmp", 768, 360, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_dashAttack_alt", "image/2_Player/green/green_dashAttack_alt.bmp", 549, 432, 3, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_dashAttack_ctrl", "image/2_Player/green/green_dashAttack_ctrl.bmp", 219, 330, 1, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_crawl", "image/2_Player/green/green_crawl.bmp", 1008, 294, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_catch", "image/2_Player/green/green_catch.bmp", 2784, 576, 8, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_catch_frontCombo", "image/2_Player/green/green_dash.bmp", 1410, 438, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_fly", "image/2_Player/green/green_fly.bmp", 1332, 378, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_death", "image/2_Player/green/green_death.bmp", 888, 444, 4, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_death2", "image/2_Player/green/green_death2.bmp", 216, 396, 1, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Ryno_givp_up", "image/2_Player/green/green_givp_up.bmp", 234, 564, 5, 2, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Ryno_escape", "image/2_Player/green/green_escape.bmp", 189, 432, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadow", "image/2_Player/green/shadow.bmp", 100, 35, true, RGB(255, 0, 255));
	_shadow = IMAGEMANAGER->findImage("shadow");
	isRight = true;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	//idlestate만들면 _state =  new idlestate 해주세요 
	_state = new Ryno_idle;
	_state->enter(this);
	return S_OK;
}

void player::update()
{
	handleInput();
	_state->update(this);
}

void player::release()
{
}

void player::render()
{

	_shadow->render(getMemDC());
	_playerimg->frameRender(getMemDC(), _x - (_playerimg->getFrameWidth() / 2), _y - (_playerimg->getFrameHeight() / 2));

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
