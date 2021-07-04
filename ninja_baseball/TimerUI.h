#pragma once
#include "gameNode.h"
class timerUI : public gameNode
{
private:
	int _time; //ó�� Ÿ�̸� �ð�
	int _timeStandard; //Ÿ�̸Ӱ� 1�� �������� ���� �ð�
	float _worldTime;
	float _x, _y;
public :
	HRESULT init(int time, int time_standard, float x, float y); //��ü �ð��� Ÿ�̸Ӱ� ���ʸ��� ��������,  Ÿ�̸� ������ǥ
	void release();
	void update(float x, float y);
	void render();

	int getTime() { return _time; }
	void setTime(int time) { _time = time; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
};

