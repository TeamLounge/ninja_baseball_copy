#pragma once

class glove;

class gloveState
{
protected:


public:
	virtual gloveState* inputHandle(glove* glove) = 0;		//'= 0' : �̿��ߴ��� Ȯ�ο�
	virtual void update(glove* glove) = 0;
	virtual void enter(glove* glove) = 0;
	virtual void exit(glove* glove) = 0;

};
