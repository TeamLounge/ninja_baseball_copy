#pragma once
#include "gameNode.h"

struct Object
{
	image* img;
	float _x, _y;
	RECT _obj_rc;
};

class baseball : public gameNode
{
private:
	Object _obj;

public:
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	float getX() { return _obj._x; }
	float getY() { return _obj._y; }
	image* getImage() { return _obj.img; }
	RECT getRect() { return _obj._obj_rc; }

	void setX(float x) { _obj._x = x; }
	void setY(float y) { _obj._y = y; }
	void getImage(image* img) { _obj.img = img; }
	void getRect(RECT rc) { _obj._obj_rc = rc; }

};

class trashCan : public gameNode
{
private:
	Object _obj;

public:
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	float getX() { return _obj._x; }
	float getY() { return _obj._y; }
	image* getImage() { return _obj.img; }
	RECT getRect() { return _obj._obj_rc; }

	void setX(float x) { _obj._x = x; }
	void setY(float y) { _obj._y = y; }
	void getImage(image* img) { _obj.img = img; }
	void getRect(RECT rc) { _obj._obj_rc = rc; }

};

class banana : public gameNode
{
private:
	Object _obj;

public:
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	float getX() { return _obj._x; }
	float getY() { return _obj._y; }
	image* getImage() { return _obj.img; }
	RECT getRect() { return _obj._obj_rc; }

	void setX(float x) { _obj._x = x; }
	void setY(float y) { _obj._y = y; }
	void getImage(image* img) { _obj.img = img; }
	void getRect(RECT rc) { _obj._obj_rc = rc; }

};

