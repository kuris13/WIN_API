#include "setDefine.h"
#include "mainGame.h"
#include <thread>

using namespace std;

HRESULT mainGame::init()
{
	gameNode::init();
	w;
	
	w.loc = {WINSIZE_X/2, WINSIZE_Y/2 };
	w.bodySize = 40;
	w.radius = 30;
	w.speed = 8;
	w.angle = PI /2;
	tCount = 0;

	for (int i = 0; i < w.bodySize; i++) {
		w.bodyLoc.push_back(w.loc);
		w.bodyAngle.push_back(w.angle);
	}


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	
}



void mainGame::update()
{
	gameNode::update();
	

	//hody

	/*
	w.bodyAngle.at(0) = w.angle;
	w.bodyLoc.at(0).x = -cosf(w.bodyAngle.at(0)) * 50 + w.loc.x;
	w.bodyLoc.at(0).y = +sinf(w.bodyAngle.at(0)) * 50 + w.loc.y;
	
	
	for (int i = w.bodySize - 1; i > 0; i--) {
		w.bodyAngle.at(i) = w.bodyAngle.at(i - 1);
		w.bodyLoc.at(i).x = -cosf(w.bodyAngle.at(i)) * 50 + w.bodyLoc.at(i - 1).x;
		w.bodyLoc.at(i).y = +sinf(w.bodyAngle.at(i)) * 50 + w.bodyLoc.at(i - 1).y;

	}
	*/

	if (Xcount >= w.bodySize) {
		Xcount = 0;
		Fbody = 0;

	}
	
	if (tCount == 5) {
		w.bodyLoc.at(Xcount) = w.loc;
		tCount = 0;
		Fbody++;
		Xcount++;
	}
	


	//=================================
	//head
	w.loc.x += cosf(w.angle) * w.speed;
	w.loc.y += -sinf(w.angle) * w.speed;

	
	if (w.loc.x < 0)
	{
		w.angle = PI - w.angle;
	}
	else if (w.loc.x > WINSIZE_X)
	{
		w.angle = PI - w.angle;
	}
	else if (w.loc.y < 0)
	{
		w.angle = 2 * PI - w.angle;
	}
	else if (w.loc.y > WINSIZE_Y)
	{
		w.angle = 2 * PI - w.angle;
	}


	

	//=======================================
	//KeyManager에 따른 입력 처리
	//======================================


	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		w.angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		w.angle -= 0.04f;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {

		
		
	}
	//=======================================
	
	
	
	tCount++;
}





void mainGame::render(HDC hdc)
{
	


	//             2             3
	for (int i = Fbody ; i < w.bodySize; i++) {
	
		

		//첫번째 몸통부터 그려야 함
		EllipseMakeCenter(hdc,w.bodyLoc.at(i).x, w.bodyLoc.at(i).y,w.radius*2,w.radius *2 );
		
	}

	for (int i = 0; i < Fbody; i++) {
		EllipseMakeCenter(hdc, w.bodyLoc.at(i).x, w.bodyLoc.at(i).y, w.radius * 2, w.radius * 2);
	}
	
	//EllipseMakeCenter(hdc, w.bodyLoc.at(0).x, w.bodyLoc.at(0).y, w.radius * 2, w.radius * 2);
	EllipseMakeCenter(hdc, w.loc.x, w.loc.y, w.radius * 2, w.radius * 2);

	
	
	//브러쉬 생성/삭제 반복 or 브러쉬 생성된 채로 유지 
	wsprintf(strPt, "0번 loc.x : %d , loc.y : %d , Tcount : %d" , w.bodyLoc.at(0).x, w.bodyLoc.at(0).x, tCount);
	TextOut(hdc, 10, 740, strPt, strlen(strPt));

	

	
}

void mainGame::tail()
{
	if (tCount == 100) {

	}
	tCount++;
}

auto mainGame::collision(POINT body1, POINT body2, int radius)
{
	float distanceX = pow((body1.x - body2.x), 2);
	float distanceY = pow((body1.y - body2.y), 2);

	float distance = sqrtf(distanceX + distanceY);

	return distance;
}


