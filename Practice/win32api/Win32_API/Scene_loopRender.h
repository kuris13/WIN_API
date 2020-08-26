#pragma once
#include "gameNode.h"

class Scene_loopRender : public gameNode
{
private:
	int _offsetX1, _offsetY1;
	int _offsetX2, _offsetY2;
	int _offsetX3, _offsetY3;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	Scene_loopRender() {}
	~Scene_loopRender() {}
};

