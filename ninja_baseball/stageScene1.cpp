#include "stdafx.h"
#include "stageScene1.h"

HRESULT stageScene1::init()
{
	setImage();

	CAMERAMANAGER->setCamera(0, 0);
	vText = TXTDATA->txtLoad("playerData.txt");

	_playerSelect = atoi(vText[0].c_str());

	_player = new player;
	_player->init(_playerSelect, true);

	_em = new enemyManager;

	_obj = new objectManager;
	_obj->init();

	_obj->setLinkPlayer(_player);
	_obj->setLinkEnemyManager(_em);

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);

	_playerUI = new playerUI;
	_playerUI->init(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, _playerSelect, _player->gethp(), _player->gethp(), _player->getlife());

	_timerUI = new timerUI;
	_timerUI->init(99, 2, CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

	//SET baseBall
	//_em->setBlueBaseball();
	//_em->setGreenBaseball();
	//_em->setWhiteBaseball();
	//_em->setYellowBaseball();
	//////////////////////////

	//SET bat
	//_em->setBat1();		//stage1에 등장하는 배트 2마리
	/////////////////////////

	//SET glove
	//_em->setGlove();
	////////////////////////

	setShutter();

	queue<float> empty;
	swap(_cameraStopX, empty);

	queue<float> empty2;
	swap(_setEnemy, empty2);

	_cameraStopX.push(1300);
	_cameraStopX.push(2300);
	_cameraStopX.push(BACKGROUNDX);

	_setEnemy.push(1150);
	_setEnemy.push(2250);
	_setEnemy.push(2450);
	_setEnemy.push(BACKGROUNDX - 100);

	_gameoverUI = new gameOverUI;
	_gameoverUI->init();

	_count = 0;

	_setBaseBallandGlove = false;

	_isWhiteBaseBallSet = false;

	_isAllEnemySet = false;
	SOUNDMANAGER->stop("캐릭터선택");
	SOUNDMANAGER->play("스테이지1", 0.2f);

	_isGameOverSound = false;
	_isContinueSound = false;
	_soundCount = 0;
	return S_OK;
}

void stageScene1::release()
{
	_player->release();
	_em->release();
	_obj->release();

	//애들 죽으면 release해줘야 stage3에서도 안나올거야
	RENDERMANAGER->deleteAll();
}

