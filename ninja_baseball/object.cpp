#include "stdafx.h"
#include "object.h"

HRESULT baseball::init(POINT position)
{
	_obj._img = IMAGEMANAGER->addImage("baseball", "image/5_Item/baseball.bmp", 59, 53, true, RGB(255, 0, 255), false);
	_obj._shadow = IMAGEMANAGER->addImage("baseballshadow", "image/5_Item/baseballshadow.bmp", 59, 14, true, RGB(255, 0, 255), false);
	_obj._x = position.x;
	_obj._y = position.y;
	_obj._shadowX = position.x;
	_obj._shadowY = position.y+_obj._img->getHeight()/2;
	_obj._obj_rc = RectMakeCenter(_obj._x, _obj._y, 59, 53);
	_obj._shadow_rc = RectMakeCenter(_obj._shadowX, _obj._shadowY, _obj._shadow->getWidth(), _obj._shadow->getHeight());

	ishold = isattack = false;

	return S_OK;
}

void baseball::release()
{

}

void baseball::update(bool Right)
{
	if (isattack)
	{
		if (Right)
			_obj._x += 8;
		else
			_obj._x -= 8;
		_obj._shadowX = _obj._x;
		_obj._img->setCenter(_obj._x ,_obj._y);
		_obj._shadow->setCenter(_obj._shadowX , _obj._shadowY);
		_obj._obj_rc = RectMakeCenter(_obj._x, _obj._y, _obj._img->getWidth(), _obj._img->getHeight());
		_obj._shadow_rc = RectMakeCenter(_obj._shadowX, _obj._shadowY, _obj._shadow->getWidth(), _obj._shadow->getHeight());
		if (CAMERAMANAGER->getCameraRIGHT() < _obj._x || CAMERAMANAGER->getCameraLEFT()> _obj._x )
		{
			isattack = false;
		}
	}
}

void baseball::render()
{
	Rectangle(getMemDC(), _obj._obj_rc);
	Rectangle(getMemDC(), _obj._shadow_rc);
	_obj._shadow->render(getMemDC() , _obj._shadow_rc.left, _obj._shadow_rc.top);
	_obj._img->render(getMemDC(), _obj._obj_rc.left, _obj._obj_rc.top);
}

HRESULT trashCan::init(POINT position)
{
	return S_OK;
}

void trashCan::release()
{

}

void trashCan::update()
{

}

void trashCan::render()
{

}

HRESULT banana::init(POINT position)
{
	return S_OK;
}

void banana::release()
{

}

void banana::update()
{

}

void banana::render()
{

}
