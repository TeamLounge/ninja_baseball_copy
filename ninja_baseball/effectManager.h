#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//생산
	typedef vector<effect*>								arrEffects;
	typedef vector<effect*>::iterator					iterEffects;
	//가공
	typedef map<string, arrEffects>						arrEffect;
	typedef map<string, arrEffects>::iterator			iterEffect;
	//포장
	typedef vector<map<string, arrEffects>>				arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator	iterTotalEffect;

private:
	arrTotalEffect _vTotalEffect;
	int _count;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void update(float x, float y);
	void update(string effectName, float x, float y);
	void render();

	void addEffect(string effectName, const char* imageName, int imageWidth,
		int imageHeight, int effectWidth, int effectHeight, int fps, float elapsed, int buffer);

	void play(string effectName, int x, int y);
	void play(string effectName, int x, int y, int count);
	void stop(string effectName);
};

