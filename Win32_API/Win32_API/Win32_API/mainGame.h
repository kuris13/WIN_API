#pragma once
#include "gameNode.h"
#include <vector>
/*
	mainGame은 토대의 역할을 함. 씬을 만들면 더 이상 사용하지 않음

*/


class mainGame : public gameNode
{
private:
	RECT rc;

	RECT player;

	char strPt[128];
	//중앙에 나올 말
	char strPt2[128];
	char strPt3[128];


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	mainGame() {}
	~mainGame() {  }
};

