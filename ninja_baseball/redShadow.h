#pragma once
#include "gameNode.h"
#include "player.h"

class redShadow :public gameNode
{
private:
	
	float _x;
	float _y;
	RECT _rc;
	image* _shadowImage;

	player* _player;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//그림자 겟터
	float getShadowX() { return _x; }
	float getShadowY() { return _y; }
	RECT getShadowRect() { return _rc; }
	image* getShadowImage() { return _shadowImage; }

	//그림자 셋터
	void setShadowX(float x) { _x = x; }
	void setShadowY(float y) { _y = y; }
	void setShadowRect(RECT rc) { _rc = rc; }
	void setShadowImage(image* shadowImage) { _shadowImage = shadowImage; }
};

