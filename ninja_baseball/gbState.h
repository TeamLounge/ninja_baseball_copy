#pragma once

class greenBaseball;

class gbState
{
protected:


public:
	virtual gbState* inputHandle(greenBaseball* greenBaseball) = 0;		//'= 0' : 이용했는지 확인용
	virtual void update(greenBaseball* greenBaseball) = 0;
	virtual void enter(greenBaseball* greenBaseball) = 0;
	virtual void exit(greenBaseball* greenBaseball) = 0;

};
