#pragma once

class blueBaseball;

class bbState
{
protected:

public:
	virtual bbState* inputHandle(blueBaseball* blueBaseball) = 0;		//'= 0' : �̿��ߴ��� Ȯ�ο�
	virtual void update(blueBaseball* blueBaseball) = 0;
	virtual void enter(blueBaseball* blueBaseball) = 0;
	virtual void exit(blueBaseball* blueBaseball) = 0;

};
