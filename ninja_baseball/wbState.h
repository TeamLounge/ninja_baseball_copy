#pragma once

class whiteBaseball;

class wbState
{
protected:
	int _currentFrameX;
	int _currentFrameY;

public:
	virtual wbState* inputHandle(whiteBaseball* whiteBaseball) = 0;		//'= 0' : �̿��ߴ��� Ȯ�ο�
	virtual void update(whiteBaseball* whiteBaseball) = 0;
	virtual void enter(whiteBaseball* whiteBaseball) = 0;
	virtual void exit(whiteBaseball* whiteBaseball) = 0;

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }
};
