#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class renderManager : public singletonBase<renderManager>
{
private:
	typedef struct tagObj
	{
		const char* bodyImageName;
		const char* shadowImageName;
		int *currentFrameX;
		int *currentFrameY;
		float* shadowX;
		float* shadowY;
		float* bodyX;
		float *bodyY;
		bool isNotHaveCurrentFrame;
		bool isFrameImage;
		bool isAlphaBlend;
		int* alpha;
	}OBJ; //������ ��ü ����

	typedef vector<OBJ>						arrObj;
	typedef vector<OBJ>::iterator			iterObj;
	typedef map<string, arrObj>				mapObjList;
	typedef map<string, arrObj>::iterator	mapObjIter;

private:
	mapObjList _mObjList; //�������� ��

	arrObj _arrObj; //������Ʈ ���Ŀ� ����
public :

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//====================������Ʈ �߰�==============================

	//============currentFrameX, currentFrameY�� ���� ���===========
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, bool isFrameImage);
	//���� �ִ� ���
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, bool isFrameImage, int* alphaBlend);
	//==============================================================

	//============currentFrameX, currentFrameY�� �ִ� ���===========
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, int* currentFrameX, int* currentFrameY);
	//���� �ִ� ���
	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, 
		float* bodyX, float* bodyY, float* shadowX, float* shadowY, int* currentFrameX, int* currentFrameY, int* alphaBlend);
	//==============================================================
	//==============================================================

	//Ư�� ������Ʈ ����
	bool deleteObj(string strKey, int i);

	//���� ������Ʈ�� �����ϱ� ���� �� ���Ϳ� ����
	void setObjArray();

	//������Ʈ ����
	void quickSort(int left, int right);

	//��� ������Ʈ ����
	bool deleteAll();
};

