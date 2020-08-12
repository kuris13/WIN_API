#include "setDefine.h"
#include "mainGame.h"
#include <thread>

using namespace std;


HRESULT mainGame::init()
{
	gameNode::init();
	
	//==============================
	//b.speed = 1.0;
					
	for (int i = 0; i < 10; i++) {
		bullet[i].speed = 1.0;
	}
	


	tank.angle = PI / 2;			//90도로 포신 세우기
	tank.barLength = 150;			//포신의 길이
	tank.radius = 100;				//탱크 몸통
	tank.center.x = WINSIZE_X / 2;	//탱크 x
	tank.center.y = WINSIZE_Y;		//탱크 y

	//==============================


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	
}

void mainGame::Fire() {

}


void mainGame::update()
{
	gameNode::update();
	

	for (int i = 0; i < 10; i++) {
		if (bullet[i].nowLoc.y < 0) {
			bullet[i].created = false;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && tank.angle < 3.0f) {
		tank.angle += 0.04f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && tank.angle > 0.1f) {
		tank.angle -= 0.04f;
	}

	//포신 끝점의 x,y좌표를 각도에 따라 업데이트
	tank.barrel.x = cosf(tank.angle) * tank.barLength + tank.center.x;
	tank.barrel.y = -sinf(tank.angle) * tank.barLength + tank.center.y;


	for (int i = 0; i < 10; i++) {

		if (bullet[i].created == true) {
			bullet[i].nowLoc.x = cosf(bullet[i].angle) * (tank.barLength + bullet[i].speed) + tank.center.x;
			bullet[i].nowLoc.y = -sinf(bullet[i].angle) * (tank.barLength + bullet[i].speed) + tank.center.y;

			bullet[i].speed += 1;
		}

	}
	
	

	

	//=======================================
	//KeyManager에 따른 입력 처리
	//======================================

	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {

		bullet[bulletCount].created = true;
		bullet[bulletCount].angle = tank.angle;
		bullet[bulletCount].createLoc.x = cosf(tank.angle) * (tank.barLength) + tank.center.x;
		bullet[bulletCount].createLoc.y = -sinf(tank.angle) * (tank.barLength) + tank.center.y;
		
		bulletCount++;

		if (bulletCount == 10) {
			bulletCount = 0;
		}

	}

	//=======================================
}





void mainGame::render(HDC hdc)
{
	
	//원형 탱크
	EllipseMakeCenter(hdc, tank.center.x, tank.center.y, tank.radius * 2, tank.radius * 2);
	
	for (int i = 0; i < 10; i++) {
		EllipseMakeCenter(hdc, bullet[i].nowLoc.x, bullet[i].nowLoc.y, 50, 50);

	}
	
	

	
	
	LineMake(hdc, tank.center, tank.barrel);




}


