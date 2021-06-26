#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* Bulletimg;	//�Ѿ� �̹���
	RECT rc;			//�Ѿ� ��Ʈ
	float x, y;			//�Ѿ� ��ǥ(�ǽð�)
	float angle;		//�Ѿ� ����
	float speed;		//�Ѿ� ���ǵ�
	float fireX, fireY;	//�Ѿ� �߻� ��ǥ
	bool isFire;		//�߻� ����
};

class punchBullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;		//�̹��� �ҷ��� �̸�
	float _range;				//��Ÿ�
	int _bulletMax;				//�Ѿ� �ִ밹��

public:
	punchBullet() {};
	~punchBullet() {};
	
	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed);

	void move();
};

