#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//이미지
	IMAGEMANAGER->addFrameImage("stolen", "image/6_UI/startScene/stolen_frame.bmp", 26880, 574, 28, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->findImage("stolen")->setFrameX(0);
	IMAGEMANAGER->findImage("stolen")->setFrameY(0);

	IMAGEMANAGER->addImage("start_background", "image/6_UI/startScene/background.bmp", WINSIZEX, 768, true, RGB(255, 0, 255), false);

	//다이얼로그
	_dialog.push_back("ONE DAY SIX BASEBALL ITEMS WERE");
	_dialog.push_back("STOLEN FROM THE BASEBALL HALL OF");
	_dialog.push_back("FAME BY A SECRET SOCIETY CALLED");
	_dialog.push_back("\"JADO.\"");

	_dialog.push_back("THE COMMISSIONER OF THE HALL ASKED");
	_dialog.push_back("NINJA BASEBALL BATMAN TO RETURN");
	_dialog.push_back("THE STOLEN ITEMS");

	for (int i = 0; i < 7; i++)
	{
		_dialogTextNum[i] = 0;
	}

	_dialogNow = 0;

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (_dialogTextNum[2] >= 17 && !_isFirstDialogEnd)
	{
		_elapsedSecForFrame += TIMEMANAGER->getElapsedTime();
		if (IMAGEMANAGER->findImage("stolen")->getFrameX() >= IMAGEMANAGER->findImage("stolen")->getMaxFrameX())
		{
			if (_elapsedSecForFrame >= 3.0f)
			{
				_elapsedSecForFrame -= 3.0f;
				_isFirstDialogEnd = true;
			}
		}
		else if (_elapsedSecForFrame >= 0.2f)
		{
			_elapsedSecForFrame -= 0.2f;
			if (IMAGEMANAGER->findImage("stolen")->getFrameX() >= IMAGEMANAGER->findImage("stolen")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("stolen")->setFrameX(IMAGEMANAGER->findImage("stolen")->getMaxFrameX());
			}
			else
			{
				IMAGEMANAGER->findImage("stolen")->setFrameX(IMAGEMANAGER->findImage("stolen")->getFrameX() + 1);
			}
		}
	}

	if (_dialogNow < 4 && !_isFirstDialogEnd)
	{
		_elapsedSecForText += TIMEMANAGER->getElapsedTime();
		if (_elapsedSecForText >= 0.1f)
		{
			_elapsedSecForText -= 0.1f;
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
	else if(_isFirstDialogEnd)
	{
		_elapsedSecForText += TIMEMANAGER->getElapsedTime();
		if (_elapsedSecForText >= 0.1f)
		{
			_elapsedSecForText -= 0.1f;
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

	if (_dialogTextNum[_dialog.size() - 1] == _dialog[6].length())
	{
		SCENEMANAGER->changeScene("stage");
	}
}

void startScene::render()
{
	IMAGEMANAGER->findImage("tile_background")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("start_background")->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("start_background")->getHeight());

	if (_dialogTextNum[2] >= 17 && !_isFirstDialogEnd)
	{
		IMAGEMANAGER->findImage("stolen")->frameRender(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("stolen")->getFrameHeight());
	}

	HFONT font = CreateFont(35, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("Retro Gaming"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	//그림자
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	if (!_isFirstDialogEnd)
	{
		for (int i = 0; i < 4; i++)
		{
			TextOut(getMemDC(), 152, WINSIZEY - 147 + 30 * i, _dialog[i].c_str(), _dialogTextNum[i]);
		}
	}
	else
	{
		for (int i = 4; i < _dialog.size(); i++)
		{
			TextOut(getMemDC(), 152, WINSIZEY - 147 + 30 * (i-4), _dialog[i].c_str(), _dialogTextNum[i]);
		}
	}

	//텍스트
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	if (!_isFirstDialogEnd)
	{
		for (int i = 0; i < 4; i++)
		{
			TextOut(getMemDC(), 150, WINSIZEY - 150 + 30 * i, _dialog[i].c_str(), _dialogTextNum[i]);
		}
	}
	else
	{
		for (int i = 4; i < _dialog.size(); i++)
		{
			TextOut(getMemDC(), 150, WINSIZEY - 150 + 30 * (i - 4), _dialog[i].c_str(), _dialogTextNum[i]);
		}
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
