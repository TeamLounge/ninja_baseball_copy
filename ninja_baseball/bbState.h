#pragma once

class blueBaseball;

class bbState
{
protected:
	int _currentFrameX;
	int _currentFrameY;

public:
	virtual bbState* inputHandle(blueBaseball* blueBaseball) = 0;		//'= 0' : �̿��ߴ��� Ȯ�ο�
	virtual void update(blueBaseball* blueBaseball) = 0;
	virtual void enter(blueBaseball* blueBaseball) = 0;
	virtual void exit(blueBaseball* blueBaseball) = 0;

	int getCurrentFrameX() { return _currentFrameX; }
	int getCurrentFrameY() { return _currentFrameY; }
};
