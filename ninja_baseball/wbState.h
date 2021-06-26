#pragma once

class whiteBaseball;

class wbState
{
protected:
	int _currentFrameX;
	int _currentFrameY;

public:
	virtual wbState* inputHandle(whiteBaseball* whiteBaseball) = 0;		//'= 0' : 이용했는지 확인용
	virtual void update(whiteBaseball* whiteBaseball) = 0;
	virtual void enter(whiteBaseball* whiteBaseball) = 0;
	virtual void exit(whiteBaseball* whiteBaseball) = 0;

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }
};
