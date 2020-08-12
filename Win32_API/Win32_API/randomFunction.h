#pragma once
#include "singletonBase.h"
#include <random>

using namespace std;
/*
	c++ 11 ǥ������ �ٲٱ� 
*/




class randomFunction : public singletonBase<randomFunction>
{
private:
	
public:
	random_device rn;



	//GetTickCount() : OS�� ���õ� ���Ŀ� ����� �ð��� ���� 
	//������
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