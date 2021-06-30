#pragma once
#include "batState.h"

class bat;

class batDeathState :public batState
{
public:

	int frameCount;

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};
