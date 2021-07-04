#include "stdafx.h"
#include "gameOverUI.h"

HRESULT gameOverUI::init()
{
	IMAGEMANAGER->addImage("game_over", "image/6_UI/inGame/game_over.bmp", 648, 144, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("continue", "image/6_UI/inGame/continue.bmp", 432, 96, true, RGB(255, 0, 255), false);
	_timerUI = new timerUI;
	_timerUI->init(9, 1, CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() + 100);
	return S_OK;
}

void gameOverUI::release()
{
}

void gameOverUI::update()
{
	if (_isGameOver)
	{
		_timerUI->update(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() + 100);
		if (_timerUI->getTime() <= 0)
		{
			SCENEMANAGER->changeScene("title");
			SOUNDMANAGER->stop("continue");
			_isGameOver = false;
		}
	}
	else
	{
		_timerUI->setX(CAMERAMANAGER->getCameraCenterX());
		_timerUI->setY(CAMERAMANAGER->getCameraCenterY() + 100);
	}
}

void gameOverUI::render()
{
	if (_isGameOver)
	{
		IMAGEMANAGER->findImage("game_over")->render(getMemDC(),
			CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("game_over")->getWidth() / 2,
			170);

		IMAGEMANAGER->findImage("continue")->render(getMemDC(),
			CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("continue")->getWidth() / 2,
			360);

		_timerUI->render();
	}
}
