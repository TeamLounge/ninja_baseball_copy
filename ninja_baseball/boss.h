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
	int _maxHp;
	int _currentHp;

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
	///////////////////////////////

	/////////////////////////////
	//    ## �ǰݿ� ��Ʈ ##     //
	////////////////////////////
	RECT _assultedRect;
	

	image* _isLeft_RightNoWing;
	image* _isLeft_LeftNoWing;
	image* _isRight_RightNoWing;
	image* _isRight_LeftNoWing;
	image* _isLeft_NoWingProp;
	image* _isRight_NoWingProp;
	image* _isLeft_RightArm;
	image* _isLeft_LeftArm;
	image* _isRight_LeftArm;
	image* _isRight_RightArm;

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
	bool _isSmallDamaged;
	//���� ����������� Ȯ��
	bool _isMoveState;
	//���� ������������ Ȯ��
	bool _isIdleState, _isShootingState, _isDeathState, _isSmallDamagedState;
	bool _isWindState;
	int _windCnt;
	float _windPower, _windInerita;
	string _imageName;
	string _shadowName;
	//���� ��ġ���̿�
	float _imageX, _imageY;
	//���� �Ұ�
	bool _isNoWing, _isNoWingProp, _isNoOneArm, _isNoArm;
	float _divideX, _divideY, _divideGravity;

	//�׸� �Ұ�
	bool _isGreenAttack12, _isGreenAttack3;   //�׸����� 1,2,3 �������� �Ұ�
	bool _isGreenCatch, _isGreenCatchAttack, _isGreenCatchBackAttack, _isGreenCatchFrontCombo;
	bool _isGreenCatchAttackPre;

	//���� ���� �Ұ�
	bool _isRedAttack1, _isRedAttack2, _isRedAttack3; //���� �⺻����
	bool _isRedDownAttack, _isRedDynamiteDance, _isRedCatchAttack, _isRedHomeRunAttack;
	bool _isRedJumpAttack, _isRedCatch, _isRedGrip, _isRedLegKickAttack, isRedSliding;
	bool _isRedDynamiteOn, _isRedCatchAttackPre, _isRedThrow;




	void InputHandle();

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
	void setBoss();
	void setBossShadow();
	void renderAdjust();
	void smokeEffect();
	void imgLocation();
	void pinRender();

	//���� ����
	bool getIsUpper() { return _isUpper; }
	bool getIsLeft() { return _isLeft; }
	float getCenterX() { return (_boss.rc.left + _boss.rc.right) / 2; }
	float getCenterY() { return (_boss.rc.top + _boss.rc.bottom) / 2; }

	int getCurrentHP() { return _currentHp; }
	int getMaxHP() { return _maxHp; }

	//���ͼ��� == �ʿ�������� ��;
	void setImageName(string imgName) { _imageName = imgName; }
};

