#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{	
	IMAGEMANAGER->addImage("stage", "image/1_Map/Stage1.bmp", 4320, 2304, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - 768);

	_Ryno = new player;
	_Ryno->init(2, true);


	_red = new player;
	_red->init(1, true);

	_em = new enemyManager;
	_em->init();

	_em->setPlayerMemoryAddressLink(_Ryno);
	_Ryno->setEmMemoryAddressLink(_em);

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	RENDERMANAGER->update();
	_Ryno->update();
	//_red->update();
	_em->update();
	CAMERAMANAGER->updateCamera(_Ryno->getX(), WINSIZEY / 2);


	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (!CAMERAMANAGER->_isFixed)
		{
			CAMERAMANAGER->_isFixed = true;
		}
		else
		{
			CAMERAMANAGER->_isFixed = false;
		}
	}
}

void stageScene::render()
{
	IMAGEMANAGER->findImage("stage")->render(getMemDC(), 0, 0);
	RENDERMANAGER->render(getMemDC());
	_em->render();

	_Ryno->render();
//	_red->render();

}
