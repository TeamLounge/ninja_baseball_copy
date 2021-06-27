#include "stdafx.h"
#include "stageScene.h"
HRESULT stageScene::init()
{
	IMAGEMANAGER->addImage("stage", "image/1_Map/Stage1.bmp", 4320, 2304, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - 768);

	//IMAGEMANAGER->addFrameImage("green_idle", "image/2_Player/green/green_idle.bmp", 1020, 432, 5, 2, true, RGB(255, 0, 255), false);
	//_rc = RectMakeCenter(200, BACKGROUNDY - 200 ,204, 216);
	_Ryno = new player;
	_Ryno->init(2);
	_em = new enemyManager;
	_em->init();

	_em->setRedMemoryAddressLink(_Ryno);

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	/*_count++;
	if (_count % 10 == 0)
	{
		if (IMAGEMANAGER->findImage("green_idle")->getFrameX() >= IMAGEMANAGER->findImage("green_idle")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("green_idle")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage("green_idle")->setFrameX(IMAGEMANAGER->findImage("green_idle")->getFrameX() + 1);
		}
	}
	*/
	_Ryno->update();
	_em->update();
	CAMERAMANAGER->updateCamera(_Ryno->getX(), _Ryno->getY());
}

void stageScene::render()
{
	IMAGEMANAGER->findImage("stage")->render(getMemDC(), 0, 0);
	//Rectangle(getMemDC(), _rc);
	_em->render();
	_Ryno->render();
	//IMAGEMANAGER->findImage("green_idle")->frameRender(getMemDC(), _rc.left, _rc.top, IMAGEMANAGER->findImage("green_idle")->getFrameX(), 0);
}
