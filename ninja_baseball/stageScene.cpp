#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	IMAGEMANAGER->addImage("stage", "image/1_Map/Stage1.bmp", 4320, 2304, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - 768);


	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
}

void stageScene::render()
{
	IMAGEMANAGER->findImage("stage")->render(getMemDC(), 0, 0);
}
