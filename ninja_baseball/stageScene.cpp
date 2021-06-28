#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	IMAGEMANAGER->addImage("stage", "image/1_Map/Stage1.bmp", 4320, 2304, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - 768);

	//_Ryno = new player;
	//_Ryno->init(2);

	_red = new player;
	_red->init(1);

	_em = new enemyManager;
	_em->init();

	/*_em->setPlayerMemoryAddressLink(_Ryno);*/
	_em->setPlayerMemoryAddressLink(_red);

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	/*_Ryno->update();*/
	_red->update();
	_em->update();
	/*CAMERAMANAGER->updateCamera(_Ryno->getX(), _Ryno->getY());*/
	CAMERAMANAGER->updateCamera(_red->getX(), _red->getY());

}

void stageScene::render()
{
	IMAGEMANAGER->findImage("stage")->render(getMemDC(), 0, 0);
	_em->render();
	/*_Ryno->render();*/
	_red->render();
}
