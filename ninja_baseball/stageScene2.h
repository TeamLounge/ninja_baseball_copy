#pragma once
#include "gameNode.h"
#include "playerUI.h"
class stageScene2 : public gameNode
{
private:
	vector<string> vText; //텍스트 저장 및 불러오기용 벡터

	string _imageName;
	float _x, _y; //이미지 중점 x, y좌표

	float _distance; //_y와 화면 중심 사이의 거리

	playerUI* _playerUI;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

