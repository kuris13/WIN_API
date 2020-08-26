#pragma once
#include "gameNode.h"

#define BULLET_MAX 100
#define _ENEMY 30

//�� ����ü
struct ENEMY
{
	image* img;
	RECT rc;
	bool _isDead;
};

//ź��
struct BULLET
{
	image* img;
	RECT rc;
	bool _isFire;
};

class Scene_galaga : public gameNode
{
private:
	//�� ��ü
	ENEMY enemy[_ENEMY];

	//�÷��̾�
	RECT player;
	image* playerImage;

	//ź��
	BULLET bullet[BULLET_MAX];
	
	//���� ó���� bool
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

