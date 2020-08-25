#pragma once
#include "gameNode.h"

/* ===================================
				내가 만든 Scene 목록
=================================== */
#include "Scene_alphaRender.h"
#include "Scene_galaga.h"
#include "Scene_loopRender.h"
#include "TestProj.h"

class mainGame : public gameNode
{
private:
	Scene_alphaRender* _scene1;
	Scene_galaga* _scene2;
	Scene_loopRender* _scene3;

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

