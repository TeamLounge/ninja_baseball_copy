#pragma once
#include "gameNode.h"
#include "bossState.h"

//���� ���¸� enum������ ����
//�ϳ��� state�� �ִ´�.. ������?
enum BOSSFORM
{
	DEFAULT,				//�⺻����
	NO_WING,				//�������� ����
	NO_WING_PROP,			//�����緯 ���� ����
	NO_ONE_ARM,				//�� ���� ���� ����
	NO_ARM					//�� ���� ��� ���� ����
};


////////////////////////////
// ####  ���� ����ü #######
////////////////////////////
struct BOSS
{
	RECT rc;
	float x, y;
	image* img;
};

////////////////////////////
// ####  �׸��� ����ü ######
////////////////////////////
struct BOSSSHADOW
{
	RECT rc;
	float x, y;
	image* img;
};


////////////////////////////
// ####  ���� ������ ######
////////////////////////////
struct BOSSPINLIGHT
{
	float x, y;
	image* img;
};

class boss : public gameNode
{
private:

public:
	boss() {};
	~boss() {};

	bossState* _bossState;
	BOSS _boss;
	BOSSSHADOW _bossShadow;
	BOSSFORM _bossForm;
	BOSSPINLIGHT _bossPinLight;

	////////////////////////////////
	// ������ �Ұ�
	//////////////////////////////
	bool _isAttacked;

	//���� ������ Ȯ�ο�
	int _currentFrameX, _currentFrameY;
	//���� �ӵ�
	float _speed;
	//�Ұ� �����
	bool _isLeft, _isUpper;
	//ī��Ʈ��(���º�ȯ)
	int _count, _stateCount;
	//������ ��� �Ұ�
	bool _isPinLight;
	//���� ��
	int _alphaIdx, _alphaCnt;
	bool _isAlpha;
	//���� �ִ��� Ȯ��
	bool _isJump;
	//���� ������ �׸��� y�� ����
	float _jumpShadowY;
	bool _isPreWind;
	//�����ҋ� ��鸲 ������
	bool _isMoveStopRangeX, _isMoveStopRangeY;
	//���Ÿ� ���ݿ� ������Ʈ
	RECT _longRangeAtkRc;
	//���Ÿ� ���� ���ü��ִ� ŷ���Ǽ�
	int _numAtkPattern;
	bool _isLongRangeCrash, _isShootingAttack, _isTrigger;
	bool _isSucceedShootingAttack;
	//�ٰŸ� jab ���� Ʈ����
	bool _isJabAttack; // �̰� ����Ʈ����
	bool _isSucceedJabAttack; // �̰� �Ѱ��� Ʈ����
	bool _isJabState; //��..
	//�ٰŸ� ���� ���°��� ����
	bool _isCrash;
	int _missCount;
	//�ٰŸ� straight ���� Ʈ����
	bool _isStraightAttack;
	bool _isSucceedStraightAttack;
	bool _isStraightState;
	//�ٰŸ� ���� ��õ(������) ����Ʈ����
	bool _isUpperCut;
	bool _isSucceedUpperCut;
	bool _isUpperCutState;
	//�������� ���� �������� Ȯ��
	bool _isDamaged;
	bool _isDamagedState;

	void InputHandle();

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setBoss();
	void setBossShadow();

	//���� ����
	bool getIsUpper() { return _isUpper; }
	bool getIsLeft() { return _isLeft; }
	float getCenterX() { return (_boss.rc.left + _boss.rc.right) / 2; }
	float getCenterY() { return (_boss.rc.top + _boss.rc.bottom) / 2; }


	//���ͼ��� == �ʿ�������� ��;
};

