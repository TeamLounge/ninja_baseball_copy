#pragma once
#include "gameNode.h"
#include "playerstate.h"

class playerstate; //�̰��� ��������..

class player : public gameNode
{
private:
	//�⺻���� ��� �ٸ��� �ʿ��ϴٸ� �߰����ּŵ��˴ϴ�
	//===================================
	image* _playerimg; //�̹���
	RECT _playerrc; // ��Ʈ
	float _x, _y; // ��ǥ
	playerstate* _state; // �������� ����
	//==================================
	//�߰��׸���� �ؿ� �߰����ּ��� �ּ��� �޾��ֽô°� ���� �����ּ���


public:
	//public������ �ٸ� Ŭ�����ʿ��� �� �����ص� �Ǵ°ɷ� ���ּ��� get,set���� �������ϱ� ��
	//�̰� �÷��̾��� ��,�� ������ �� ���� bool���� 
	bool isRight;
	image* _shadow; // �׸����̹���

	//�Լ��� �����Ϸ��� ���⿡��
	//���Ϳ� ���ʹ� ���ε��� �ؿ� �� ���� ���ּ���
	virtual HRESULT init(int character);
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void handleInput(); // ���º�ȯ�޴��Լ�

	virtual void addImage();
	//������ ����
	virtual image* getImage() { return _playerimg; }
	virtual RECT getRect() { return _playerrc; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }


	//������ ����
	virtual void setImage(image* img) { _playerimg = img; }
	virtual void setRect(RECT rc) { _playerrc = rc; }
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }

};

