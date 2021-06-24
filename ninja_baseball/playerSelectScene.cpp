#include "stdafx.h"
#include "playerSelectScene.h"

HRESULT playerSelectScene::init()
{
	//배경
	IMAGEMANAGER->addImage("playerSelectBackground", "image/6_UI/playerSelect/background_playerSelect.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	
	//캐릭터
	IMAGEMANAGER->addImage("redDrafted", "image/6_UI/playerSelect/red_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("redEmployed", "image/6_UI/playerSelect/red_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("greenDrafted", "image/6_UI/playerSelect/green_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("greenEmployed", "image/6_UI/playerSelect/green_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellowDrafted", "image/6_UI/playerSelect/yellow_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("yellowEmployed", "image/6_UI/playerSelect/yellow_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("blueDrafted", "image/6_UI/playerSelect/blue_select1.bmp", 240, 300, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("blueEmployed", "image/6_UI/playerSelect/blue_select2.bmp", 240, 288, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("cursor", "image/6_UI/playerSelect/cursor_frame.bmp", 96, 93, 2, 1, true, RGB(255, 0, 255), false);

	//카메라설정
	CAMERAMANAGER->setCamera(0, 0);

	_character[0].imageName = "redDrafted";
	_character[1].imageName = "greenDrafted";
	_character[2].imageName = "yellowDrafted";
	_character[3].imageName = "blueDrafted";

	//렉트 초기화
	for (int i = 0; i < 4; i++)
	{
		_character[i].rc = RectMake(240 * i, 270, 240, 300);
		_cursor[i] = RectMake(240 * i + 50, 150, IMAGEMANAGER->findImage("cursor")->getFrameWidth(), IMAGEMANAGER->findImage("cursor")->getFrameHeight());
	}

	_currentSelect = 0;
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

	IMAGEMANAGER->findImage("cursor")->frameRender(getMemDC(), _cursor[_currentSelect].left, _cursor[_currentSelect].top, 
		IMAGEMANAGER->findImage("cursor")->getFrameX(), 0);
}
