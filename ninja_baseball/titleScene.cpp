#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init()
{
	IMAGEMANAGER->addImage("title_background", "image/6_UI/title/title_background.bmp", WINSIZEX, WINSIZEY, false, RGB(255,0,255), false);
	IMAGEMANAGER->addImage("silhouette", "image/6_UI/title/silhouette.bmp", 900, 510, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("title_frame", "image/6_UI/title/title_frame.bmp", 11745, 420, 15, 1, true, RGB(255, 0, 255), false);
	
	_silhouette = RectMakeCenter(WINSIZEX / 2, WINSIZEY + IMAGEMANAGER->findImage("silhouette")->getHeight()/2, IMAGEMANAGER->findImage("silhouette")->getWidth(), IMAGEMANAGER->findImage("silhouette")->getHeight());
	CAMERAMANAGER->setCamera(0, 0);
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
}

void titleScene::render()
{
	IMAGEMANAGER->findImage("title_background")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("silhouette")->render(getMemDC(), _silhouette.left, _silhouette.top);

	IMAGEMANAGER->findImage("title_frame")->frameRender(getMemDC(), 150, 30, 0, 0);
}
