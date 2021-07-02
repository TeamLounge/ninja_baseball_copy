#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerUI.h"
#include "timerUI.h"
#include "enemyManager.h"
#include "queue"

class stageScene3 : public gameNode
{
private:
	player* _player;

	enemyManager* _em;

	float _elapsedTime;

	vector<string> vText; //�ؽ�Ʈ ���� �� �ҷ������ ����

	playerUI* _playerUI;
	timerUI* _timerUI;

	queue<float> _cameraStopX;

	bool _isHaveToSetBoss;

	bool _isSetBoss;

	bool _isStart;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

