#include "stdafx.h"
#include "stageScene3.h"

HRESULT stageScene3::init()
{
	IMAGEMANAGER->addImage("stage_3", "image/1_Map/stage1-3.bmp", 1920, WINSIZEY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);

	_player = new player;
	_player->init(2);
	return S_OK;
}

void stageScene3::release()
{
}

void stageScene3::update()
{
	_player->update();
	CAMERAMANAGER->updateCamera(_player->getX(), _player->getY(), 0.51f);
}

void stageScene3::render()
{
	IMAGEMANAGER->findImage("stage_3")->render(getMemDC(), 0, 0);
	_player->render();
}
