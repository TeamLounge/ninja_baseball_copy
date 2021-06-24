#include "stdafx.h"
#include "playerSelectScene.h"

HRESULT playerSelectScene::init()
{
	IMAGEMANAGER->addImage("playerSelectBackground", "image/6_UI/playerSelect/background_playerSelect.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, 0);
	return S_OK;
}

void playerSelectScene::release()
{
}

void playerSelectScene::update()
{
	
}

void playerSelectScene::render()
{
	IMAGEMANAGER->findImage("playerSelectBackground")->render(getMemDC(), 0, 0);

}
