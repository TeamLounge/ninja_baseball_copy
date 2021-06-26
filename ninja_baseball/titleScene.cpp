#include "stdafx.h"
#include "titleScene.h"
#include <conio.h>

HRESULT titleScene::init()
{
	IMAGEMANAGER->addImage("title_background", "image/6_UI/title/title_background.bmp", WINSIZEX, WINSIZEY, false, RGB(255,0,255), false);
	IMAGEMANAGER->addImage("silhouette", "image/6_UI/title/silhouette.bmp", 900, 510, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("title_start", "image/6_UI/title/title_start_frame.bmp", 19200, 420, 20, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("title_frame", "image/6_UI/title/title_frame.bmp", 11745, 420, 15, 1, true, RGB(255, 0, 255), false);
	
	_silhouette = RectMakeCenter(WINSIZEX / 2, WINSIZEY + IMAGEMANAGER->findImage("silhouette")->getHeight()/2, IMAGEMANAGER->findImage("silhouette")->getWidth(), IMAGEMANAGER->findImage("silhouette")->getHeight());
	CAMERAMANAGER->setCamera(0, 0);

	_elapsedSec = 0;
	_isTitleStart = false;

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (_silhouette.top <= WINSIZEY / 2 - 90 - IMAGEMANAGER->findImage("silhouette")->getHeight()/2)
	{
		_silhouette.top = WINSIZEY / 2 - 90 - IMAGEMANAGER->findImage("silhouette")->getHeight()/2;
		_silhouette.bottom = _silhouette.top + IMAGEMANAGER->findImage("silhouette")->getHeight();
	}
	else
	{
		_silhouette.top -= 5;
		_silhouette.bottom = _silhouette.top + IMAGEMANAGER->findImage("silhouette")->getHeight();
	}

	if (_silhouette.top == WINSIZEY / 2 - 90 - IMAGEMANAGER->findImage("silhouette")->getHeight() / 2)
	{
		_elapsedSec += TIMEMANAGER->getElapsedTime();
		if (_elapsedSec >= 2.0f)
		{
			_elapsedSec -= 2.0f;
			_isTitleStart = true;
		}
	}

	if (_isTitleStart)
	{
		if (_elapsedSec >= 0.25f)
		{
			_elapsedSec -= 0.25f;
			if (IMAGEMANAGER->findImage("title_start")->getFrameX() >= IMAGEMANAGER->findImage("title_start")->getMaxFrameX())
			{
				_isTitleStart = false;
				_isTitleStoped = true;
			}
			else
			{
				IMAGEMANAGER->findImage("title_start")->setFrameX(IMAGEMANAGER->findImage("title_start")->getFrameX() + 1);
			}
		}
	}

	if (_isTitleStoped)
	{
		if (_elapsedSec >= 0.25f)
		{
			_elapsedSec -= 0.25f;
			if (IMAGEMANAGER->findImage("title_frame")->getFrameX() >= IMAGEMANAGER->findImage("title_frame")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("title_frame")->setFrameX(0);
			}
			else
			{
				IMAGEMANAGER->findImage("title_frame")->setFrameX(IMAGEMANAGER->findImage("title_frame")->getFrameX() + 1);
			}
		}

		if(KEYMANAGER->isOnceKeyDown())
		{
			SCENEMANAGER->changeScene("playerSelect");
		}
		
	}
}

void titleScene::render()
{
	IMAGEMANAGER->findImage("title_background")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("silhouette")->render(getMemDC(), _silhouette.left, _silhouette.top);
	if (_isTitleStart)
	{
		IMAGEMANAGER->findImage("title_start")->frameRender(getMemDC(), 0, 30);
	}
	if(_isTitleStoped)
	{
		IMAGEMANAGER->findImage("title_frame")->frameRender(getMemDC(), 123, 30);
	}
	
	//IMAGEMANAGER->findImage("title_start")->frameRender(getMemDC(), 0, 30, 19, 0);
	
	
}
