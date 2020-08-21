#pragma once
#include "gameNode.h"

/* ===================================
				���� ���� Scene ���
=================================== */
#include "Scene_alphaRender.h"
#include "TestProj.h"

class mainGame : public gameNode
{
private:
	Scene_alphaRender* _scene1;
	TestProj* _TestScene;
	gameNode* _currentScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

