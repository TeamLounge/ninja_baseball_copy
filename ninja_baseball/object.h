#pragma once
#include "gameNode.h"

struct Object
{
	image* _img;
	image* _shadow;
	float _x, _y;
	float _shadowX, _shadowY;
	RECT _obj_rc ,_shadow_rc;
};

class baseball : public gameNode
{
private:
	Object _obj;

public:
	bool isattack , ishold;
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update(bool Right);
	virtual void render();

	float getX() { return _obj._x; }
	float getY() { return _obj._y; }
	float getShadowX() { return _obj._shadowX; }
	float getShadowY() { return _obj._shadowY; }
	image* getImage() { return _obj._img; }
	image* getShadow() { return _obj._shadow; }
	RECT getRect() { return _obj._obj_rc; }
	RECT getShadowRect() { return _obj._shadow_rc; }

	void setX(float x) { _obj._x = x; }
	void setY(float y) { _obj._y = y; }
	void setShadowX(float x) { _obj._shadowX = x; }
	void setShadowY(float y) { _obj._shadowY = y; }
	void setImage(image* img) { _obj._img = img; }
	void setShadow(image* img) {  _obj._shadow = img; }
	void setRect(RECT rc) { _obj._obj_rc = rc; }
	void setShadowRect(RECT rc) { _obj._shadow_rc = rc; }
};

class trashCan : public gameNode
{
private:
	Object _obj;

public:
	bool iscrush;

	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();


	float getX() { return _obj._x; }
	float getY() { return _obj._y; }
	float getShadowX() { return _obj._shadowX; }
	float getShadowY() { return _obj._shadowY; }
	image* getImage() { return _obj._img; }
	image* getShadow() { return _obj._shadow; }
	RECT getRect() { return _obj._obj_rc; }
	RECT getShadowRect() { return _obj._shadow_rc; }

	void setX(float x) { _obj._x = x; }
	void setY(float y) { _obj._y = y; }
	void setShadowX(float x) { _obj._shadowX; }
	void setShadowY(float y) { _obj._shadowY; }
	void setImage(image* img) { _obj._img = img; }
	void setShadow(image* img) { _obj._shadow = img; }
	void setRect(RECT rc) { _obj._obj_rc = rc; }
	void setShadowRect(RECT rc) { _obj._shadow_rc; }

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
	float getShadowX() { return _obj._shadowX; }
	float getShadowY() { return _obj._shadowY; }
	image* getImage() { return _obj._img; }
	image* getShadow() { return _obj._shadow; }
	RECT getRect() { return _obj._obj_rc; }
	RECT getShadowRect() { return _obj._shadow_rc; }

	void setX(float x) { _obj._x = x; }
	void setY(float y) { _obj._y = y; }
	void setShadowX(float x) { _obj._shadowX; }
	void setShadowY(float y) { _obj._shadowY; }
	void setImage(image* img) { _obj._img = img; }
	void setShadow(image* img) { _obj._shadow = img; }
	void setRect(RECT rc) { _obj._obj_rc = rc; }
	void setShadowRect(RECT rc) { _obj._shadow_rc; }

};

