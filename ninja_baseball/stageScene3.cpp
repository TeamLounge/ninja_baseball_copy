#include "stdafx.h"
#include "stageScene3.h"

HRESULT stageScene3::init()
{
	IMAGEMANAGER->addImage("stage_3", "image/1_Map/stage1-3.bmp", 1920, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("»§ºü·¹", "image/6_UI/inGame/»§ºü·¹.bmp", 7125, 258, 19, 1, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);

	vText = TXTDATA->txtLoad("playerData.txt");

	_player = new player;
	_player->init(atoi(vText[0].c_str()));

	_player->setX(WINSIZEX - (BACKGROUNDX-atoi(vText[3].c_str())));
	_player->setY(atoi(vText[4].c_str()));

	_elapsedTime = 0;
	return S_OK;
}

void stageScene3::release()
{
}

void stageScene3::update()
{
	_player->update();

	_elapsedTime += TIMEMANAGER->getElapsedTime();

	if (_elapsedTime >= 0.2f)
	{
		_elapsedTime -= 0.2f;
		if (IMAGEMANAGER->findImage("»§ºü·¹")->getFrameX() >= IMAGEMANAGER->findImage("»§ºü·¹")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("»§ºü·¹")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage("»§ºü·¹")->setFrameX(IMAGEMANAGER->findImage("»§ºü·¹")->getFrameX() + 1);
		}
	}

	//Ä«¸Ş¶ó ¹«ºù ¼öÁ¤ ÇÊ¿ä
	CAMERAMANAGER->updateCamera(_player->getX(), WINSIZEY/2);
	if (CAMERAMANAGER->getCameraRIGHT() >= IMAGEMANAGER->findImage("stage_3")->getWidth())
	{
		CAMERAMANAGER->setCamera(IMAGEMANAGER->findImage("stage_3")->getWidth() - WINSIZEX, 0);
	}

	RENDERMANAGER->update();
}

void stageScene3::render()
{
	IMAGEMANAGER->findImage("stage_3")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("»§ºü·¹")->frameRender(getMemDC(), IMAGEMANAGER->findImage("stage_3")->getWidth() - 680, WINSIZEY - 350);
	_player->render();

	RENDERMANAGER->render(getMemDC());
	
}
