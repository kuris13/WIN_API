#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	//01. 알파블렌드
	_scene1 = new Scene_alphaRender;
	_scene1->init();

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
}

void mainGame::update()
{
	gameNode::update();

	_currentScene->update();

	//숫자 키패드 입력에 따라 Scene 전환
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
		_currentScene = _scene1;

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		_currentScene = _TestScene;

}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//render
	_currentScene->render();

	this->getBackBuffer()->render(getHDC());
}
