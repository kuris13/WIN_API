#pragma once
#include "singletonBase.h"
#include <random>

using namespace std;
/*
	c++ 11 표준으로 바꾸기 
*/




class randomFunction : public singletonBase<randomFunction>
{
private:
	
public:
	random_device rn;



	//GetTickCount() : OS가 부팅된 이후에 경과한 시간을 리턴 
	//생성자
	randomFunction() 
	{ 
		//srand(GetTickCount()); 
	}	
	~randomFunction() { }

	HRESULT init()
	{
		return S_OK;
	}
	
	inline int getInt(int num)
	{
		
		mt19937_64 rnd(rn());

		uniform_int_distribution<int> range(0, num);
		
		return range(rnd);
	}

	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}


};