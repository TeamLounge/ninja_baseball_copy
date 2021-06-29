#pragma once
#include "gameNode.h"
class startScene : public gameNode
{
private:
	float _elapsedSecForFrame; //������ ������ ����
	float _elapsedSecForText; //�ؽ�Ʈ ��¿�

	vector<string> _dialog; //���̾�α� ����� ����
	int _dialogTextNum[7]; //���̾�α� ��� �󸶳� ����
	int _dialogNow; //���� ��µǰ� �ִ� �ؽ�Ʈ ��

	string _faceImgName; // �� �̹��� ��ȯ��
	string _dBackgroundName; //���̾�α� �� ��� ��ȯ��

	int _backgroundHeight; //�� ��� fade in��

	bool _isFirstDialogEnd; //ù��° ���̾�αװ� ��������
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

