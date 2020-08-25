#include "setDefine.h"
#include "Scene_animation.h"



HRESULT Scene_animation::init()
{
	//스프라이트 시트 이미지 추가
	//450 , 256 -> bmp파일 크기
	//9 ,4 가로 몇개 세로 몇개인지 
	IMAGEMANAGER->addFrameImage("캐릭터", "Images/woman.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 450, 256, 9, 4, true, RGB(0, 0, 0));

	//이미지를 객체에 할당
	player = IMAGEMANAGER->findImage("캐릭터");

	//이미지를 덧 씌울 RECT 초기화
	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 50, 64);

	//카운터 변수 초기화
	_count = _index = 0;

	//캐릭터 움직임을 판단하는 bool 변수
	_isStop = false;

	return S_OK;
}

void Scene_animation::release()
{
}

void Scene_animation::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 5;
		rc.right -= 5;
		_isStop = false;

		player->setFrameY(1);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += 5;
		rc.right += 5;
		_isStop = false;

		player->setFrameY(2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 5;
		rc.bottom -= 5;
		_isStop = false;

		player->setFrameY(3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 5;
		rc.bottom += 5;
		_isStop = false;

		player->setFrameY(0);
	}

	//애니메이션 재생
	{
		_count++;

		if (_count % 5 == 0)
		{
			//캐릭터가 정지한 경우 가장 처음에 위치한 스프라이트를 출력 (좌측 상단)
			if (_isStop)
			{
				player->setFrameX(0);
				return;
			}

			//그렇지 않을 경우 애니메이션 출력
			if (_index > 9) _index = 0;

			//setFrame의 값은 _index에서 받아온다.
			player->setFrameX(_index);
			_index++;
		}
	}

	//방향키 입력을 안 했을 때는 움직임을 스스로 멈추도록
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_isStop = true;
		player->setFrameX(0);
	}
}

void Scene_animation::render()
{
	//출력
	IMAGEMANAGER->frameRender("캐릭터", getMemDC(), rc.left, rc.top);

	//디버그용 박스 ON/OFF
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), rc);
	}
}

Scene_animation::Scene_animation()
{
}


Scene_animation::~Scene_animation()
{
}