void stageScene1::update()
{
	if (!_gameoverUI->getIsGameOver())
	{
		RENDERMANAGER->update();

		if (!_shutter.isCrush)
		{
			shutterCollison();
		}
		_player->update();
		
		_obj->update();

		updateShutter();

		CAMERAMANAGER->updateCamera(_player->getX(), _player->getY(), 0.51f);
		CAMERAMANAGER->update();

		//===============================에너미 세팅===============================================
		if (!_setEnemy.empty() && _setEnemy.front() <= CAMERAMANAGER->getCameraRIGHT())
		{
			if (_setEnemy.front() == 1150)
			{
				_em->setBlueBaseball();
				_em->setYellowBaseball();

			}
			else if (_setEnemy.front() == 2250)
			{
				_em->setWhiteBaseball();
				_isWhiteBaseBallSet = true;
			}
			else if (_setEnemy.front() == 2450)
			{
				_em->setCard();
			}
			else if (_setEnemy.front() == BACKGROUNDX - 100)
			{
				_count = 0;
				_setBaseBallandGlove = true;
			}
			_setEnemy.pop();
		}
		

		if (_setBaseBallandGlove)
		{
			_count++;
			if (_count != 0)
			{
				if (_count <= 350 && _count % 350 == 0)
				{
					_em->setGlove();
				}
				else if (_count % 700 == 0)
				{
					_em->setGreenBaseball();
				}
				if (_count > 700)
				{
					_setBaseBallandGlove = false;
					_isAllEnemySet = true;
					_count = 0;
				}
			}
		}
		//=======================================================================================

		//==================에너미 업데이트 ================================

	
		//UPDATE baseBall////////////
		_em->update();
	
		_em->updateBlueBaseball();
		_em->updateGreenBaseball();
		_em->updateWhiteBaseball();
		_em->updateYellowBaseball();
		
		_em->baseballCollision();
		/////////////////////////////

		//UPDATE BAT
		_em->updateBat();
		_em->batCollision();
		////////////////////////////

		//UPDATE GLOVE
		_em->updateGlove();
		_em->gloveCollision();
		////////////////////////////

		//UPDATE CARD
		_em->updateCard();
		
		//ryno, red 위치 찾아주기 (baseball, bat, glove 다 들어있어요)
		_em->playerLocation();

		_em->wallLocation();

		//===============================================================

		//카메라
		if (!_cameraStopX.empty() && _cameraStopX.front() <= CAMERAMANAGER->getCameraRIGHT())
		{
			_cameraStopX.pop();	//이전 카메라 지워줌
			CAMERAMANAGER->_isFixed = true;
		}

		if (_em->isAllDead())
		{
			if (CAMERAMANAGER->_isFixed)
			{
				CAMERAMANAGER->_isFixed = false;
			}
			if (_isAllEnemySet)
			{
				_count++;
				if (_count >= 100)
				{
					//텍스트 데이터로 현재 정보 넘기기 위해 기존에 벡터에 저장했던거 삭제
					vText.clear();

					//플레이어 선택, 플레이어 목숨, 플레이어 hp, 플레이어 x좌표, 플레이어 y좌표, 플레이어가 오른쪽을 보고있는지 bool값, 타이머 시간 순으로 텍스트에 저장
					char temp[128];
					_itoa_s(_playerSelect, temp, 10);
					vText.push_back(temp);
					_itoa_s(_player->getlife(), temp, 10);
					vText.push_back(temp);
					_itoa_s(_player->gethp(), temp, 10);
					vText.push_back(temp);
					_itoa_s(_player->getX(), temp, 10);
					vText.push_back(temp);
					_itoa_s(_player->getY(), temp, 10);
					vText.push_back(temp);
					_itoa_s((bool)(_player->isRight), temp, 10);
					vText.push_back(temp);
					_itoa_s(_timerUI->getTime(), temp, 10);
					vText.push_back(temp);

					TXTDATA->txtSave("playerData.txt", vText);

					SCENEMANAGER->changeScene("stage2");
				}
			}
		}
		//=============================================

		_playerUI->update(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, _player->gethp(), _player->getlife());

		_timerUI->update(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

		if (_timerUI->getTime() == 0)
		{
			_gameoverUI->setIsGameOver(true);
		}

		_gameoverUI->update();

		if (_player->getlife() <= 0 && _player->gethp() <= 0)
		{
			if (_player->isEnd)
			{
				_gameoverUI->setIsGameOver(true);
				SOUNDMANAGER->pause("스테이지1");
				if (!_isGameOverSound)
				{
					_isGameOverSound = true;
					SOUNDMANAGER->play("gameOver", 0.7f);
				}
			}
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown())
		{
			_gameoverUI->setIsGameOver(false);
			_gameoverUI->setTimer(9);
			_timerUI->setTime(99);
			_player->setlife(3);
			_player->sethp(5);
			_player->isEnd = false;
			_soundCount = 0;
			_isGameOverSound = false;
			_isContinueSound = false;
			SOUNDMANAGER->resume("스테이지1");
			SOUNDMANAGER->stop("continue");
			//_player->update();
		}

		_soundCount++;

		if (_soundCount >= 100)
		{
			SOUNDMANAGER->stop("gameOver");
			_gameoverUI->update();
			if (!_isContinueSound)
			{
				_isContinueSound = true;
				SOUNDMANAGER->play("continue", 0.7f);
			}
		}
	}

}

void stageScene1::render()
{
	IMAGEMANAGER->findImage("stage_1")->render(getMemDC(), 0, 0);

	EFFECTMANAGER->render();

	_obj->render();

	//RENDER baseBall
	_em->renderBlueBaseball();
	_em->renderGreenBaseball();
	_em->renderWhiteBaseball();
	_em->renderYellowBaseball();
	///////////////////////////////

	//RENDER BAT
	_em->renderBat();
	///////////////////////////////

	//RENDER GLOVE
	_em->renderGlove();
	///////////////////////////////


	_em->renderCard();

	if (!_shutter.isCrush)
	{
		IMAGEMANAGER->findImage("셔터")->render(getMemDC(), _shutter.x, _shutter.y);
		//Rectangle(getMemDC(), _shutter.rc);
	}
	else if (IMAGEMANAGER->findImage("shutterParticle1")->getY() + IMAGEMANAGER->findImage("shutterParticle1")->getHeight() < WINSIZEY)
	{
		IMAGEMANAGER->findImage("shutterParticle1")->render(getMemDC());
		IMAGEMANAGER->findImage("shutterParticle2")->render(getMemDC());
		IMAGEMANAGER->findImage("shutterParticle3")->render(getMemDC());
		IMAGEMANAGER->findImage("shutterParticle4")->render(getMemDC());
		IMAGEMANAGER->findImage("shutterParticle5")->render(getMemDC());
		IMAGEMANAGER->findImage("shutterParticle6")->render(getMemDC());
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("shutter_pixel")->render(getMemDC());
	}


	RENDERMANAGER->render(getMemDC());
	IMAGEMANAGER->findImage("기둥")->render(getMemDC(), BACKGROUNDX - 1032, 0);
	_player->render();

	_playerUI->render();
	_timerUI->render();

	


	//EFFECTMANAGER->render();

	if (_gameoverUI->getIsGameOver())
	{
		_gameoverUI->render();
	}
}

void stageScene1::shutterCollison()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) return;

	float right = BACKGROUNDX;
	float top = 0;
	float bottom = WINSIZEY;

	float probeRight = _player->getShadowX() + _player->_shadow->getWidth() / 2;

	for (int i = _player->_shadow->getX(); i < probeRight + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("shutter_pixel")->getMemDC(), i, _player->getShadowY() - _player->_shadow->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			//_player->setShadowX(i - _player->_shadow->getWidth() / 2);
			//_player->setX(_player->getShadowX());
			//break;
			if (right > i)
			{
				right = i;
			}

		}
	}

	if (right <= _player->getShadowX() + _player->_shadow->getWidth() / 2)
	{
		_player->setShadowX(_player->getShadowX() - (_player->getShadowX() + _player->_shadow->getWidth() / 2 - right) + 6);
		_player->setX(_player->getShadowX());
	}

	if (!_em->getVWb().empty())
	{
		for (int i = 0; i < _em->getVWb().size(); i++)
		{
			right = BACKGROUNDX;
			if (_em->getVWb()[i]->isRollState) continue;
			float enemyProbeRight = _em->getVWb()[i]->getShadowX() + (_em->getVWb()[i]->getShadowRect().right - _em->getVWb()[i]->getShadowRect().left) / 2;
			for (int j = _em->getVWb()[i]->getShadowX() - (_em->getVWb()[i]->getShadowRect().right - _em->getVWb()[i]->getShadowRect().left) / 2; 
				j < enemyProbeRight + 50; ++j)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("shutter_pixel")->getMemDC(), j,
					_em->getVWb()[i]->getShadowY() - (_em->getVWb()[i]->getShadowRect().bottom - _em->getVWb()[i]->getShadowRect().top) / 2);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if ((r == 0 && g == 0 && b == 255))
				{
					if (right > j)
					{
						right = j;
					}

				}
			}

			if (right <= _em->getVWb()[i]->getShadowX() + (_em->getVWb()[i]->getShadowRect().right - _em->getVWb()[i]->getShadowRect().left) / 2)
			{
				_em->getVWb()[i]->setShadowX(_em->getVWb()[i]->getShadowX() - (_em->getVWb()[i]->getShadowX() + (_em->getVWb()[i]->getShadowRect().right - _em->getVWb()[i]->getShadowRect().left) / 2 - right) + 6);
				_em->getVWb()[i]->setX(_em->getVWb()[i]->getShadowX() - 200);
			}
		}
	}
}

