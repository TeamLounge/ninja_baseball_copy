#include "stdafx.h"
#include "stageScene3.h"

//ver 0702_22:27 주석 삭제
HRESULT stageScene3::init()
{
	IMAGEMANAGER->addImage("stage_3", "image/1_Map/stage1-3.bmp", 1920, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("빵빠레", "image/6_UI/inGame/빵빠레.bmp", 7125, 258, 19, 1, true, RGB(255, 0, 255), false);
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
	_em->setBat2();		//stage3에 등장하는 배트 3마리

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);

	_count = 0;

	_cameraStopX.push(1080);

	CAMERAMANAGER->_isFixed = true;

	_isSetBoss = false;

	_isStart = true;

	_bossHPBar = new progressBar;
	_bossHPBar->init(CAMERAMANAGER->getCameraCenterX() - 288, 150, "image/6_UI/inGame/boss_greenBar.bmp", "image/6_UI/inGame/boss_yellowBar.bmp", 576, 24);
	_bossHPBar2 = new progressBar;
	_bossHPBar2->init(CAMERAMANAGER->getCameraCenterX() - 288, 150, "image/6_UI/inGame/boss_yellowBar.bmp", "image/4_Boss/boss_redBar.bmp", 576, 24);

	_gameoverUI = new gameOverUI;
	_gameoverUI->init();

	return S_OK;
}

void stageScene3::release()
{
	_player->release();
	_em->release();
	RENDERMANAGER->deleteAll();
}

void stageScene3::update()
{
	if (!_gameoverUI->getIsGameOver())
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

	_em->updateBat();
	//ryno, red 위치 찾아주기 (baseball, bat, glove 다 들어있어요)
	_em->playerLocation();
	

	_player->update();

	_em->update();
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
				if (IMAGEMANAGER->findImage("빵빠레")->getFrameX() >= IMAGEMANAGER->findImage("빵빠레")->getMaxFrameX())
				{
					IMAGEMANAGER->findImage("빵빠레")->setFrameX(IMAGEMANAGER->findImage("빵빠레")->getMaxFrameX());
					_isSetBoss = true;
					_em->setBoss();
				}
				else
				{
					IMAGEMANAGER->findImage("빵빠레")->setFrameX(IMAGEMANAGER->findImage("빵빠레")->getFrameX() + 1);
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
			CAMERAMANAGER->updateCamera(_player->getX(), WINSIZEY / 2, _em->getBoss()->getCenterX(), WINSIZEY / 2, 0.07f, 0.93f);
		}
		else
		{
			CAMERAMANAGER->updateCamera(_player->getX(), WINSIZEY / 2, 0.51f);
		}

		//카메라 오른쪽 맵 밖으로 안나가게
		if (CAMERAMANAGER->getCameraRIGHT() >= IMAGEMANAGER->findImage("stage_3")->getWidth())
		{
			CAMERAMANAGER->setCamera(IMAGEMANAGER->findImage("stage_3")->getWidth() - WINSIZEX, 0);
		}

		RENDERMANAGER->update();

		_playerUI->update(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, _player->gethp(), _player->getlife());
		_timerUI->update(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

		//보스 죽으면
		if (_isSetBoss && _em->getBoss()->_isDeathState)
		{
			_count++;
			if (_count >= 500)
			{
				_count = 0;
				SCENEMANAGER->changeScene("ending");
			}
		}

		//보스 체력바
		if (_isSetBoss)
		{
			if (_em->getBoss()->_count < 10)
			{
				_bossHPBar->setX(CAMERAMANAGER->getCameraCenterX() - 288);
				_bossHPBar->setGauge(_em->getBoss()->getCurrentHP(), _em->getBoss()->getMaxHP());
				_bossHPBar->update();
			}
			else if (_em->getBoss()->_count <= 20)
			{
				_bossHPBar2->setX(CAMERAMANAGER->getCameraCenterX() - 288);
				_bossHPBar2->setGauge(_em->getBoss()->getCurrentHP(), _em->getBoss()->getMaxHP());
				_bossHPBar2->update();
			}
		}
	}
	else
	{
		//게임오버 상태면
		if (KEYMANAGER->isOnceKeyDown())
		{
			_gameoverUI->setIsGameOver(false);
			_gameoverUI->setTimer(9);
			_player->setlife(4);
			_player->sethp(5);
			_player->isEnd = false;
			//_player->update();
		}
		_gameoverUI->update();
	}

}

void stageScene3::render()
{
	IMAGEMANAGER->findImage("stage_3")->render(getMemDC(), 0, 0);
	if (_isHaveToSetBoss)
	{
		IMAGEMANAGER->findImage("빵빠레")->frameRender(getMemDC(), IMAGEMANAGER->findImage("stage_3")->getWidth() - 680, WINSIZEY - 350);
	}
	_player->render();

	if (_isSetBoss)
	{
		_em->pinRender();
	}
	_em->renderBat();
	RENDERMANAGER->render(getMemDC());
	if (_isSetBoss)
	{
		//_em->renderBoss();
	}
	EFFECTMANAGER->render();
	_em->render();

	_playerUI->render();
	_timerUI->render();
	
	//보스 체력바 출력
	if (_isSetBoss)
	{
		if (_em->getBoss()->_count < 10)
			_bossHPBar->render();
		else
			_bossHPBar2->render();

		IMAGEMANAGER->findImage("boss_name")->render(getMemDC(),
			CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("boss_name")->getWidth() / 2,
			120);
	}
}
