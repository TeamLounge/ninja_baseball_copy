#pragma once
#include "gameNode.h"
class playerSelectScene : public gameNode
{
private:
	RECT _curser; //Ŀ�� �̹��� �̵��� ��Ʈ
	int _currentSelect; //���� ������ ĳ����

	RECT _character[4]; //ĳ���� �̹��� ��Ʈ
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

