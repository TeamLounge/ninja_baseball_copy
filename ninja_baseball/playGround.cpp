#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	//플레이어(레드) 프레임 이미지
	IMAGEMANAGER->addFrameImage("red_idle", "image/2_player/red/red_idle.bmp", 0, 0, 240, 462, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_walk", "image/2_player/red/red_walk.bmp", 0, 0, 1440, 522, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_jump", "image/2_player/red/red_jump.bmp", 0, 0, 231, 498, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_attack", "image/2_player/red/red_attack.bmp", 0, 0, 7344, 630, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_run", "image/2_player/red/red_run.bmp", 0, 0, 768, 480, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("red_grip2", "image/2_player/red/red_grip2.bmp", 0, 0, 666, 444, 3, 2, true, RGB(255, 0, 255));
	//그림자 이미지
	IMAGEMANAGER->addImage("shadow", "image/2_player/green/shadow.bmp", 145, 30, true, RGB(255, 0, 255));

	//상속해서 다르게 하실수 있으니까
	//만약 상속을하셨다면 다르게 new할당을 해주시면 됩니다.
	// player = new (상속한 클래스);

	_red = new player;
	_red->init();
		
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();
	
}


void playGround::update()
{
	gameNode::update();
		
	_red->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	TIMEMANAGER->render(getMemDC());

	_red->render();
	
	//==================================================
	//여기도 건들지마라
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
