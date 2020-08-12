#pragma once
#include "gameNode.h"
#include <vector>
/*
	mainGame은 토대의 역할을 함. 씬을 만들면 더 이상 사용하지 않음

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
	//중앙에 나올 말
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

