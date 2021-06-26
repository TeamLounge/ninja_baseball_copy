#pragma once

#include "gameNode.h"
#include "ybState.h"

struct YELLOWBASEBALL
{
	RECT rc;
	image* img;
	
	float x, y;

};

class yellowBaseball :public gameNode
{
private:

public:

	void InputHandle();
	ybState* _ybState;

	YELLOWBASEBALL _yellowBaseball;
	


	yellowBaseball() {};
	~yellowBaseball() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();


};
