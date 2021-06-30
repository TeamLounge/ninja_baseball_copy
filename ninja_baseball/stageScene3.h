#pragma once
#include "gameNode.h"
#include "player.h"
class stageScene3 : public gameNode
{
private:
	player* _player;

	float _elapsedTime;

	vector<string> vText; //텍스트 저장 및 불러오기용 벡터

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

