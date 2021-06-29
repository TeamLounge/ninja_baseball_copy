#pragma once

class bat;

class batState
{
protected:

public:
	virtual batState* inputHandle(bat* bat) = 0;		//'= 0' : 이용했는지 확인용
	virtual void update(bat* bat) = 0;
	virtual void enter(bat* bat) = 0;
	virtual void exit(bat* bat) = 0;

};
