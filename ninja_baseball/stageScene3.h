#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerUI.h"
#include "timerUI.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "queue"
#include "progressBar.h"
#include "gameOverUI.h"
class stageScene3 : public gameNode
{
private:
	player* _player;

	enemyManager* _em;
	objectManager* _obj;

	float _elapsedTime;

	vector<string> vText; //텍스트 저장 및 불러오기용 벡터

	playerUI* _playerUI;
	timerUI* _timerUI;

	int _count; //보스 죽으면 엔딩 씬 전까지 카운트

	queue<float> _cameraStopX; //카메라 멈추는 좌표 큐

	bool _isHaveToSetBoss;

	bool _isSetBoss;

	bool _isStart;

	progressBar* _bossHPBar;
	progressBar* _bossHPBar2;

	string _bossHpBarImgAddress;

	gameOverUI* _gameoverUI;
	goldbat* _goldbat;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

