#pragma once
#include "singletonBase.h"
#include <ctime>

class randomFunction : public singletonBase<randomFunction>
{
public:
	//GetTickCount() : OS가 부팅된 이후의 경과 시간을 리턴
	randomFunction() { srand(GetTickCount()); }
	~randomFunction() {}

	HRESULT init()
	{
		return S_OK;
	}

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}

	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};