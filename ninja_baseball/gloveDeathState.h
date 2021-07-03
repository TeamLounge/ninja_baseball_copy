#pragma once
#include "gloveState.h"

class glove;

class gloveDeathState :public gloveState
{
public:

	int frameCount;
	int count;

	virtual gloveState* inputHandle(glove* glove);
	virtual void update(glove* glove);
	virtual void enter(glove* glove);
	virtual void exit(glove* glove);


};