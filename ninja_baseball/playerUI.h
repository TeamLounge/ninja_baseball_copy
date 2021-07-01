#pragma once
#include "gameNode.h"
#include "progressBar.h"
class playerUI : public gameNode
{
private:
	progressBar* _hpBar; //플레이어 체력 바
	RECT _rc;
	float _x, _y; //ui left, top 좌표
	int _maxHP; //플레이어 최대 체력
	int _currentHP; //플레이어 현재 체력
	int _playerSelect; //현재 선택한 캐릭터

	int _life; //플레이어 목숨 개수

	bool _isAttacked;

	float _elapsedSec;
	float _count;
public:
	HRESULT init(float x, float y, int playerSelect, int maxHP, int currentHP, int life);
	void release();
	void update(float x, float y, int currentHp, int life);
	void render();
};

