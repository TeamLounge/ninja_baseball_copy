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

	//셔터
	RECT rc; //타격 범위 rc
	bool _isCrush;
	vector<string> _sutterParticle;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//셔터 픽셀충돌
	void shutterCollison();

	void setImage();

	void setShutter();
};

