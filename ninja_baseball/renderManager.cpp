#include "stdafx.h"
#include "renderManager.h"

HRESULT renderManager::init()
{
	return S_OK;
}

void renderManager::release()
{
}

void renderManager::update()
{
	setObjArray();
	quickSort(0, _arrObj.size() - 1);
}

void renderManager::render(HDC hdc)
{
	for (int i = 0; i < _arrObj.size(); i++)
	{
		if (_arrObj[i].isNotHaveCurrentFrame)
		{
			if (_arrObj[i].isAlphaBlend)
			{
				IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->render(hdc,
					*_arrObj[i].shadowX - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getWidth() / 2),
					*_arrObj[i].shadowY - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getHeight() / 2));
				if (_arrObj[i].isFrameImage)
				{
					IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->alphaFrameRender(hdc, *_arrObj[i].bodyX - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getFrameWidth() / 2),
						*_arrObj[i].bodyY - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getFrameHeight() / 2), *_arrObj[i].alpha);
				}
				else
				{
					IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->alphaRender(hdc, *_arrObj[i].bodyX - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getWidth() / 2),
						*_arrObj[i].bodyY - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getHeight() / 2), *_arrObj[i].alpha);
				}
			}
			else
			{
				IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->render(hdc,
					*_arrObj[i].shadowX - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getWidth() / 2),
					*_arrObj[i].shadowY - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getHeight() / 2));

				if (_arrObj[i].isFrameImage)
				{
					IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->frameRender(hdc, *_arrObj[i].bodyX - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getFrameWidth() / 2),
						*_arrObj[i].bodyY - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getFrameHeight() / 2));
				}
				else
				{
					IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->render(hdc, *_arrObj[i].bodyX - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getWidth() / 2),
						*_arrObj[i].bodyY - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getHeight() / 2));
				}
			}
		}
		else
		{
			if (_arrObj[i].isAlphaBlend)
			{
				IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->render(hdc,
					*_arrObj[i].shadowX - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getWidth() / 2),
					*_arrObj[i].shadowY - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getHeight() / 2));
				IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->alphaFrameRender(hdc, *_arrObj[i].bodyX - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getFrameWidth() / 2),
					*_arrObj[i].bodyY - (IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->getFrameHeight() / 2), *_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY, *_arrObj[i].alpha);

			}
			else
			{
				if (strcmp(_arrObj[i].shadowImageName, ""))
				{
					IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->render(hdc,
						*_arrObj[i].shadowX - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getWidth() / 2),
						*_arrObj[i].shadowY - (IMAGEMANAGER->findImage(_arrObj[i].shadowImageName)->getHeight() / 2));

				}
				IMAGEMANAGER->findImage(_arrObj[i].bodyImageName)->frameRender(hdc,
					*_arrObj[i].bodyX,
					*_arrObj[i].bodyY, *_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
			}
			
		}
	}
}

void renderManager::addObj(string strKey, const char* bodyImageName, const char* shadowImageName, float* bodyX, float* bodyY, float* shadowX, float* shadowY, bool isFrameImage)
{
	OBJ object;
	object.bodyImageName = bodyImageName;
	object.shadowImageName = shadowImageName;
	object.bodyX = bodyX;
	object.bodyY = bodyY;
	object.shadowX = shadowX;
	object.shadowY = shadowY;
	object.isNotHaveCurrentFrame = true;
	object.isFrameImage = isFrameImage;
	object.isAlphaBlend = false;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));
}

void renderManager::addObj(string strKey, const char * bodyImageName, const char * shadowImageName, float * bodyX, float * bodyY, float * shadowX, float * shadowY, bool isFrameImage, int * alphaBlend)
{
	OBJ object;
	object.bodyImageName = bodyImageName;
	object.shadowImageName = shadowImageName;
	object.bodyX = bodyX;
	object.bodyY = bodyY;
	object.shadowX = shadowX;
	object.shadowY = shadowY;
	object.isNotHaveCurrentFrame = true;
	object.isFrameImage = isFrameImage;
	object.isAlphaBlend = true;
	object.alpha = alphaBlend;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));
}

void renderManager::addObj(string strKey, const char* bodyImageName, const char* shadowImageName, float* bodyX, float* bodyY, float* shadowX, float* shadowY, int* currentFrameX, int* currentFrameY)
{
	OBJ object;
	object.bodyImageName = bodyImageName;
	object.shadowImageName = shadowImageName;
	object.bodyX = bodyX;
	object.bodyY = bodyY;
	object.shadowX = shadowX;
	object.shadowY = shadowY;
	object.currentFrameX = currentFrameX;
	object.currentFrameY = currentFrameY;
	object.isNotHaveCurrentFrame = false;
	object.isFrameImage = true;
	object.isAlphaBlend = false;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));

}

void renderManager::addObj(string strKey, const char * bodyImageName, const char * shadowImageName, float * bodyX, float * bodyY, float * shadowX, float * shadowY, int * currentFrameX, int * currentFrameY, int * alphaBlend)
{
	OBJ object;
	object.bodyImageName = bodyImageName;
	object.shadowImageName = shadowImageName;
	object.bodyX = bodyX;
	object.bodyY = bodyY;
	object.shadowX = shadowX;
	object.shadowY = shadowY;
	object.currentFrameX = currentFrameX;
	object.currentFrameY = currentFrameY;
	object.isNotHaveCurrentFrame = false;
	object.isFrameImage = true;
	object.isAlphaBlend = true;
	object.alpha = alphaBlend;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));
}

bool renderManager::deleteObj(string strKey, int i)
{

	mapObjIter key = _mObjList.find(strKey);

	if (key != _mObjList.end())
	{
		key->second.erase(key->second.begin() + i);
		if (key->second.empty())
		{
			_mObjList.erase(key);
		}
		return true;
	}

	return false;
}

void renderManager::setObjArray()
{
	if (!_arrObj.empty())
	{
		_arrObj.clear();
	}
	for (mapObjIter mIter = _mObjList.begin(); mIter != _mObjList.end(); mIter++)
	{
		for (iterObj vIter = mIter->second.begin(); vIter != mIter->second.end(); vIter++)
		{
			_arrObj.push_back(*vIter);
		}
	}
}

void renderManager::quickSort(int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int pivot = left;
	int i = left + 1;
	int j = right;
	OBJ temp;

	while (i <= j)
	{
		while (i <= right && *_arrObj[i].shadowY <= *_arrObj[pivot].shadowY) i++;
		while (j > left && *_arrObj[j].shadowY >= *_arrObj[pivot].shadowY) j--;

		if (i > j)
		{
			temp = _arrObj[pivot];
			_arrObj[pivot] = _arrObj[j];
			_arrObj[j] = temp;
		}
		else
		{
			temp = _arrObj[j];
			_arrObj[j] = _arrObj[i];
			_arrObj[i] = temp;
		}
	}
	quickSort(left, j - 1);
	quickSort(j + 1, right);
}

bool renderManager::deleteAll()
{
	mapObjIter iter = _mObjList.begin();

	for (; iter != _mObjList.end();)
	{
		if (!iter->second.empty())
		{
			iter->second.clear();
		}
		else ++iter;
	}

	_mObjList.clear();

	return false;
}


