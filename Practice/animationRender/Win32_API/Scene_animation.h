#pragma once
#include "gameNode.h"
class Scene_animation : public gameNode
{
private:
	image* player;

	RECT rc;

	bool _isStop;

	int _count, _index;



public:
	HRESULT init();
	void release();
	void update();
	void render();


	Scene_animation();
	~Scene_animation();
};

