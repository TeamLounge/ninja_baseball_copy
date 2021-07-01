#pragma once
#include "gameNode.h"
#include "cardState.h"
#include <vector>

/////////////////////////////
//     ī�� ����ü
////////////////////////////
struct CARD
{
	RECT rc;
	float x, y;
	image* img;
};

/////////////////////////
//    �׸��� ����ü
/////////////////////////
struct CARDSHADOW
{
	RECT rc;
	float x, y;
	image* img;
};


/////////////////////////
//    �Ѿ� ����ü
/////////////////////////
struct tagPunchBullet
{
	RECT rc;
	float x, y;
	float fireX, fireY;
	image* img;
	bool isFire;
	float speed;
	float angle;
	float range;
	int count;
	int currentFrameX, currentFrameY;
};

class card : public gameNode
{
private:
	
public:
	vector<tagPunchBullet>				 _vPunchBullet;
	vector<tagPunchBullet>::iterator	 _viPunchBullet;
	cardState* _cardState;
	CARDSHADOW _cardShadow;
	CARD _card;

	void InputHandle();

	/////////////////////////////
	//    ## �ǰݿ� ��Ʈ ##     //
	////////////////////////////
	RECT _assultedRect;

	string _imageName;

	//�߷�
	float _gravity, _jumpPower;
	//���� �ӵ�
	float _speed;
	//����������, ���ݹ޾Ҵ���, ���������� ��� �Ұ� �����
	bool _isJump, _isLeft, _isDamaged, _isUpper, _isApex;
	//���� ��Ҵ��� Ȯ��
	bool _isRightWall, _isLeftWall, _isTopWall, _isBottomWall;
	//Dash �������� �ָԹ߻� �������� Ȯ�ο�
	bool _isDash, _isPunchBullet;
	//�÷��̾��� ���� X�� ����Y�� �޾ƿ����� �������.
	float _rpX, _rpY;
	//��ġ �淿 �������� �������� 1�� �Դ��� Ȯ���ϰ� �Ѿ��� �߻��ϱ� ���� ���
	bool _isFire;
	//���ݿ� ��Ʈ
	RECT _atkRc;
	//���� ������ ��ȣ ����(������Ʈ)
	int _currentFrameX, _currentFrameY;
	//���� ������ ��ȣ ����(�Ѿ�)
	int _bulletFrameX, _bulletFrameY;
	//�Ѿ� ��� ������ ī��Ʈ�ϴ°�
	int _bulletCount;
	int _bulletMax;
	float _range;
	//���������� �ֱ����� �۾�
	int numPattern;
	bool _isCrash;
	//���� ���� boo�� �ֱ�
	bool _isCardSmallDamagedState, _isCardSmallDamaged;
	bool _isCardHeavyDamagedState, _isCardHeavyDamaged;
	bool _isCardDeathState, _isCardDeath;



	bool isattack;              //���ʹ̰� �����߾�??
	bool isdamage;				//���ʹ̰� ������ �޾Ҿ�??							
	bool iscatch;				//�����̰� ������??

	card();
	~card();

	virtual HRESULT init();	
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();	

	void setImage();
	void setCard();
	void setCardShadow();
	void getGravity();

	////////////////////////////
	//   �Ѿ� �߻� �Լ�
	///////////////////////////
	void setBullet(int bulletMax, float range);
	void updateBullet();
	void renderBullet();
	void fireBullet(float x, float y, float angle);
	void moveBullet();

	//���� �Լ�
	void setIsUpper(bool isUpper) { _isUpper = isUpper; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsDash(bool isDash) { _isDash = isDash; }
	void setIsBullet(bool isPunchBullet) { _isPunchBullet = isPunchBullet; }
	void setIsDamaged(bool isDamaged) { _isDamaged = isDamaged; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	void setIsFire(bool isFire) { _isFire = isFire; }

	//���� ����
	RECT getCardRc() { return _card.rc; }
	RECT getAtkCardRc() { return _atkRc; }
	float getCenterX() { return (_card.rc.left + _card.rc.right) / 2; }
	float getCenterY() { return (_card.rc.top + _card.rc.bottom) / 2; }
	bool getIsUpper() { return _isUpper; }
	bool getIsLeft() { return _isLeft; }
	bool getIsDash() { return _isDash; }
	bool getIsBullet() { return _isPunchBullet; }
	bool getIsFire() { return _isFire; }
};