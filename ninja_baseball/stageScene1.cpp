#include "stdafx.h"
#include "stageScene1.h"

HRESULT stageScene1::init()
{
	IMAGEMANAGER->addImage("stage_1", "image/1_Map/stage1-1.bmp", BACKGROUNDX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("���", "image/1_Map/stage1-1���.bmp",  72, 768, true, RGB(255, 0, 255), false);
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
	//_red->setEmMemoryAddressLink(_em);

	_em->setPlayerMemoryAddressLink(_player);
	_player->setEmMemoryAddressLink(_em);

	_playerUI = new playerUI;
	_playerUI->init(CAMERAMANAGER->getCameraLEFT() + 120, CAMERAMANAGER->getCameraTOP() + 10, _playerSelect, _player->gethp(), _player->gethp(), _player->getlife());

	_timerUI = new timerUI;
	_timerUI->init(99, 5, CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 36);

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

	_player->update();
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

	_player->render();
	_obj->render();
	_em->render();
	
	RENDERMANAGER->render(getMemDC());
	_playerUI->render();
	_timerUI->render();
	
	IMAGEMANAGER->findImage("���")->render(getMemDC(), BACKGROUNDX - 1032, 0);

	//EFFECTMANAGER->render();
	
}
