#pragma once
#include "gameNode.h"
class birdScene : public gameNode
{
	
private:

	RECT background;
	RECT enemy[7];
	RECT player;
	int pow = 0;
	int _offsetX1 = 0, _offsetY1 = 0;
	bool isJump = false;
	int jC = 0;
	
	int score=0;
	char str[128];
	char str2[128];
	int randEnemy=3;

	bool gameStop = false;;
public:


	void gameInit();

	HRESULT init();
	void release();
	void update();
	void render();
};

