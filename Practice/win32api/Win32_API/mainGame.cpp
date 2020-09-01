#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	//01. 알파블렌드
	SCENEMANAGER->addScene("알파렌더", new Scene_alphaRender);

	//02. 갤러그
	SCENEMANAGER->addScene("갤러그",new Scene_galaga);
	
	//03. 루프 렌더
	SCENEMANAGER->addScene("루프렌더",new Scene_loopRender );

	//04
	SCENEMANAGER->addScene("애니메이션",new Scene_animation );
	
	//05
	SCENEMANAGER->addScene("픽셀충돌",new p_Scene );

	//테스트Scene
	SCENEMANAGER->addScene("테스트",new TestProj);

	//bird
	SCENEMANAGER->addScene("버드", new birdScene);

	//shop
	SCENEMANAGER->addScene("상점", new Scene_shop);

	//popol
	SCENEMANAGER->addScene("포폴", new popolScene);

	//실행할 Scene을 선택
	SCENEMANAGER->changeScene("알파렌더");

	






	//====================================
	//재생할 사운드를 추가
	SOUNDMANAGER->addSound("브금", "BGM.mp3",true,true);

	//사운드 재생
	//SOUNDMANAGER->play("브금", 0.5f);



	return S_OK;
}

void mainGame::release()
{
	gameNode::release();


}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();

	//숫자 키패드 입력에 따라 Scene 전환
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
		SCENEMANAGER->changeScene("알파렌더");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
		SCENEMANAGER->changeScene("갤러그");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
		SCENEMANAGER->changeScene("루프렌더");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		SCENEMANAGER->changeScene("애니메이션");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		SCENEMANAGER->changeScene("픽셀충돌");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		SCENEMANAGER->changeScene("픽셀충돌");


	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
		SCENEMANAGER->changeScene("버드");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
		SCENEMANAGER->changeScene("상점");

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		SCENEMANAGER->changeScene("포폴");

}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//render
	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC());
}
