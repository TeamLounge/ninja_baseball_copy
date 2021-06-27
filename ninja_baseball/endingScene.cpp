#include "stdafx.h"
#include "endingScene.h"

HRESULT endingScene::init()
{
	//이미지 추가
	IMAGEMANAGER->addImage("tile_background", "image/6_UI/tile_background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("character_scene", "image/6_UI/endingScene/stage1CleardCharacter.bmp", WINSIZEX, 384, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ending_background", "image/6_UI/endingScene/ending_background.bmp", 1440, 384, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->findImage("ending_background")->setX(0);
	IMAGEMANAGER->addImage("ui_green", "image/6_UI/inGame/green.bmp", 63, 72, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("ui_red", "image/6_UI/inGame/red.bmp", 63, 72, true, RGB(255, 0, 255), false);

	//카메라 설정
	CAMERAMANAGER->setCamera(0, 0);

	//다이얼로그 뒷 배경 렉트
	_textRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 120, WINSIZEX + 2, 242);

	_sceneHeight = 0;

	_elapsedTime = 0;

	for (int i = 0; i < 3; i++)
	{
		_dialogTextNum[i] = 0;
	}
	_dialogNow = 0;

	_dialog.push_back("GOOD, WE GOT THE BAT BACK!!");
	_dialog.push_back("THE NEXT ENEMY IS WAITING FOR US");
	_dialog.push_back("ON THE STEAM SHIP!!");
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	//캐릭터 씬과 캐릭터 배경이 전부 출력되면 배경 움직임
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

		//다이얼로그도 출력
		_elapsedTime += TIMEMANAGER->getElapsedTime();

		if (_dialogNow < _dialog.size())
		{
			if (_elapsedTime >= 0.2f)
			{
				_elapsedTime -= 0.2f;
				if (_dialogTextNum[_dialogNow] >= _dialog[_dialogNow].length())
				{
					_dialogTextNum[_dialogNow] = _dialog[_dialogNow].length();
				}
				else
				{
					_dialogTextNum[_dialogNow]++;
				}
			}
			if (_dialogTextNum[_dialogNow] == _dialog[_dialogNow].length())
			{
				_dialogNow++;
			}
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_dialogTextNum[_dialogNow] = _dialog[_dialogNow].length();
			}
		}
	}

	//캐릭터 씬 y 출력 사이즈 조절
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
	//가장 뒷배경인 타일
	IMAGEMANAGER->findImage("tile_background")->render(getMemDC());

	//캐릭터 뒤 배경
	IMAGEMANAGER->findImage("ending_background")->render(getMemDC(), IMAGEMANAGER->findImage("ending_background")->getX(), 144 + IMAGEMANAGER->findImage("ending_background")->getHeight()/2 - _sceneHeight,
		0, IMAGEMANAGER->findImage("ending_background")->getHeight()/2 - _sceneHeight, IMAGEMANAGER->findImage("ending_background")->getWidth(), _sceneHeight * 2);
	
	//다이얼로그 뒷 배경
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

	//캐릭터 씬
	IMAGEMANAGER->findImage("character_scene")->render(getMemDC(), 0, 144 + IMAGEMANAGER->findImage("character_scene")->getHeight() / 2 - _sceneHeight, 
		0, IMAGEMANAGER->findImage("character_scene")->getHeight() /2 - _sceneHeight, WINSIZEX, _sceneHeight * 2);
	
	HFONT font = CreateFont(35, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("Retro Gaming"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	//그림자
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	for (int i = 0; i < 2; i++)
	{
		TextOut(getMemDC(), 152, 553 + 110 * i, _dialog[i].c_str(), _dialogTextNum[i]);
	}
	TextOut(getMemDC(), 152, 553 + 135, _dialog[2].c_str(), _dialogTextNum[2]);

	//텍스트
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	for (int i = 0; i < 2; i++)
	{
		TextOut(getMemDC(), 150, 550 + 110 * i, _dialog[i].c_str(), _dialogTextNum[i]);
	}
	TextOut(getMemDC(), 150, 550 + 135, _dialog[2].c_str(), _dialogTextNum[2]);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	if (_dialogTextNum[0] != 0)
	{
		IMAGEMANAGER->findImage("ui_green")->render(getMemDC(), 60, _textRC.top + 2);
	}
	if (_dialogTextNum[1] != 0)
	{
		IMAGEMANAGER->findImage("ui_red")->render(getMemDC(), 60, _textRC.top + 120);
	}
}
