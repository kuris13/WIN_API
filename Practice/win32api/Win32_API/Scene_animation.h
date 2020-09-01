#pragma once
#include "gameNode.h"
#include "progressBar.h"
class Scene_animation : public gameNode
{
private:
	image* player;

	RECT rc;

	bool _isStop;

	int _count, _index;

	float _maxHP, _currentHP;
	progressBar* _hpBar;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	Scene_animation();
	~Scene_animation();
};

