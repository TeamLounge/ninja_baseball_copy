#pragma once
#include "gameNode.h"
class startScene : public gameNode
{
private:
	float _elapsedSecForFrame; //������ ������ ����
	float _elapsedSecForText; //�ؽ�Ʈ ��¿�

	vector<string> _dialog;
	int _dialogTextNum[7];
	int _dialogNow;

	bool _isFirstDialogEnd;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

