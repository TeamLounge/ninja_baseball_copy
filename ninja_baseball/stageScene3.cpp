#include "stdafx.h"
#include "stageScene3.h"

HRESULT stageScene3::init()
{
	IMAGEMANAGER->addImage("stage_3", "image/1_Map/stage1-3.bmp", 1920, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("»§ºü·¹", "image/6_UI/inGame/»§ºü·¹.bmp", 7125, 258, 19, 1, true, RGB(255, 0, 255), false);
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
	_timerUI->init(atoi(vText[6].c_str()), 5, CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

	_em = new enemyManager;
	_em->init();

	_em->setBoss();

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);

	return S_OK;
}

void stageScene3::release()
{
}

void stageScene3::update()
{
	_player->update();

	_em->update();

	_em->updateBoss();

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
	CAMERAMANAGER->updateCamera(_player->getX(), WINSIZEY/2, 0.51f);
	if (CAMERAMANAGER->getCameraRIGHT() >= IMAGEMANAGER->findImage("stage_3")->getWidth())
	{
		CAMERAMANAGER->setCamera(IMAGEMANAGER->findImage("stage_3")->getWidth() - WINSIZEX, 0);
	}

	RENDERMANAGER->update();

	_playerUI->init(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, atoi(vText[0].c_str()), 5, _player->gethp(), _player->getlife());
	_timerUI->update(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

	if (_em->getBoss()->_isDeathState)
	{
		SCENEMANAGER->changeScene("ending");
	}
}

void stageScene3::render()
{
	IMAGEMANAGER->findImage("stage_3")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("»§ºü·¹")->frameRender(getMemDC(), IMAGEMANAGER->findImage("stage_3")->getWidth() - 680, WINSIZEY - 350);
	_player->render();
	_em->render();
	RENDERMANAGER->render(getMemDC());

	_playerUI->render();
	_timerUI->render();
	
}