void stageScene1::setImage()
{
	IMAGEMANAGER->addImage("stage_1", "image/1_Map/stage1-1.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("기둥", "image/1_Map/stage1-1기둥.bmp", 72, 768, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("셔터", "image/9_Object/shutter.bmp", 327, 768, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutter_pixel", "image/9_Object/shutter_pixel.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutterParticle1", "image/9_Object/shutter_particle1.bmp", 236, 215, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutterParticle2", "image/9_Object/shutter_particle2.bmp", 188, 263, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutterParticle3", "image/9_Object/shutter_particle3.bmp", 206, 301, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutterParticle4", "image/9_Object/shutter_particle4.bmp", 143, 278, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutterParticle5", "image/9_Object/shutter_particle5.bmp", 227, 240, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutterParticle6", "image/9_Object/shutter_particle6.bmp", 191, 260, true, RGB(255, 0, 255), false);
}

void stageScene1::setShutter()
{
	_shutter.x = 2001;
	_shutter.y = -IMAGEMANAGER->findImage("셔터")->getHeight() / 2 + 100;
	_shutter.body = RectMake(_shutter.x, _shutter.y, IMAGEMANAGER->findImage("셔터")->getWidth(), IMAGEMANAGER->findImage("셔터")->getHeight());
	_shutter.rc = RectMake(2001, 200, IMAGEMANAGER->findImage("셔터")->getWidth(), 500);
	_down = 100.f;
	_gravity = 10.f;
	IMAGEMANAGER->findImage("shutterParticle1")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle2")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle3")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle4")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle5")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle6")->setCenter(2001 + 30, WINSIZEY / 2);
	_shutter.isCrush = false;
	_shutter.isClosed = false;
	_shutter.height = 30;
}

