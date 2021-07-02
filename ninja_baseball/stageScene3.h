#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerUI.h"
#include "timerUI.h"
#include "enemyManager.h"
#include "queue"
#include "progressBar.h"
#include "gameOverUI.h"

class gameOverUI;

class stageScene3 : public gameNode
{
private:
	player* _player;

	enemyManager* _em;

	float _elapsedTime;

	vector<string> vText; //�ؽ�Ʈ ���� �� �ҷ������ ����

	playerUI* _playerUI;
	timerUI* _timerUI;

	int _count; //���� ������ ���� �� ������ ī��Ʈ

	queue<float> _cameraStopX; //ī�޶� ���ߴ� ��ǥ ť

	bool _isHaveToSetBoss;

	bool _isSetBoss;

	bool _isStart;

	progressBar* _bossHPBar;
	progressBar* _bossHPBar2;

	gameOverUI* _gameoverUI;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

