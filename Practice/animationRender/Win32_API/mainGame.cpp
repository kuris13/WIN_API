#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	//01. 알파블렌드
	_scene1 = new Scene_alphaRender;
	_scene1->init();

	//02. 갤러그
	_scene2 = new Scene_galaga;
	_scene2->init();

	//03. 루프 렌더
	_scene3 = new Scene_loopRender;
	_scene3->init();

	_scene4 = new Scene_animation;
	_scene4->init();

	//테스트Scene
	_TestScene = new TestProj;
	_TestScene->init();

	//실행할 Scene을 선택
	_currentScene = _scene1;

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	SAFE_DELETE(_scene1);
	SAFE_DELETE(_scene2);
	SAFE_DELETE(_scene3);
	SAFE_DELETE(_scene4);
}

void mainGame::update()
{
	gameNode::update();

	_currentScene->update();

	//숫자 키패드 입력에 따라 Scene 전환
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
		_currentScene = _scene1;

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
		_currentScene = _scene2;

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		_currentScene = _scene3;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		_currentScene = _scene4;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
		_currentScene = _TestScene;
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//render
	_currentScene->render();

	this->getBackBuffer()->render(getHDC());
}
