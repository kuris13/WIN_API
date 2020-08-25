#pragma once
#include "gameNode.h"

#define BULLET_MAX 100
#define _ENEMY 30

//적 구조체
struct ENEMY
{
	image* img;
	RECT rc;
	bool _isDead;
};

//탄약
struct BULLET
{
	image* img;
	RECT rc;
	bool _isFire;
};

class Scene_galaga : public gameNode
{
private:
	//적 개체
	ENEMY enemy[_ENEMY];

	//플레이어
	RECT player;
	image* playerImage;

	//탄약
	BULLET bullet[BULLET_MAX];
	
	//몬스터 처리용 bool
	bool _isOver;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void isFired();
	void Movement();

	Scene_galaga() {}
	~Scene_galaga() {}
};

