#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerUI.h"
#include "timerUI.h"

class stageScene3 : public gameNode
{
private:
	player* _player;

	float _elapsedTime;

	vector<string> vText; //�ؽ�Ʈ ���� �� �ҷ������ ����

	playerUI* _playerUI;
	timerUI* _timerUI;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

