#pragma once

class whiteBaseball;

class wbState
{
protected:
	

public:
	virtual wbState* inputHandle(whiteBaseball* whiteBaseball) = 0;		//'= 0' : �̿��ߴ��� Ȯ�ο�
	virtual void update(whiteBaseball* whiteBaseball) = 0;
	virtual void enter(whiteBaseball* whiteBaseball) = 0;
	virtual void exit(whiteBaseball* whiteBaseball) = 0;
	
};
