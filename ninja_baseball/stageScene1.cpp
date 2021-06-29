#include "stdafx.h"
#include "stageScene1.h"

HRESULT stageScene1::init()
{
	IMAGEMANAGER->addImage("stage_1", "image/1_Map/stage1-1.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);

	_Ryno = new player;
	_Ryno->init(2);

	_red = new player;
	_red->init(1);

	_em = new enemyManager;
	_em->init();

	_em->setPlayerMemoryAddressLink(_Ryno);
	return S_OK;
}

void stageScene1::release()
{
}

void stageScene1::update()
{
	RENDERMANAGER->update();
	_Ryno->update();
	_red->update();
	_em->update();
	CAMERAMANAGER->updateCamera(_Ryno->getX(), _Ryno->getY(), 0.51f);

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

void stageScene1::render()
{
	IMAGEMANAGER->findImage("stage_1")->render(getMemDC(), 0, 0);
	RENDERMANAGER->render(getMemDC());
	_em->render();
	_Ryno->render();
	_red->render();
}