void stageScene1::updateShutter()
{
	RECT temp;
	if (_player->isattack)
	{
		if (IntersectRect(&temp, &_player->_attack_rc, &_shutter.rc))
		{
			_shutter.isCrush = true;
		}
	}
	if (_shutter.isCrush)
	{
		IMAGEMANAGER->findImage("shutterParticle1")->setCenter(IMAGEMANAGER->findImage("shutterParticle1")->getCenterX() + 5, IMAGEMANAGER->findImage("shutterParticle1")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle2")->setCenter(IMAGEMANAGER->findImage("shutterParticle2")->getCenterX() + 10, IMAGEMANAGER->findImage("shutterParticle2")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle3")->setCenter(IMAGEMANAGER->findImage("shutterParticle3")->getCenterX() + 15, IMAGEMANAGER->findImage("shutterParticle3")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle4")->setCenter(IMAGEMANAGER->findImage("shutterParticle4")->getCenterX() - 5, IMAGEMANAGER->findImage("shutterParticle4")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle5")->setCenter(IMAGEMANAGER->findImage("shutterParticle5")->getCenterX() - 7, IMAGEMANAGER->findImage("shutterParticle5")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle6")->setCenter(IMAGEMANAGER->findImage("shutterParticle6")->getCenterX() - 13, IMAGEMANAGER->findImage("shutterParticle6")->getCenterY() - _down);
		_down -= _gravity;
	}

	if(_isWhiteBaseBallSet)
	{
		_count++;
		if (_count >= 50)
		{
			if (_shutter.body.bottom >= WINSIZEY)
			{
				if (!_shutter.isClosed)
				{
					_shutter.body.bottom = WINSIZEY - _shutter.height;
					_shutter.height -= 5;
					if (_shutter.height <= 0)
					{
						_shutter.isClosed = true;
						_isWhiteBaseBallSet = false;
						_count = 0;
					}
				}
				else
				{
					_shutter.body.bottom = WINSIZEY;
				}
				_shutter.y = _shutter.body.bottom - IMAGEMANAGER->findImage("셔터")->getHeight();
			}
			else
			{
				_shutter.y += 10;
			}
		}
		_shutter.body = RectMake(_shutter.x, _shutter.y, IMAGEMANAGER->findImage("셔터")->getWidth(), IMAGEMANAGER->findImage("셔터")->getHeight());
	}
}
