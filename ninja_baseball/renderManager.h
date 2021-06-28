#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class renderManager : public singletonBase<imageManager>
{
private:
	typedef struct tagObj
	{
		string bodyImageName;
		string shadowImageName;
		RECT body; //본체
		RECT shadow; //그림자
		int currentFrameX, currentFrameY;
		float shadowX, shadowY;
		bool isHaveRect;
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

	void addObj(string strKey, string bodyImageName, string shadowImageName);

	void addObj(string strKey, string bodyImageName, string shadowImageName, RECT& body, RECT& shadow, int& currentFrameX, int& currentFrameY);

	void deleteObj(string strKey, int i);

	void setObjArray();

	void quickSort(int left, int right);
};

