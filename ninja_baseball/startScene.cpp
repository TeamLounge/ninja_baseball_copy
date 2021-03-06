#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//이미지
	IMAGEMANAGER->addFrameImage("stolen", "image/6_UI/startScene/stolen_frame.bmp", 27840, 574, 29, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("start_background", "image/6_UI/startScene/background.bmp", WINSIZEX, 384, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("start_dialog_background", "image/6_UI/startScene/dialogBackground.bmp", WINSIZEX, 191, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("start_dialog_background2", "image/6_UI/startScene/dialogBackground2.bmp", WINSIZEX, 191, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("statue", "image/6_UI/startScene/statue.bmp", 177, 305, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("face_yellow", "image/6_UI/startScene/face_yellow.bmp", 240, 192, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("face_blue", "image/6_UI/startScene/face_blue.bmp", 240, 192, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("face_red", "image/6_UI/startScene/face_red.bmp", 240, 192, true, RGB(255, 0, 255), false);

	IMAGEMANAGER->findImage("stolen")->setFrameX(0);
	IMAGEMANAGER->findImage("stolen")->setFrameY(0);

	CAMERAMANAGER->setCamera(0, 0);

	//다이얼로그
	_dialog.clear();

	_dialog.push_back("ONE DAY SIX BASEBALL ITEMS WERE");
	_dialog.push_back("STOLEN FROM THE BASEBALL HALL OF");
	_dialog.push_back("FAME BY A SECRET SOCIETY CALLED");
	_dialog.push_back("\"JADO.\"");

	_dialog.push_back("THE COMMISSIONER OF THE HALL ASKED");
	_dialog.push_back("NINJA BASEBALL BATMAN TO RETURN");
	_dialog.push_back("THE STOLEN ITEMS");

	_backgroundHeight = 0;
	_dialogNow = 0;

	for (int i = 0; i < 7; i++)
	{
		_dialogTextNum[i] = 0;
	}

	_faceImgName = "face_yellow";
	_dBackgroundName = "start_dialog_background";

	_elapsedSecForFrame = 0;
	_elapsedSecForText = 0;

	
	_isFirstDialogEnd = false;

	return S_OK;
}

void startScene::release()
{

}

void startScene::update()
{
	//배경이 전부 나오면 다이얼로그 출력 시작
	if (_backgroundHeight == IMAGEMANAGER->findImage("start_background")->getHeight() / 2)
	{
		//씬 넘기기
		if (_dialogTextNum[2] >= 17 && !_isFirstDialogEnd)
		{
			_elapsedSecForFrame += TIMEMANAGER->getElapsedTime();
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_isFirstDialogEnd = true;
			}
			if (IMAGEMANAGER->findImage("stolen")->getFrameX() >= IMAGEMANAGER->findImage("stolen")->getMaxFrameX())
			{
				if (_elapsedSecForFrame >= 1.0f)
				{
					_elapsedSecForFrame -= 1.0f;
					_isFirstDialogEnd = true;
				}
			}
			else if (_elapsedSecForFrame >= 0.08f)
			{
				_elapsedSecForFrame -= 0.08f;
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
		//첫번째 다이얼로그
		if (_dialogNow < 4 && !_isFirstDialogEnd)
		{
			_elapsedSecForText += TIMEMANAGER->getElapsedTime();
			if (_elapsedSecForText >= 0.08f)
			{
				_elapsedSecForText -= 0.08f;
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
		else if (_isFirstDialogEnd && _dialogNow<_dialog.size())
		{
			//두번째 다이얼로그
			_elapsedSecForText += TIMEMANAGER->getElapsedTime();
			if (_elapsedSecForText >= 0.05f)
			{
				_elapsedSecForText -= 0.05f;
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

	//다이얼로그가 전부 나오고, 배경이 사라지면 씬 바꿈
	if (_dialogTextNum[_dialog.size() - 1] == _dialog[_dialog.size() - 1].length())
	{
		_backgroundHeight -= 4;
		if (_backgroundHeight < 0)
		{
			SCENEMANAGER->changeScene("stage1");
		}
	}
	else
	{
		//배경 y 출력 사이즈 조절
		if (_backgroundHeight >= IMAGEMANAGER->findImage("start_background")->getHeight() / 2)
		{
			_backgroundHeight = IMAGEMANAGER->findImage("start_background")->getHeight() / 2;
		}
		else
		{
			_backgroundHeight += 4;
		}
	}

	//장면 효과
	if ((_dialogTextNum[4] >= 1 && _dialogTextNum[4] < 18) || (_dialogTextNum[5] >= 4 && _dialogTextNum[5] < 23) || _dialogTextNum[6] >= 12)
	{
		_faceImgName = "face_blue";
		_dBackgroundName = "start_dialog_background";
	}
	if ((_dialogTextNum[4] >= 18 && _dialogTextNum[5] < 4) || (_dialogTextNum[5] >= 23 && _dialogTextNum[6] < 12))
	{
		_faceImgName = "face_red";
		_dBackgroundName = "start_dialog_background2";
	}

	
}

void startScene::render()
{
	IMAGEMANAGER->findImage("tile_background")->render(getMemDC(), 0, 0);
	//뒷 배경
	IMAGEMANAGER->findImage("start_background")->render(getMemDC(), IMAGEMANAGER->findImage("start_background")->getX(), 194 + IMAGEMANAGER->findImage("start_background")->getHeight() / 2 - _backgroundHeight,
		0, IMAGEMANAGER->findImage("start_background")->getHeight() / 2 - _backgroundHeight, IMAGEMANAGER->findImage("start_background")->getWidth(), _backgroundHeight * 2);
	//다이얼로그 뒤 배경
	if (_backgroundHeight == IMAGEMANAGER->findImage("start_background")->getHeight() / 2)
	{
		IMAGEMANAGER->findImage(_dBackgroundName)->render(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage(_dBackgroundName)->getHeight());
	}
	//얼굴 이미지
	IMAGEMANAGER->findImage(_faceImgName)->render(getMemDC(), 42, WINSIZEY - 359);

	//동상 이미지
	if (IMAGEMANAGER->findImage("stolen")->getFrameX() == 0 && _backgroundHeight == IMAGEMANAGER->findImage("start_background")->getHeight() / 2)
	{
		IMAGEMANAGER->findImage("statue")->render(getMemDC(), 399, WINSIZEY - IMAGEMANAGER->findImage("stolen")->getFrameHeight() + 20);
	
	}
	//훔쳐가는 장면
	if (_dialogTextNum[2] >= 17 && !_isFirstDialogEnd)
	{
		IMAGEMANAGER->findImage("stolen")->frameRender(getMemDC(), 0, WINSIZEY - IMAGEMANAGER->findImage("stolen")->getFrameHeight());
	}

	

	if (_backgroundHeight == IMAGEMANAGER->findImage("start_background")->getHeight() / 2)
	{
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
				TextOut(getMemDC(), 152, WINSIZEY - 147 + 30 * (i - 4), _dialog[i].c_str(), _dialogTextNum[i]);
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
	
}
