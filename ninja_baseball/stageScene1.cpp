#include "stdafx.h"
#include "stageScene1.h"

HRESULT stageScene1::init()
{
	IMAGEMANAGER->addImage("stage_1", "image/1_Map/stage1-1.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("기둥", "image/1_Map/stage1-1기둥.bmp",  72, 768, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("셔터", "image/9_Object/shutter.bmp", 327, 768, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("shutter_pixel", "image/9_Object/shutter_pixel.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);
	vText = TXTDATA->txtLoad("playerData.txt");

	_playerSelect = atoi(vText[0].c_str());

	_player = new player;
	_player->init(_playerSelect, true);

	_em = new enemyManager;
	_em->init();

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
	shutterCollison();
	_player->update();
	shutterCollison();
	_em->update();
	_obj->update();

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

	_player->render();
	_obj->render();
	_em->render();

	IMAGEMANAGER->findImage("셔터")->render(getMemDC(), 2001, 0);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("shutter_pixel")->render(getMemDC());
	}


	RENDERMANAGER->render(getMemDC());
	_playerUI->render();
	_timerUI->render();
	IMAGEMANAGER->findImage("기둥")->render(getMemDC(), BACKGROUNDX - 1032, 0);


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
			/**/
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
