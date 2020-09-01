#pragma once
#include "gameNode.h"

const float PI = 3.14f;

struct BIRD
{
	RECT rc;
	float x, y;
	float speed;
	float gravity;
};

struct PIPE
{
	RECT rc;
	float speed;
};



class flappyBird : public gameNode
{
private:

	RECT _rcBackground;
	RECT _rcGround;

	BIRD _bird;
	PIPE _pipe[2];

	int _score;
	bool _isStart;
	bool _isGameover;



public:

	HRESULT init();
	void release();
	void update();
	void render();

	void BirdJump();
	void collision();
	void makePipe();

	flappyBird();
	~flappyBird();
};

