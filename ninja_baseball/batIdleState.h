#pragma once
#include "batState.h"

class bat;

class batIdleState :public batState
{
public:

	int frameCount;
	int timeCount;	//���ʹ� ���� ������ �÷��̾ ������ ���۵Ǵ� ī��Ʈ(�ٷ� �������� �ʰ�, idle ���� ��� �����ϱ� ����)

	virtual batState* inputHandle(bat* bat);
	virtual void update(bat* bat);
	virtual void enter(bat* bat);
	virtual void exit(bat* bat);
};