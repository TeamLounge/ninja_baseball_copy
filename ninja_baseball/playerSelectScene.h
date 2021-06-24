#pragma once
#include "gameNode.h"
struct tagCharaterSelect
{
	RECT rc;
	string imageName;
};
class playerSelectScene : public gameNode
{
private:
	RECT _cursor[4]; //Ŀ�� �̹��� �̵��� ��Ʈ
	int _currentSelect; //���� ������ ĳ����

	tagCharaterSelect _character[4]; //ĳ���� �̹��� ��Ʈ
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

