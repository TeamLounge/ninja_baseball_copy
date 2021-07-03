#include "stdafx.h"
#include "stageScene3.h"

HRESULT stageScene3::init()
{
	IMAGEMANAGER->addImage("stage_3", "image/1_Map/stage1-3.bmp", 1920, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("빵빠레", "image/6_UI/inGame/빵빠레.bmp", 7125, 258, 19, 1, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);

	vText = TXTDATA->txtLoad("playerData.txt");

	_player = new player;
	_player->init(atoi(vText[0].c_str()), false);

	//플레이어 위치 조정
	_player->setX(WINSIZEX - (BACKGROUNDX-atoi(vText[3].c_str())));
	_player->setY(atoi(vText[4].c_str()));

	//플레이어 체력 조정
	_player->sethp(atoi(vText[2].c_str()));
	
	//플레이어 목숨 조정
	_player->setlife(atoi(vText[1].c_str()));

	//플레이어가 보는 곳이 왼쪽인지 오른쪽인지 조정
	_player->isRight = (bool)atoi(vText[5].c_str());

	//플레이어 그림자 위치 조정
	if (atoi(vText[0].c_str())==1)
	{
		if (_player->isRight)
		{
			_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 30 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
			_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		}
		else
		{
			_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 30 + IMAGEMANAGER->findImage("red_shadow")->getWidth() / 2);
			_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("red_shadow")->getHeight() / 2);
		}
	}
	else if (atoi(vText[0].c_str()) == 2)
	{
		_player->setShadowY(_player->getY() + 90 + IMAGEMANAGER->findImage("green_shadow")->getHeight() / 2);
		if (_player->isRight)
		{
			_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) - 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
		}
		else
		{
			_player->setShadowX(_player->getX() - (_player->_shadow->getWidth() / 2) + 15 + IMAGEMANAGER->findImage("green_shadow")->getWidth() / 2);
		}
	}

	
	_elapsedTime = 0;

	_playerUI = new playerUI;
	_playerUI->init(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10,
		atoi(vText[0].c_str()), 5, _player->gethp(), _player->getlife());

	_timerUI = new timerUI;
	_timerUI->init(atoi(vText[6].c_str()), 2, CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

	_em = new enemyManager;
	_em->init();

	_obj = new objectManager;
	_obj->setgoldbat(0,0);

	//bat
	_em->setBat2();		//stage3에 등장하는 배트 3마리

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);
	_obj->setLinkEnemyManager(_em);
	_obj->setLinkPlayer(_player);

	_count = 0;

	queue<float> empty;
	swap(_cameraStopX, empty);
	_cameraStopX.push(1080);

	CAMERAMANAGER->_isFixed = true;

	_isSetBoss = false;
	_isHaveToSetBoss = false;
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

	
	//ryno, red 위치 찾아주기 (baseball, bat, glove 다 들어있어요)
	_player->update();
	_em->playerLocation();
	_em->updateBat();
	_em->batCollision();
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

		if (_isSetBoss)
		{
			_em->updateBoss();
			_obj->updategoldbat();
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
		if (_isSetBoss && _em->getBoss()->_isDeathState && _obj->getGoldbat()->ishold)
		{

			_count++;
			if (_count >= 350)
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
	if (_isSetBoss)
	{
		_em->pinRender();
		_obj->goldrender();
	}
	_em->renderBat();
	RENDERMANAGER->render(getMemDC());
	if (_isSetBoss)
	{
		_em->renderBoss();
	}
	EFFECTMANAGER->render();
	_em->render();
	_player->render();
	_playerUI->render();
	_timerUI->render();
	//보스 체력바 출력
	if (_isSetBoss && !_em->getBoss()->_isDeathState)
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
