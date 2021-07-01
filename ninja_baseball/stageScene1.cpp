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
	//_em->init();

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
	_em->setBlueBaseball();
	_em->setGreenBaseball();
	_em->setWhiteBaseball();
	_em->setYellowBaseball();
	//////////////////////////

	//SET bat
	_em->setBat1();
	/////////////////////////

	//SET glove
	_em->setGlove();
	////////////////////////
	_em->setCard();

	setShutter();

	return S_OK;
}

void stageScene1::release()
{
	_player->release();
	_obj->release();
}

void stageScene1::update()
{
	RENDERMANAGER->update();

	if (!_shutter.isCrush)
	{
		shutterCollison();
	}
	_player->update();
	_em->update();
	//_em->update();
	_obj->update();
	
	_em->updateCard();

	updateShutter();
	//UPDATE baseBall////////////
	//_em->updateBlueBaseball();
	//_em->updateGreenBaseball();
	//_em->updateWhiteBaseball();
	//_em->updateYellowBaseball();
	/////////////////////////////

	//_em->updateBat();

	//_em->updateGlove();
	

	CAMERAMANAGER->updateCamera(_player->getX(), _player->getY(), 0.51f);
	CAMERAMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('Q'))
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

	if (KEYMANAGER->isOnceKeyDown('S'))
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

	_playerUI->update(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, _player->gethp(), _player->getlife());

	_timerUI->update(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

}

void stageScene1::render()
{
	IMAGEMANAGER->findImage("stage_1")->render(getMemDC(), 0, 0);

	EFFECTMANAGER->render();

	_obj->render();
	//_em->render();

	////RENDER baseBall////////////
	//_em->renderBlueBaseball();
	//_em->renderGreenBaseball();
	//_em->renderWhiteBaseball();
	//_em->renderGreenBaseball();
	///////////////////////////////
	//
	//_em->renderBat();
	//
	//_em->renderGlove();
	_em->render();
	//_em->renderCard();

	if (!_shutter.isCrush)
	{
		IMAGEMANAGER->findImage("셔터")->render(getMemDC(), 2001, 0);
		Rectangle(getMemDC(), _shutter.rc);
	}
	else if (IMAGEMANAGER->findImage("shutterParticle1")->getY()+ IMAGEMANAGER->findImage("shutterParticle1")->getHeight() < WINSIZEY)
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
	_playerUI->render();
	_timerUI->render();
	_player->render();
	IMAGEMANAGER->findImage("기둥")->render(getMemDC(), BACKGROUNDX - 1032, 0);


	//EFFECTMANAGER->render();

}

void stageScene1::shutterCollison()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) return;

	float right = BACKGROUNDX;
	float top = 0;
	float bottom = WINSIZEY;

	float _probeRight = _player->getShadowX() + _player->_shadow->getWidth() / 2;

	for (int i = _probeRight - 20; i < _probeRight + 20; ++i)
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
	_shutter.rc = RectMake(2001, 200, IMAGEMANAGER->findImage("셔터")->getWidth(), 500);
	_down = 100.f;
	_gravity = 10.f;
	IMAGEMANAGER->findImage("shutterParticle1")->setCenter(2001+ 30, WINSIZEY/2);
	IMAGEMANAGER->findImage("shutterParticle2")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle3")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle4")->setCenter(2001 + 30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle5")->setCenter(2001 +30, WINSIZEY / 2);
	IMAGEMANAGER->findImage("shutterParticle6")->setCenter(2001 +30, WINSIZEY / 2);
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
		IMAGEMANAGER->findImage("shutterParticle1")->setCenter(IMAGEMANAGER->findImage("shutterParticle1")->getCenterX()+ 5 , IMAGEMANAGER->findImage("shutterParticle1")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle2")->setCenter(IMAGEMANAGER->findImage("shutterParticle2")->getCenterX() + 10, IMAGEMANAGER->findImage("shutterParticle2")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle3")->setCenter(IMAGEMANAGER->findImage("shutterParticle3")->getCenterX() + 15, IMAGEMANAGER->findImage("shutterParticle3")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle4")->setCenter(IMAGEMANAGER->findImage("shutterParticle4")->getCenterX() - 5, IMAGEMANAGER->findImage("shutterParticle4")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle5")->setCenter(IMAGEMANAGER->findImage("shutterParticle5")->getCenterX() - 7, IMAGEMANAGER->findImage("shutterParticle5")->getCenterY() - _down);
		IMAGEMANAGER->findImage("shutterParticle6")->setCenter(IMAGEMANAGER->findImage("shutterParticle6")->getCenterX() - 13, IMAGEMANAGER->findImage("shutterParticle6")->getCenterY() - _down);
		_down -= _gravity;
	}
}
