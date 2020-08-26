#pragma once
#include "gameNode.h"
class birdScene : public gameNode
{

private:

	RECT background;
	RECT enemy[4];
	RECT player;
	int pow = 0;
	int _offsetX1 = 0, _offsetY1 = 0;
	bool isJump = false;
	int jC = 0;
	
	bool gameStop = false;;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

