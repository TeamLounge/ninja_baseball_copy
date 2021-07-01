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

	ishold = isattack = isappear = isfire =false;

	return S_OK;
}

void baseball::release()
{

}

void baseball::update(bool Right)
{
	if (isattack)
	{
		if (Right&& isfire)
			speed = 8;
		else if(!Right&&isfire)
			speed = -8;
		isfire = false;
		_obj._x += speed;
		_obj._shadowX = _obj._x;
		_obj._img->setCenter(_obj._x ,_obj._y);
		_obj._shadow->setCenter(_obj._shadowX , _obj._shadowY);
		_obj._obj_rc = RectMakeCenter(_obj._x, _obj._y, _obj._img->getWidth(), _obj._img->getHeight());
		_obj._shadow_rc = RectMakeCenter(_obj._shadowX, _obj._shadowY, _obj._shadow->getWidth(), _obj._shadow->getHeight());
		if (CAMERAMANAGER->getCameraRIGHT() < _obj._x || CAMERAMANAGER->getCameraLEFT()> _obj._x )
		{
			isattack = false;
			isappear = false;
		}
	}
}

void baseball::render()
{
	_obj._shadow->render(getMemDC() , _obj._shadow_rc.left, _obj._shadow_rc.top);
	_obj._img->render(getMemDC(), _obj._obj_rc.left, _obj._obj_rc.top);
}

HRESULT trashCan::init(POINT position, int present)
{
	_obj._img = IMAGEMANAGER->addImage("trashCan", "image/5_Item/trashCan.bmp", 99, 137, true, RGB(255, 0, 255), false);
	_obj._shadow = IMAGEMANAGER->addImage("trashshadow", "image/5_Item/trahsCanshadow.bmp", 95, 23, true, RGB(255, 0, 255), false);
	_obj._x = position.x;
	_obj._y = position.y;
	_obj._shadowX = position.x;
	_obj._shadowY = position.y + _obj._img->getHeight() / 2;
	_obj._obj_rc = RectMakeCenter(_obj._x, _obj._y, 99, 137);
	_obj._shadow_rc = RectMakeCenter(_obj._shadowX, _obj._shadowY, _obj._shadow->getWidth(), _obj._shadow->getHeight());

	char str[128];
	sprintf_s(str, "trashCanPiece%d",present);
	peice1 = IMAGEMANAGER->addImage(str, "image/5_Item/trashCanPiece1.bmp", 54, 80, true, RGB(255, 0, 255),false);
	sprintf_s(str, "trashCanPiece%d", present+3);
	peice2 = IMAGEMANAGER->addImage(str, "image/5_Item/trashCanPiece2.bmp", 55, 41, true, RGB(255, 0, 255), false);
	sprintf_s(str, "trashCanPiece%d", present+6);
	peice3 = IMAGEMANAGER->addImage(str, "image/5_Item/trashCanPiece3.bmp", 52, 69, true, RGB(255, 0, 255), false);
	peice1->setCenter(position.x , position.y);
	peice2->setCenter(position.x, position.y);
	peice3->setCenter(position.x, position.y);

	_present = present;
	damagecount = pasty = presenty = 0;
	jumppower = 4.f;
	gravity = 0.2f;
	isdamage = iscrush =  false;
	return S_OK;
}

void trashCan::release()
{

}

void trashCan::update()
{
	if (isdamage&&damagecount<3)
	{
		damagecount++;
		isdamage = false;
	}
	if (damagecount == 3)
	{
		iscrush = true;
	}
	if (iscrush)
	{
		peice1->setCenter(peice1->getCenterX() + 5, peice1->getCenterY() - jumppower);
		peice2->setCenter(peice2->getCenterX() - 3, peice1->getCenterY() - jumppower);
		peice3->setCenter(peice3->getCenterX() - 1, peice1->getCenterY() - jumppower);
		jumppower -= gravity;
	}
}

void trashCan::render()
{
	if (!iscrush) {
		_obj._shadow->render(getMemDC(), _obj._shadow_rc.left, _obj._shadow_rc.top);
		_obj._img->render(getMemDC(), _obj._obj_rc.left, _obj._obj_rc.top);
	}
	else
	{
		peice1->render(getMemDC());
		peice2->render(getMemDC());
		peice3->render(getMemDC());
	}
}

HRESULT banana::init(POINT position)
{
	_obj._img = IMAGEMANAGER->addImage("banana", "image/5_Item/banana.bmp", 138, 105, true, RGB(255, 0, 255), false);
	_obj._shadow = IMAGEMANAGER->addImage("bananashadow", "image/5_Item/bananashadow.bmp", 95, 23, true, RGB(255, 0, 255), false);
	_obj._x = position.x;
	_obj._y = position.y;
	_obj._shadowX = position.x;
	_obj._shadowY = position.y + _obj._img->getHeight() / 2 -10;
	_obj._obj_rc = RectMakeCenter(_obj._x, _obj._y, _obj._img->getWidth(), _obj._img->getHeight());
	_obj._shadow_rc = RectMakeCenter(_obj._shadowX, _obj._shadowY, _obj._shadow->getWidth(), _obj._shadow->getHeight());

	ishold = iseat = isappear = false;

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

	_obj._shadow->render(getMemDC(), _obj._shadow_rc.left, _obj._shadow_rc.top);
	_obj._img->render(getMemDC(), _obj._obj_rc.left, _obj._obj_rc.top);
}

HRESULT cereal::init(POINT position)
{
	_obj._img = IMAGEMANAGER->addImage("cereal", "image/5_Item/cereal.bmp", 170, 131, true, RGB(255, 0, 255), false);
	_obj._shadow = IMAGEMANAGER->addImage("cerealshadow", "image/5_Item/cerealshadow.bmp", 95, 23, true, RGB(255, 0, 255), false);
	_obj._x = position.x;
	_obj._y = position.y;
	_obj._shadowX = position.x;
	_obj._shadowY = position.y + _obj._img->getHeight() / 2 - 10;
	_obj._obj_rc = RectMakeCenter(_obj._x, _obj._y, _obj._img->getWidth(), _obj._img->getHeight());
	_obj._shadow_rc = RectMakeCenter(_obj._shadowX, _obj._shadowY, _obj._shadow->getWidth(), _obj._shadow->getHeight());

	ishold = iseat = isappear = false;

	return S_OK;
}

void cereal::release()
{
}

void cereal::update()
{

}

void cereal::render()
{
	_obj._shadow->render(getMemDC(), _obj._shadow_rc.left, _obj._shadow_rc.top);
	_obj._img->render(getMemDC(), _obj._obj_rc.left, _obj._obj_rc.top);
}
