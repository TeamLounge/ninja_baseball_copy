#pragma once
#include "gameNode.h"
#include "timerUI.h"
struct tagCharacterSelect
{
	RECT rc;
	string imageName;
};
class playerSelectScene : public gameNode
{
private:
	RECT _cursor[4]; //Ŀ�� �̹��� �̵��� ��Ʈ
	int _currentSelect; //���� ������ ĳ����

	float _elapsedSec;

	float _characterFrameSec;
	
	bool _isSelect; //�����ߴ��� Ȯ��

	tagCharacterSelect _character[4]; //ĳ���� �̹��� ��Ʈ

	timerUI* _timerUI;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

