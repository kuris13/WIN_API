#pragma once
#include "gameNode.h"
#include <vector>
/*
	mainGame�� ����� ������ ��. ���� ����� �� �̻� ������� ����

*/


class mainGame : public gameNode
{
private:
	RECT rc;

	RECT player;

	char strPt[128];
	//�߾ӿ� ���� ��
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

