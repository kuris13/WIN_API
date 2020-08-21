#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "bullet.h"

const int enemyLenght = 7;
const int bulletLength = 30;
class TestProj : public gameNode
{

private:
	RECT background;
	RECT aa;
	Enemy enemy[enemyLenght];
	RECT enemyRect[enemyLenght];
	bullet bullet[bulletLength];
	RECT player;
	int bC = 0;
public:

	HRESULT init();
	void release();
	void update();
	void render();


	TestProj();
	~TestProj();
};

