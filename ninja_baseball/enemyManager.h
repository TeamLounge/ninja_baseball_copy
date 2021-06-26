#pragma once

#include "gameNode.h"
#include "whiteBaseball.h"
#include <vector>

class red;

class enemyManager : public gameNode
{
private:
	typedef vector<whiteBaseball*>				vWhiteBaseball;
	typedef vector<whiteBaseball*>::iterator	viWhiteBaseball;

private:
	vWhiteBaseball  _vWb;
	viWhiteBaseball _viWb;


	red* _red;
	
public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	vector<whiteBaseball*> getVWb() { return _vWb; }
	vector<whiteBaseball*>::iterator getVIWb() { return _viWb; }

	void setRedMemoryAddressLink(red* red) { _red = red; }

	void setWB();
	void updateWB();
	void renderWB();

	void playerLocation();

	void collision();
};

