#include "stdafx.h"
#include "stageScene.h"
HRESULT stageScene::init()
{
	IMAGEMANAGER->addImage("stage", "image/1_Map/Stage1.bmp", 4320, 2304, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - 768);

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
}
