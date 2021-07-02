#include "stdafx.h"
#include "stageScene3.h"

HRESULT stageScene3::init()
{
	IMAGEMANAGER->addImage("stage_3", "image/1_Map/stage1-3.bmp", 1920, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("������", "image/6_UI/inGame/������.bmp", 7125, 258, 19, 1, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);

	vText = TXTDATA->txtLoad("playerData.txt");

	_player = new player;
	_player->init(atoi(vText[0].c_str()), false);

	_player->setX(WINSIZEX - (BACKGROUNDX-atoi(vText[3].c_str())));
	_player->setY(atoi(vText[4].c_str()));

	_player->sethp(atoi(vText[2].c_str()));
	_player->setlife(atoi(vText[1].c_str()));

	_player->isRight = (bool)atoi(vText[5].c_str());
	
	_elapsedTime = 0;

	_playerUI = new playerUI;
	_playerUI->init(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10,
		atoi(vText[0].c_str()), 5, _player->gethp(), _player->getlife());

	_timerUI = new timerUI;
	_timerUI->init(atoi(vText[6].c_str()), 2, CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

	_em = new enemyManager;
	_em->init();
	_em->setBat2();
	//_em->setBoss();
	

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);

	_cameraStopX.push(1080);

	CAMERAMANAGER->_isFixed = true;

	_isSetBoss = false;

	_isStart = true;

	return S_OK;
}

void stageScene3::release()
{
}

void stageScene3::update()
{
	if (_isStart)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown(VK_UP) ||
			KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			CAMERAMANAGER->_isFixed = false;
			_isStart = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (CAMERAMANAGER->_isFixed)
		{
			CAMERAMANAGER->_isFixed = false;
		}
	}

	if (!_isHaveToSetBoss && CAMERAMANAGER->getCameraRIGHT() >= 1920)
	{
		_isHaveToSetBoss = true;
	}
	
	_player->update();

	_em->update();
	
	if (_isSetBoss)
	{
		_em->updateBoss();
	}
	
	if (_isHaveToSetBoss && !_isSetBoss)
	{
		_elapsedTime += TIMEMANAGER->getElapsedTime();

		if (_elapsedTime >= 0.2f)
		{
			_elapsedTime -= 0.2f;
			if (IMAGEMANAGER->findImage("������")->getFrameX() >= IMAGEMANAGER->findImage("������")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("������")->setFrameX(IMAGEMANAGER->findImage("������")->getMaxFrameX());
				_isSetBoss = true;
				_em->setBoss();
			}
			else
			{
				IMAGEMANAGER->findImage("������")->setFrameX(IMAGEMANAGER->findImage("������")->getFrameX() + 1);
			}
		}
	}

	if (!_cameraStopX.empty() && _cameraStopX.front() <= CAMERAMANAGER->getCameraRIGHT())
	{
		_cameraStopX.pop();
		CAMERAMANAGER->_isFixed = true;
	}

	if (_isSetBoss)
	{
		CAMERAMANAGER->updateCamera(_player->getX(), WINSIZEY/2, _em->getBoss()->getCenterX(), WINSIZEY/2, 0.1f, 0.9f);
	}
	else
	{
		//ī�޶� ���� ���� �ʿ�
		CAMERAMANAGER->updateCamera(_player->getX(), WINSIZEY / 2, 0.51f);
	}
	if (CAMERAMANAGER->getCameraRIGHT() >= IMAGEMANAGER->findImage("stage_3")->getWidth())
	{
		CAMERAMANAGER->setCamera(IMAGEMANAGER->findImage("stage_3")->getWidth() - WINSIZEX, 0);
	}

	RENDERMANAGER->update();

	_playerUI->update(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, _player->gethp(), _player->getlife());
	_timerUI->update(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

	if (_isSetBoss && _em->getBoss()->_isDeathState)
	{
		SCENEMANAGER->changeScene("ending");
	}

}

void stageScene3::render()
{
	IMAGEMANAGER->findImage("stage_3")->render(getMemDC(), 0, 0);
	if (_isHaveToSetBoss)
	{
		IMAGEMANAGER->findImage("������")->frameRender(getMemDC(), IMAGEMANAGER->findImage("stage_3")->getWidth() - 680, WINSIZEY - 350);
	}
	_player->render();
	_em->render();
	//em->renderBoss();
	RENDERMANAGER->render(getMemDC());
	_playerUI->render();
	_timerUI->render();
	

}
