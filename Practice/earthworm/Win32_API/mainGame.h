#pragma once
#include "gameNode.h"
#include <vector>
/*
	mainGame은 토대의 역할을 함. 씬을 만들면 더 이상 사용하지 않음

*/

const float PI = 3.141592f;

class mainGame : public gameNode
{
private:
	worm w;

	RECT player;
	int Xcount =0;
	int Fbody =0 ;
	char strPt[128];
	//중앙에 나올 말
	char strPt2[128];
	char strPt3[128];
	int tCount;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void tail();

	auto collision(POINT body1, POINT body2, int radius);
	mainGame() {}
	~mainGame() {  }
};

