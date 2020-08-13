#include "setDefine.h"
#include "gameNode.h"

//초기화
HRESULT gameNode::init()
{
	//SetTimer(hWnd, nIDEvent, wElapse, TimerFunc );
	//시간계산용
	/*
		hWnd		: 윈도우 핸들 지정
		nIDEvent	: 타이머의 번호를 지정, 타이머간의 구분을 하기 위해 사용
					 ( windows에는 동시에 여러 개의 타이머가 설치될 수 있음 )
		wElapse		: WM_TIMER 메시지가 생성되는 시간 간격을 설정.
					 ( 1 / 1000 초 단위로 지정할 수 있다. ms )
		TimerFunc	: 보통 NULL로 지정하여 WM_TIMER 메시지가 WndProc로 전달될 수 있도록 한다.
	*/
	SetTimer(_hWnd, 1, 10, NULL);

	return S_OK;
}

//해제
void gameNode::release()
{
	//타이머 삭제용
	KillTimer(_hWnd, 1);
}

//실시간 갱신
void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, TRUE);
}

//그리는 곳
void gameNode::render(HDC hdc)
{
	//뭔가 그리는 곳임
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:

		KEYMANAGER->ptMouse.x = LOWORD(lParam);
		KEYMANAGER->ptMouse.y = HIWORD(lParam);
		//_ptMouse.x = LOWORD(lParam);
		//_ptMouse.y = HIWORD(lParam);

		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
