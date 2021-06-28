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

	string _faceImgName; // �� �̹��� ��ȯ��
	string _dBackgroundName; //���̾�α� �� ��� ��ȯ��

	int _backgroundHeight; //�� ��� fade in��

	bool _isFirstDialogEnd;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

