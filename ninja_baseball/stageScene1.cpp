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
	_em->setBlueBaseball();
	_em->setGreenBaseball();
	_em->setWhiteBaseball();
	_em->setYellowBaseball();
	//////////////////////////

	//SET bat
	_em->setBat1();		//stage1�� �����ϴ� ��Ʈ 2����
	/////////////////////////

	//SET glove
	_em->setGlove();
	////////////////////////


	_em->setCard();

	return S_OK;
}

void stageScene1::release()
{
	_player->release();
	_obj->release();

	//�ֵ� ������ release����� stage3������ �ȳ��ðž�
}

void stageScene1::update()
{
	RENDERMANAGER->update();

	if (!_shutter.isCrush)
	{
		shutterCollison();
	}
	_player->update();
	_obj->update();
	
	_em->updateCard();


	//UPDATE BASEBALL
	//_em->updateBlueBaseball();
	//_em->updateGreenBaseball();
	//_em->updateWhiteBaseball();
	_em->updateYellowBaseball();
	_em->baseballCollision();
	/////////////////////////////


	//UPDATE BAT
	//_em->updateBat();
	//_em->batCollision();
	////////////////////////////


	//UPDATE GLOVE
	//_em->updateGlove();
	//_em->gloveCollision();
	////////////////////////////

	//ryno, red ��ġ ã���ֱ� (baseball, bat, glove �� ����־��)
	_em->playerLocation();
	

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
		//�ؽ�Ʈ �����ͷ� ���� ���� �ѱ�� ���� ������ ���Ϳ� �����ߴ��� ����
		vText.clear();

		//�÷��̾� ����, �÷��̾� ���, �÷��̾� hp, �÷��̾� x��ǥ, �÷��̾� y��ǥ, �÷��̾ �������� �����ִ��� bool��, Ÿ�̸� �ð� ������ �ؽ�Ʈ�� ����
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

	//RENDER baseBall
	_em->renderBlueBaseball();
	_em->renderGreenBaseball();
	_em->renderWhiteBaseball();
	_em->renderGreenBaseball();
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
		IMAGEMANAGER->findImage("����")->render(getMemDC(), 2001, 0);
	}


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("shutter_pixel")->render(getMemDC());
	}


	RENDERMANAGER->render(getMemDC());
	_playerUI->render();
	_timerUI->render();
	_player->render();
	IMAGEMANAGER->findImage("���")->render(getMemDC(), BACKGROUNDX - 1032, 0);


	//EFFECTMANAGER->render();

}

void stageScene1::shutterCollison()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_DOWN)) return;

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
	IMAGEMANAGER->addImage("���", "image/1_Map/stage1-1���.bmp", 72, 768, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("����", "image/9_Object/shutter.bmp", 327, 768, true, RGB(255, 0, 255), false);
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
	char str[128];
	for (int i = 1; i <= 6; i++)
	{
		sprintf_s(str, "shutterPiece%d", i);
		_shutter.sutterParticle.push_back(str);
	}
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
}
