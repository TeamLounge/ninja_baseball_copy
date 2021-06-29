#pragma once
#include "batState.h"

class bat;

class batDamagedState :public batState
{
public:

	int frameCount;
	int damageCount;	//��Ʈ�� 3�ܰ� ������ ���� ī��Ʈ
						//�ǰ�(count)  1~2ȸ : ���� x
						//�ǰ�			3ȸ : 1�ܰ� ����<noCap mode>	..���� ���ư�;
						//�ǰ�			4ȸ : 2�ܰ� ����<noBat mode>	..��Ʈ ���ư�;	(���ڶ� ��Ʈ�� ȸ�� ���� �״�� ���ư�����, ī�޶� �� �°� ƨ�� + ���ķ���)
						//�ǰ�			5ȸ : 3�ܰ� ����<death mode>	..����;			(360�� ȸ���ϸ� ���ư��ٰ� ���ķ���)

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};
