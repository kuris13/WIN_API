#include "setDefine.h"
#include "mainGame.h"
#include <Windows.h>
#include <thread>

using namespace std;


HRESULT mainGame::init()
{
	gameNode::init();
	
	//==============================
	//b.speed = 1.0;
					
	scoreBox = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
	
	tank.angle = PI / 2;			//90도로 포신 세우기
	tank.barLength = 150;			//포신의 길이
	tank.radius = 100;				//탱크 몸통
	tank.center.x = WINSIZE_X / 2;	//탱크 x
	tank.center.y = WINSIZE_Y;		//탱크 y

	//==============================


	return S_OK;
}

auto mainGame::pointPluse(POINT x, POINT x2)->decltype(x)
{
	POINT x3;
	x3.x = x2.x - x.x;
	x3.y = x2.y - x.y;
	return x3;
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

	bullet[bulletCount].nowLoc.x = cosf(tank.angle) * (bullet[bulletCount].bulletLengthX) + tank.center.x;
	bullet[bulletCount].nowLoc.y = -sinf(tank.angle) * (bullet[bulletCount].bulletLengthY) + tank.center.y;
	bullet[bulletCount].speed = 5.0;
	bullet[bulletCount].colOn = false;
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

		

		if (bullet[i].created == true) {
			

			if (bullet[i].colOn == true) {
				for (int j = 0; j < bulletC; j++) {

					if (bullet[j].created == true && j != i) {
						auto tempP = pointPluse(bullet[j].nowLoc, bullet[i].nowLoc);
						int tempX = tempP.x * tempP.x;
						int tempY = tempP.y * tempP.y;

						if (tempX + tempY <= (bullet[i].radias * 2) *(bullet[i].radias * 2)) {
							bullet[i].turnY = !bullet[i].turnY;
							bullet[i].turnX = !bullet[i].turnX;

							bullet[j].turnY = !bullet[j].turnY;
							bullet[j].turnX = !bullet[j].turnX;

							bullet[j].nowLoc.x += (((bullet[i].radias * 2) *(bullet[i].radias * 2)) - (tempX + tempY)) * cosf(bullet[j].angle);
							bullet[j].nowLoc.y += (((bullet[i].radias * 2) *(bullet[i].radias * 2)) - (tempX + tempY)) * -sinf(bullet[j].angle);



							wsprintf(strPt, "충돌한 원들 %d : %d ,받아온 temp.x : %d, 받아온 temp.y : %d ,두 점 사이의 거리(x,y) : (%d, %d)", i, j, tempP.x, tempP.y, tempX, tempY);
							//Sleep(1000);
						}
					}

				}
			}



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

			
			


			if (bullet[i].nowLoc.y < 25) {
				
				bullet[i].turnY = !bullet[i].turnY;
				//bullet[i].nowLoc.y = 25;
				bullet[i].colOn = true;
				//++bullet[i].turnCount;
			}
			else if (bullet[i].nowLoc.y > WINSIZE_Y-25) {
				bullet[i].turnY = !bullet[i].turnY;
				//bullet[i].nowLoc.y = WINSIZE_Y-25;
				bullet[i].colOn = true;
				//++bullet[i].turnCount;
			}

			if (bullet[i].nowLoc.x < 25) {

				bullet[i].turnX = !bullet[i].turnX;
				//bullet[i].nowLoc.x = 25;
				bullet[i].colOn = true;
				//++bullet[i].turnCount;
			}
			else if (bullet[i].nowLoc.x > WINSIZE_X-25) {
				bullet[i].turnX = !bullet[i].turnX;
				//bullet[i].nowLoc.x = WINSIZE_X-25;
				bullet[i].colOn = true;
				//++bullet[i].turnCount;
			}

			if (bullet[i].turnCount > 5) {
				bullet[i].created = false;
			}


			if (PtInRect(&scoreBox, bullet[i].nowLoc)) {
				bullet[i].turnY = !bullet[i].turnY;
				bullet[i].turnX = !bullet[i].turnX;
				//++bullet[i].turnCount;
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
			EllipseMakeCenter(hdc, bullet[i].nowLoc.x, bullet[i].nowLoc.y, bullet[i].radias*2, bullet[i].radias * 2);

		}
		
	}
	
	
	auto brush = CreateSolidBrush(RGB(230, 0, 0));
	FillRect(hdc, &scoreBox, brush);
	DeleteObject(brush);
	

	LineMake(hdc, tank.center, tank.barrel);


	
	TextOut(hdc, 10, 740, strPt, strlen(strPt));

}


