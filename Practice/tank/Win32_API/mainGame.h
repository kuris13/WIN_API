#pragma once
#include "gameNode.h"
#include <vector>
/*
	mainGame�� ����� ������ ��. ���� ����� �� �̻� ������� ����

*/

const float PI{ 3.14592f };


class mainGame : public gameNode
{
private:
	int bulletCount = 0;
	circleTank tank;
	bullet bullet[10];

	
	POINT save{ 0,0 };
	
	char strPt[128];
	//�߾ӿ� ���� ��
	char strPt2[128];
	char strPt3[128];


public:
	HRESULT init();
	void release();
	void Fire();
	void update();
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {  }
};

