#include "stdafx.h"
#include "stageScene2.h"

HRESULT stageScene2::init()
{
	IMAGEMANAGER->addImage("stage_2", "image/1_Map/stage1-2.bmp", WINSIZEX, BACKGROUNDY, true, RGB(255, 0, 255), false);
	CAMERAMANAGER->setCamera(0, BACKGROUNDY - WINSIZEY);

	vText = TXTDATA->txtLoad("playerData.txt");

	_x = WINSIZEX - (BACKGROUNDX - atoi(vText[3].c_str()));
	_y = BACKGROUNDY - (WINSIZEY - atoi(vText[4].c_str()));

	if (atoi(vText[0].c_str()) == 1)
	{
		_imageName = "red_jump";
	}
	else
	{
		_imageName = "Ryno_jumpAttack";
	}

	IMAGEMANAGER->findImage(_imageName)->setFrameX(0);
	if (atoi(vText[5].c_str()))
	{
		IMAGEMANAGER->findImage(_imageName)->setFrameY(0);
	}
	else
	{
		IMAGEMANAGER->findImage(_imageName)->setFrameY(1);
	}
	_distance = _y - (BACKGROUNDY - WINSIZEY / 2);
	return S_OK;
}

void stageScene2::release()
{
}

void stageScene2::update()
{
	_y -= 30;
	CAMERAMANAGER->updateCamera(WINSIZEX / 2, _y - _distance);
	if (_y < CAMERAMANAGER->getCameraCenterY() + _distance)
	{

		SCENEMANAGER->changeScene("stage3");
	}
}

void stageScene2::render()
{
	IMAGEMANAGER->findImage("stage_2")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage(_imageName)->frameRender(getMemDC(),
		_x - IMAGEMANAGER->findImage(_imageName)->getFrameWidth() / 2,
		_y - IMAGEMANAGER->findImage(_imageName)->getFrameHeight() / 2);
}
