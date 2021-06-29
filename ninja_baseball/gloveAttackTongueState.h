#pragma once
#include "gloveState.h"

class glove;

class gloveAttackTongueState :public gloveState
{
public:

	int frameCount;
	

	virtual gloveState* inputHandle(glove* glove);
	virtual void update(glove* glove);
	virtual void enter(glove* glove);
	virtual void exit(glove* glove);
};
