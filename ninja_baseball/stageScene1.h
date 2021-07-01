#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "progressBar.h"
#include "playerUI.h"
#include "timerUI.h"

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
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

