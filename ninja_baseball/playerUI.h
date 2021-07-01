#pragma once
#include "gameNode.h"
#include "progressBar.h"
class playerUI : public gameNode
{
private:
	progressBar* _hpBar; //�÷��̾� ü�� ��
	RECT _rc;
	float _x, _y; //ui left, top ��ǥ
	int _maxHP; //�÷��̾� �ִ� ü��
	int _currentHP; //�÷��̾� ���� ü��
	int _playerSelect; //���� ������ ĳ����

	int _life; //�÷��̾� ��� ����

	bool _isAttacked;

	float _elapsedSec;
	float _count;
public:
	HRESULT init(float x, float y, int playerSelect, int maxHP, int currentHP, int life);
	void release();
	void update(float x, float y, int currentHp, int life);
	void render();
};

