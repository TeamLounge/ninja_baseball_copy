#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
class stageScene1 : public gameNode
{
private:
	player* _player;

	int _playerSelect; //���� ���õ� �÷��̾� ����
	vector<string> vText; //�ؽ�Ʈ�κ��� �޾ƿ� ������ ���� �� �ؽ�Ʈ�� �������� �ϴ� ���� 

	enemyManager* _em;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

