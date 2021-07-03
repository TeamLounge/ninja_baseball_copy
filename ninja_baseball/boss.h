#pragma once
#include "gameNode.h"
#include "bossState.h"

//보스 형태를 enum문으로 만들어서
//하나의 state에 넣는다.. 좋은데?
enum BOSSFORM
{
	DEFAULT,				//기본상태
	NO_WING,				//날개없는 상태
	NO_WING_PROP,			//프로펠러 없는 상태
	NO_ONE_ARM,				//팔 한쪽 없는 상태
	NO_ARM					//팔 두쪽 모두 없는 상태
};


////////////////////////////
// ####  보스 구조체 #######
////////////////////////////
struct BOSS
{
	RECT rc;
	float x, y;
	image* img;
};

////////////////////////////
// ####  그림차 구조체 ######
////////////////////////////
struct BOSSSHADOW
{
	RECT rc;
	float x, y;
	image* img;
};


////////////////////////////
// ####  보스 핀조명 ######
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
	// 연습용 불값
	//////////////////////////////
	bool _isAttacked;
	///////////////////////////////

	/////////////////////////////
	//    ## 피격용 렉트 ##     //
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

	//현재 프레임 확인용
	int _currentFrameX, _currentFrameY;
	//무브 속도
	float _speed;
	//불값 적용들
	bool _isLeft, _isUpper;
	//카운트용(형태변환)
	int _count, _stateCount;
	//핀조명 사용 불값
	bool _isPinLight;
	//알파 값
	int _alphaIdx, _alphaCnt;
	bool _isAlpha;
	//날고 있는지 확인
	bool _isJump;
	//점프 했을때 그림자 y값 저장
	float _jumpShadowY;
	bool _isPreWind;
	//무브할떄 흔들림 방지용
	bool _isMoveStopRangeX, _isMoveStopRangeY;
	//원거리 공격용 감지렉트
	RECT _longRangeAtkRc;
	//원거리 공격 나올수있는 킹우의수
	int _numAtkPattern;
	bool _isLongRangeCrash, _isShootingAttack, _isTrigger;
	bool _isSucceedShootingAttack;
	//근거리 jab 공격 트리거
	bool _isJabAttack; // 이게 공격트리거
	bool _isSucceedJabAttack; // 이게 넘겨줄 트리거
	bool _isJabState; //하..
	//근거리 공격 들어온것을 감지
	bool _isCrash;
	int _missCount;
	//근거리 straight 공격 트리거
	bool _isStraightAttack;
	bool _isSucceedStraightAttack;
	bool _isStraightState;
	//근거리 용의 승천(어퍼컷) 공격트리거
	bool _isUpperCut;
	bool _isSucceedUpperCut;
	bool _isUpperCutState;
	//데미지가 들어온 상태인지 확인
	bool _isDamaged;
	bool _isDamagedState;
	bool _isSmallDamaged;
	//현재 무브상태인지 확인
	bool _isMoveState;
	//현재 무슨상태인지 확인
	bool _isIdleState, _isShootingState, _isDeathState, _isSmallDamagedState;
	bool _isWindState;
	int _windCnt;
	float _windPower, _windInerita;
	string _imageName;
	string _shadowName;
	//렌더 위치잡이용
	float _imageX, _imageY;
	//형태 불값
	bool _isNoWing, _isNoWingProp, _isNoOneArm, _isNoArm;
	float _divideX, _divideY, _divideGravity;

	//그린 불값
	bool _isGreenAttack12, _isGreenAttack3;   //그린어택 1,2,3 들어왔을때 불값
	bool _isGreenCatch, _isGreenCatchAttack, _isGreenCatchBackAttack, _isGreenCatchFrontCombo;
	bool _isGreenCatchAttackPre;

	//레드 공격 불값
	bool _isRedAttack1, _isRedAttack2, _isRedAttack3; //레드 기본어택
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

	//게터 설정
	bool getIsUpper() { return _isUpper; }
	bool getIsLeft() { return _isLeft; }
	float getCenterX() { return (_boss.rc.left + _boss.rc.right) / 2; }
	float getCenterY() { return (_boss.rc.top + _boss.rc.bottom) / 2; }

	int getCurrentHP() { return _currentHp; }
	int getMaxHP() { return _maxHp; }

	//세터설정 == 필요없긴하지 ㅎ;
	void setImageName(string imgName) { _imageName = imgName; }
};

