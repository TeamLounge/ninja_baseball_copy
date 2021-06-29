#pragma once

class blueBaseball;

class bbState
{
protected:

public:
	virtual bbState* inputHandle(blueBaseball* blueBaseball) = 0;		//'= 0' : 이용했는지 확인용
	virtual void update(blueBaseball* blueBaseball) = 0;
	virtual void enter(blueBaseball* blueBaseball) = 0;
	virtual void exit(blueBaseball* blueBaseball) = 0;

};
