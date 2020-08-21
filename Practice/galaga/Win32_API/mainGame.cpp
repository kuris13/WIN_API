#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	//01. ���ĺ���
	_scene1 = new Scene_alphaRender;
	_scene1->init();

	_TestScene = new TestProj;
	_TestScene->init();

	//������ Scene�� ����
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

	//���� Ű�е� �Է¿� ���� Scene ��ȯ
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
