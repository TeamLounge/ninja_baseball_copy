#include "stdafx.h"
#include "stageScene2.h"

HRESULT stageScene2::init()
{
	IMAGEMANAGER->addImage("stage_2", "image/1_Map/stage1-2.bmp", WINSIZEX, BACKGROUNDY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - WINSIZEY);
	return S_OK;
}

void stageScene2::release()
{
}

void stageScene2::update()
{
	
}

void stageScene2::render()
{
	IMAGEMANAGER->findImage("stage_2")->render(getMemDC(), 0, 0);
}
