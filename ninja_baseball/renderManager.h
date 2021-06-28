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
		bool isHaveFrame;
	}OBJ;

	typedef vector<OBJ>						arrObj;
	typedef vector<OBJ>::iterator			iterObj;
	typedef map<string, arrObj>				mapObjList;
	typedef map<string, arrObj>::iterator	mapObjIter;

private:
	mapObjList _mObjList; //오브젝터 맵

	arrObj _arrObj; //오브젝트 정렬용 벡터
public :

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, float* bodyX, float* bodyY, float* shadowX, float* shadowY);

	void addObj(string strKey, const char* bodyImageName, const char* shadowImageName, float* bodyX, float* bodyY, float* shadowX, float* shadowY, int* currentFrameX, int* currentFrameY);

	void deleteObj(string strKey, int i);

	void setObjArray();

	void quickSort(int left, int right);
};

