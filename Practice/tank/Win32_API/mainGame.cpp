#include "setDefine.h"
#include "mainGame.h"
#include <thread>

using namespace std;


HRESULT mainGame::init()
{
	gameNode::init();
	
	//==============================
	//b.speed = 1.0;
					
	scoreBox = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
	real_scoreBox = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 80);
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
auto mainGame::bulletInit() {
	bullet[bulletCount].created = true;
	bullet[bulletCount].turnCount = 0;
	bullet[bulletCount].turnX = false;
	bullet[bulletCount].turnY = false;
	bullet[bulletCount].angle = tank.angle;
	bullet[bulletCount].bulletLengthX = tank.barLength;
	bullet[bulletCount].bulletLengthY = tank.barLength;

	bullet[bulletCount].createLoc.x = cosf(tank.angle) * (bullet[bulletCount].bulletLengthX) + tank.center.x;
	bullet[bulletCount].createLoc.y = -sinf(tank.angle) * (bullet[bulletCount].bulletLengthY) + tank.center.y;
	bullet[bulletCount].speed = 1.0;
	bulletCount++;
}

void mainGame::update()
{
	gameNode::update();
	

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && tank.angle < 3.0f) {
		tank.angle += 0.04f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && tank.angle > 0.1f) {
		tank.angle -= 0.04f;
	}

	//포신 끝점의 x,y좌표를 각도에 따라 업데이트
	tank.barrel.x = cosf(tank.angle) * tank.barLength + tank.center.x;
	tank.barrel.y = -sinf(tank.angle) * tank.barLength + tank.center.y;


	for (int i = 0; i < bulletC; i++) {

		bullet[i].speed = 10;

		if (bullet[i].created == true) {
			

			if (bullet[i].turnX == true) 
			{
				//angle 발사 각도, barlength 발사 위치로부터의 거리 , centet 발자 위치
				//탱크 센터 기준으 angle각도 만큼 barlength거리로 설정
				bullet[i].bulletLengthX -= bullet[i].speed;
				bullet[i].nowLoc.x = cosf(bullet[i].angle) * (bullet[i].bulletLengthX) + tank.center.x;
			}
			else if(bullet[i].turnX == false) 
			{
				bullet[i].bulletLengthX += bullet[i].speed;
				bullet[i].nowLoc.x = cosf(bullet[i].angle) * (bullet[i].bulletLengthX) + tank.center.x;
			}

			if (bullet[i].turnY == true) 
			{
				bullet[i].bulletLengthY -= bullet[i].speed;
				bullet[i].nowLoc.y = -sinf(bullet[i].angle) * (bullet[i].bulletLengthY) + tank.center.y;

			}
			else if (bullet[i].turnY == false)
			{
				bullet[i].bulletLengthY += bullet[i].speed;
				bullet[i].nowLoc.y = -sinf(bullet[i].angle) * ( bullet[i].bulletLengthY) + tank.center.y;
				
			}


			


			if (bullet[i].nowLoc.y < 0) {
				
				bullet[i].turnY = !bullet[i].turnY;
				bullet[i].nowLoc.y = 0;
				++bullet[i].turnCount;
			}
			else if (bullet[i].nowLoc.y > WINSIZE_Y) {
				bullet[i].turnY = !bullet[i].turnY;
				bullet[i].nowLoc.y = WINSIZE_Y;
				++bullet[i].turnCount;
			}

			if (bullet[i].nowLoc.x < 0) {

				bullet[i].turnX = !bullet[i].turnX;
				bullet[i].nowLoc.x = 0;
				++bullet[i].turnCount;
			}
			else if (bullet[i].nowLoc.x > WINSIZE_X) {
				bullet[i].turnX = !bullet[i].turnX;
				bullet[i].nowLoc.x = WINSIZE_X;
				++bullet[i].turnCount;
			}
			if (bullet[i].turnCount > 5) {
				bullet[i].created = false;
			}

			if (PtInRect(&scoreBox, bullet[i].nowLoc)) {
				bullet[i].turnY = !bullet[i].turnY;
				bullet[i].turnX = !bullet[i].turnX;
				++bullet[i].turnCount;
			}
			if (PtInRect(&real_scoreBox, bullet[i].nowLoc)) {
				++score;
			}
			




		}

		

	}
	
	

	

	//=======================================
	//KeyManager에 따른 입력 처리
	//======================================

	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {

		if (bullet[bulletCount].created == false) {
			bulletInit();
		}
		

		if (bulletCount == bulletC) {
			bulletCount = 0;
		}

	}

	//=======================================
}





void mainGame::render(HDC hdc)
{

	

	//원형 탱크
	EllipseMakeCenter(hdc, tank.center.x, tank.center.y, tank.radius * 2, tank.radius * 2);

	//EllipseMake(hdc, scoreBox);

	for (int i = 0; i < bulletC; i++) {
		if (bullet[i].created == true) {
			EllipseMakeCenter(hdc, bullet[i].nowLoc.x, bullet[i].nowLoc.y, 50, 50);

		}
		
	}
	
	
	auto brush = CreateSolidBrush(RGB(230, 0, 0));
	FillRect(hdc, &scoreBox, brush);
	DeleteObject(brush);
	

	LineMake(hdc, tank.center, tank.barrel);


	wsprintf(strPt, "점수   :   %d", score);
	TextOut(hdc, 10, 740, strPt, strlen(strPt));

}


