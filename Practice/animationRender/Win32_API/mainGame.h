#pragma once
#include "gameNode.h"

/* ===================================
				���� ���� Scene ���
=================================== */
#include "Scene_alphaRender.h"
#include "Scene_galaga.h"
#include "Scene_loopRender.h"
#include "TestProj.h"
#include "Scene_animation.h"

class mainGame : public gameNode
{
private:
	Scene_alphaRender* _scene1;
	Scene_galaga* _scene2;
	Scene_loopRender* _scene3;
	Scene_animation* _scene4;
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

