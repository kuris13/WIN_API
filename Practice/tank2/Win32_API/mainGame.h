#pragma once
#include "gameNode.h"
#include <vector>
/*
	mainGame�� ����� ������ ��. ���� ����� �� �̻� ������� ����

*/
const int bulletC{ 100 };
const float PI{ 3.14592f };


class mainGame : public gameNode
{
private:
	
	int bulletCount = 0;
	circleTank tank;
	bullet bullet[bulletC];
	RECT scoreBox;
	RECT real_scoreBox;
	POINT save{ 0,0 };
	int score=0;
	char strPt[128];
	//�߾ӿ� ���� ��
	char strPt2[128];
	char strPt3[128];


public:

	HRESULT init();
	auto pointPluse(POINT x, POINT x2)->decltype(x);
	void release();
	auto bulletInit();
	void Fire();
	void update();
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {  }
};

