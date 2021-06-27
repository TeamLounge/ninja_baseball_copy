#include "stdafx.h"
#include "endingScene.h"

HRESULT endingScene::init()
{
	//�̹��� �߰�
	IMAGEMANAGER->addImage("tile_background", "image/6_UI/tile_background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("character_scene", "image/6_UI/endingScene/stage1CleardCharacter.bmp", WINSIZEX, 384, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ending_background", "image/6_UI/endingScene/ending_background.bmp", 1440, 384, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->findImage("ending_background")->setX(0);

	//ī�޶� ����
	CAMERAMANAGER->setCamera(0, 0);

	//���̾�α� �� ��� ��Ʈ
	_textRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 120, WINSIZEX + 2, 242);

	_sceneHeight = 0;

	_elapsedTime = 0;

	_dialogTextNum = 0;

	sprintf_s(str, "ONE DAY SIX BASEBALL ITEMS WERE");
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	//ĳ���� ���� ĳ���� ����� ���� ��µǸ� ��� ������
	if (_sceneHeight == IMAGEMANAGER->findImage("ending_background")->getHeight()/2)
	{
		if (IMAGEMANAGER->findImage("ending_background")->getX() + IMAGEMANAGER->findImage("ending_background")->getWidth() <= WINSIZEX)
		{
			IMAGEMANAGER->findImage("ending_background")->setX(WINSIZEX - IMAGEMANAGER->findImage("ending_background")->getWidth());
		}
		else
		{
			IMAGEMANAGER->findImage("ending_background")->setX(IMAGEMANAGER->findImage("ending_background")->getX() - 3);
		}

		//���̾�α׵� ���
		_elapsedTime += TIMEMANAGER->getElapsedTime();
		if (_elapsedTime >= 0.2f)
		{
			_elapsedTime -= 0.2f;
			if (_dialogTextNum >= strlen(str))
			{
				_dialogTextNum = strlen(str);
			}
			else
			{
				_dialogTextNum++;
			}

		}
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_dialogTextNum = strlen(str);
		}
	}

	//ĳ���� �� y ��� ������ ����
	if (_sceneHeight >= IMAGEMANAGER->findImage("character_scene")->getHeight() / 2)
	{
		_sceneHeight = IMAGEMANAGER->findImage("character_scene")->getHeight() / 2;
	}
	else
	{
		_sceneHeight += 4;
	}
}

void endingScene::render()
{
	//���� �޹���� Ÿ��
	IMAGEMANAGER->findImage("tile_background")->render(getMemDC());

	//ĳ���� �� ���
	IMAGEMANAGER->findImage("ending_background")->render(getMemDC(), IMAGEMANAGER->findImage("ending_background")->getX(), 144 + IMAGEMANAGER->findImage("ending_background")->getHeight()/2 - _sceneHeight,
		0, IMAGEMANAGER->findImage("ending_background")->getHeight()/2 - _sceneHeight, IMAGEMANAGER->findImage("ending_background")->getWidth(), _sceneHeight * 2);
	
	//���̾�α� �� ���
	HBRUSH brush = CreateSolidBrush(RGB(105, 105, 105));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	HPEN pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
	if (_sceneHeight == IMAGEMANAGER->findImage("character_scene")->getHeight() / 2)
	{
		Rectangle(getMemDC(), _textRC);
	}
	SelectObject(getMemDC(), oldPen);
	DeleteObject(pen);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	//ĳ���� ��
	IMAGEMANAGER->findImage("character_scene")->render(getMemDC(), 0, 144 + IMAGEMANAGER->findImage("character_scene")->getHeight() / 2 - _sceneHeight, 
		0, IMAGEMANAGER->findImage("character_scene")->getHeight() /2 - _sceneHeight, WINSIZEX, _sceneHeight * 2);

	TextOut(getMemDC(), 100, 100, str, _dialogTextNum);
}