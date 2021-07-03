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
	RECT _grip_rc;
	//�̰� �÷��̾��� ��,�� ������ �� ���� bool���� , �������ߴ��� ���ߴ��� �Ǵ��ϱ����ؼ� ���� bool���� , �¾Ҵ��� �ȸ¾Ҵ��� �Ǵ��ϴ� bool ����
	//���ٴϴ��� �ƴ��� �Ǵ��ϴ� bool���� , ��Ѵ��� �� ��Ҵ��� Ȯ���ϴ� bool ����, ���� ������ bool����
	bool isRight, isattack, isdamage;
	bool iscrawl , iscatch ,isfly, isEnd;
	image* _shadow; // �׸����̹���
	bool _isrun ,_run;
	float _runtime;
	//�÷��̾� ������Ʈ ���� Ȯ��
	bool _isGreenAttackState, _isGreenAttack1, _isGreenAttack2, _isGreenAttack3;
	bool _isGreenAttackFrontCombo1, _isGreenAttackFrontCombo2;
	bool _isGreenDashAlt, _isGreenDashAttack;
	bool _isGreenJumpAttack, _isGreenJumpPowerAttack;
	bool _isGreenCatchFrontCombo, _isGreenCatchAttack, _isGreenCatchBackAttack;

	bool _isRedAttackState, _isRedAttack1, _isRedAttack2, _isRedAttack3;
	bool _isRedDownAttack, _isRedDynamiteDance, _isRedCatchAttack, _isCatchAttackSwitch, _isRedHomeRunAttack;
	bool _isRedJumpAttack, _isRedCatch, _isRedGrip, _isRedLegKickAttack, _isRedSliding;
	bool _isRedDashAttack, _isRedCatchAttackOn, _isRedThrow;
	int _catchAttackCnt;


	image* _effect; // �����̹���1
	image* _effect1; // �����̹���2
	image* _effect2; // �����̹���3
	image* _effect3; // �����̹���4

	enemyManager* _em; //�ֳʹ�������������

	//�Լ��� �����Ϸ��� ���⿡��
	//���Ϳ� ���ʹ� ���ε��� �ؿ� �� ���� ���ּ���
	virtual HRESULT init(int character, bool isStart);
	virtual void update();
	virtual void release();
	virtual void render();
	virtual void handleInput(); // ���º�ȯ�޴��Լ�

	virtual void addImage();
	virtual void collision();
	void isStateSet();   //������Ʈ���� Ȯ�� �Ұ� -> ������ Ȯ������ by �豤��

	//������ ����
	virtual image* getImage() { return _playerimg; }
	virtual RECT getRect() { return _playerrc; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual int gethp() { return _hp; }
	virtual int getlife() { return _life; }
	virtual RECT getAtkRect() { return _attack_rc; }
	virtual RECT getGripRect() { return _grip_rc; }

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

	//�׸��� ������ǥ setter, getter
	void setShadowX(float shadowX) { _shadowX = shadowX; }
	void setShadowY(float shadowY) { _shadowY = shadowY; }
	
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
};

