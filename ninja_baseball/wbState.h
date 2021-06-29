#pragma once

class whiteBaseball;

class wbState
{
protected:
	

public:
	virtual wbState* inputHandle(whiteBaseball* whiteBaseball) = 0;		//'= 0' : 이용했는지 확인용
	virtual void update(whiteBaseball* whiteBaseball) = 0;
	virtual void enter(whiteBaseball* whiteBaseball) = 0;
	virtual void exit(whiteBaseball* whiteBaseball) = 0;
	
};
