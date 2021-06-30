#include "stdafx.h"
#include "stageScene1.h"

HRESULT stageScene1::init()
{
	IMAGEMANAGER->addImage("stage_1", "image/1_Map/stage1-1.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);

	_Ryno = new player;
	_Ryno->init(2);

	//_red = new player;
	//_red->init(1);

	_em = new enemyManager;
	_em->init();

	_obj = new objectManager;
	_obj->init();

	_em->setPlayerMemoryAddressLink(_Ryno);
	_Ryno->setEmMemoryAddressLink(_em);
	_obj->setLinkPlayer(_Ryno);
	_obj->setLinkEnemyManager(_em);
	//_red->setEmMemoryAddressLink(_em);

	return S_OK;
}

void stageScene1::release()
{
	_Ryno->release();
	//_red->release();
}

void stageScene1::update()
{
	RENDERMANAGER->update();
	_Ryno->update();
	//_red->update();
	_em->update();
	_obj->update();
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
	//_red->render();
	_obj->render();
}
