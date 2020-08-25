#pragma once
#include "gameNode.h"

class Scene_alphaRender : public gameNode
{
private:
	float _alpha;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	Scene_alphaRender() {}
	~Scene_alphaRender() {}
};

