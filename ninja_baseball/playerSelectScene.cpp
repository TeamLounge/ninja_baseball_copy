#include "stdafx.h"
#include "playerSelectScene.h"

HRESULT playerSelectScene::init()
{
	//배경
	IMAGEMANAGER->addImage("playerSelectBackground", "image/6_UI/playerSelect/background_playerSelect.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	
	//캐릭터
	//red
	IMAGEMANAGER->addImage("Drafted1", "image/6_UI/playerSelect/red_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("Employed1", "image/6_UI/playerSelect/red_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	
	//green
	IMAGEMANAGER->addImage("Drafted2", "image/6_UI/playerSelect/green_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("Employed2", "image/6_UI/playerSelect/green_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	
	//yellow
	IMAGEMANAGER->addImage("Drafted3", "image/6_UI/playerSelect/yellow_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("Employed3", "image/6_UI/playerSelect/yellow_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	
	//blue
	IMAGEMANAGER->addImage("Drafted4", "image/6_UI/playerSelect/blue_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("Employed4", "image/6_UI/playerSelect/blue_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("cursor", "image/6_UI/playerSelect/cursor_frame.bmp", 96, 93, 2, 1, true, RGB(255, 0, 255), false);

	//카메라설정
	CAMERAMANAGER->setCamera(0, 0);

	//렉트 초기화
	for (int i = 0; i < 4; i++)
	{
		_character[i].rc = RectMake(240 * i, 270, 240, 300);
		_cursor[i] = RectMake(240 * i + 50, 150, IMAGEMANAGER->findImage("cursor")->getFrameWidth(), IMAGEMANAGER->findImage("cursor")->getFrameHeight());
		char str[128];
		sprintf_s(str, "Drafted%d", i + 1);
		_character[i].imageName = str;
	}

	_currentSelect = 0;
	_elapsedSec = 0;

	_isSelect = false;
	return S_OK;
}

void playerSelectScene::release()
{
}

void playerSelectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_currentSelect -= 1;
		if (_currentSelect <= 0) _currentSelect = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_currentSelect += 1;
		if (_currentSelect >= 3) _currentSelect = 3;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (!_isSelect)
		{
			_character[_currentSelect].rc.top -= 100;
			_character[_currentSelect].rc.bottom -= 100;

			char str[128];
			sprintf_s(str, "Employed%d", _currentSelect + 1);
			_character[_currentSelect].imageName = str;

			vector<string> vStr;
			_itoa_s(_currentSelect + 1, str, 2, 10);
			vStr.push_back(str);
			
			TXTDATA->txtSave("playerData.txt", vStr);

			_isSelect = true;
		}
		
	}
	_elapsedSec += TIMEMANAGER->getElapsedTime();
	if (!_isSelect)
	{
		if (_elapsedSec >= 0.5)
		{
			_elapsedSec -= 0.5;
			if (IMAGEMANAGER->findImage("cursor")->getFrameX() >= IMAGEMANAGER->findImage("cursor")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("cursor")->setFrameX(0);
			}
			else
			{
				IMAGEMANAGER->findImage("cursor")->setFrameX(IMAGEMANAGER->findImage("cursor")->getFrameX() + 1);
			}
		}
	}
	else
	{
		if (_elapsedSec >= 3.0f)
		{
			SCENEMANAGER->changeScene("start");
		}
	}
	
}

void playerSelectScene::render()
{
	IMAGEMANAGER->findImage("playerSelectBackground")->render(getMemDC(), 0, 0);
	for (int i = 0; i < 4; i++)
	{
		//Rectangle(getMemDC(), _character[i].rc);
		IMAGEMANAGER->findImage(_character[i].imageName)->render(getMemDC(), _character[i].rc.left, _character[i].rc.top);
		//Rectangle(getMemDC(), _cursor[i]);
	}

	if (!_isSelect)
	{
		IMAGEMANAGER->findImage("cursor")->frameRender(getMemDC(), _cursor[_currentSelect].left, _cursor[_currentSelect].top,
			IMAGEMANAGER->findImage("cursor")->getFrameX(), 0);
	}
}
