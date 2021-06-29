#pragma once

class glove;

class gloveState
{
protected:


public:
	virtual gloveState* inputHandle(glove* glove) = 0;		//'= 0' : 이용했는지 확인용
	virtual void update(glove* glove) = 0;
	virtual void enter(glove* glove) = 0;
	virtual void exit(glove* glove) = 0;

};
