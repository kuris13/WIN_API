#include "setDefine.h"
#include "mainGame.h"
#include <thread>

using namespace std;

HRESULT mainGame::init()
{
	gameNode::init();
	
	
	player = RectMake(WINSIZE_X/2, WINSIZE_Y * 3/4, 25, 25);

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	
}



void mainGame::update()
{
	gameNode::update();
	
	
	
	

	//=======================================
	//KeyManager�� ���� �Է� ó��
	//======================================

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
	
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		

	}
	

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
	
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		


	}
	if (KEYMANAGER->isOnceKeyUp(VK_CONTROL))
	{
		
	}


	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {

		
		
	}
	//=======================================
}





void mainGame::render(HDC hdc)
{
	


	RectangleMake(hdc, player);

	
	
	

	

	//�귯�� ����/���� �ݺ� or �귯�� ������ ä�� ���� 
	wsprintf(strPt, "���� : %d  bulletTime : %d  ���� bulletTime Ƚ�� : %d  timeCount : %d");
	TextOut(hdc, 10, 740, strPt, strlen(strPt));

	

	
}


