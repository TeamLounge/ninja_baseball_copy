#pragma once

class yellowBaseball;

class ybState

{
protected:


public:
	virtual ybState* inputHandle(yellowBaseball* yellowBaseball) = 0;
	virtual void update(yellowBaseball* yellowBaseball) = 0;
	virtual void enter(yellowBaseball* yellowBaseball) = 0;
	virtual void exit(yellowBaseball* yellowBaseball) = 0;


};
