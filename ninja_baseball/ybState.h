#pragma once

class yellowBaseball;

class ybState

{
protected:
	int _currentFrameX;
	int _currentFrameY;

public:
	virtual ybState* inputHandle(yellowBaseball* yellowBaseball) = 0;
	virtual void update(yellowBaseball* yellowBaseball) = 0;
	virtual void enter(yellowBaseball* yellowBaseball) = 0;
	virtual void exit(yellowBaseball* yellowBaseball) = 0;

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }
};
