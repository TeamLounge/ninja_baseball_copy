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

	string _bossHpBarImgAddress;

	gameOverUI* _gameoverUI;
	goldbat* _goldbat;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

