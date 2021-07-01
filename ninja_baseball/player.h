#pragma once
#include "gameNode.h"
#include "playerstate.h"

#include "enemyManager.h"
class playerstate; //�̰��� ��������..

//class enemyManager; //enemy��� �浹 ���� ���漱��(��ȣ������)

class player : public gameNode
{
private:
	//�⺻���� ��� �ٸ��� �ʿ��ϴٸ� �߰����ּŵ��˴ϴ�
	//===================================
	image* _playerimg; //�̹���
	string _playerImgName;

	RECT _playerrc; // ��Ʈ
	float _x, _y; // ��ǥ
	float _shadowX, _shadowY;
	playerstate* _state; // �������� ����

	//==================================
	//�߰��׸���� �ؿ� �߰����ּ��� �ּ��� �޾��ֽô°� ���� �����ּ���
	int _character; // ĳ���� ���к��� 1�̸� captin 2 Ryno
	int _life , _hp;  // ����� hp

	//enemyManager* _em; //�ֳʹ�������������
public:
	//public������ �ٸ� Ŭ�����ʿ��� �� �����ص� �Ǵ°ɷ� ���ּ��� get,set���� �������ϱ� ��
	//�� ��Ʈ�� player�� �������̴� �ϸ� ����Ŭ���������� ���� ��Ʈ�� �̸� �����صδ°̴ϴ�.
	RECT _attack_rc;
	//�̰� �÷��̾��� ��,�� ������ �� ���� bool���� , �������ߴ��� ���ߴ��� �Ǵ��ϱ����ؼ� ���� bool���� , �¾Ҵ��� �ȸ¾Ҵ��� �Ǵ��ϴ� bool ����
	//���ٴϴ��� �ƴ��� �Ǵ��ϴ� bool���� , ��Ѵ��� �� ��Ҵ��� Ȯ���ϴ� bool ����, ���� ������ bool����
	bool isRight, isattack, isdamage;
	bool iscrawl , iscatch ,isfly;
	image* _shadow; // �׸����̹���
	bool _isrun ,_run;
	float _runtime;
	image* _effect;
	image* _effect1;
	image* _effect2;
	image* _effect3;
	enemyManager* _em; //�ֳʹ�������������

	//�Լ��� �����Ϸ��� ���⿡��
	//���Ϳ� ���ʹ� ���ε��� �ؿ� �� ���� ���ּ���
	virtual HRESULT init(int character);
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void handleInput(); // ���º�ȯ�޴��Լ�

	virtual void addImage();
	virtual void collision();

	//������ ����
	virtual image* getImage() { return _playerimg; }
	virtual RECT getRect() { return _playerrc; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual int gethp() { return _hp; }
	virtual int getlife() { return _life; }

	//������ ����
	virtual void setImage(image* img) { _playerimg = img; }

	virtual void setRect(RECT rc) { _playerrc = rc; }
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }

	virtual void setImageName(string s) { _playerImgName = s; }

	virtual void sethp(int hp) { _hp = hp; }
	virtual void setlife(int life) { _life  = life; }

	//���ʹ̸Ŵ����� ��ũ
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	void setShadowX(float shadowX) { _shadowX = shadowX; }
	void setShadowY(float shadowY) { _shadowY = shadowY; }
};

