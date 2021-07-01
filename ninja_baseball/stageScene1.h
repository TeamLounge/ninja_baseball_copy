#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "progressBar.h"
#include "playerUI.h"
#include "timerUI.h"

struct tagXY
{
	float x, y;
};

class stageScene1 : public gameNode
{


private:
	player* _player;

	int _playerSelect; //현재 선택된 플레이어 저장
	vector<string> vText; //텍스트로부터 받아온 데이터 저장 및 텍스트로 나가도록 하는 벡터 

	enemyManager* _em;
	objectManager* _obj;

	playerUI* _playerUI;
	
	timerUI* _timerUI;

	float _angle; //셔터 각도

	vector<tagXY> _guide;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void shutterCollison();
};

