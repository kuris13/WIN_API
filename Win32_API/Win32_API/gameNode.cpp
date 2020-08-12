#include "setDefine.h"
#include "gameNode.h"

//�ʱ�ȭ
HRESULT gameNode::init()
{
	//SetTimer(hWnd, nIDEvent, wElapse, TimerFunc );
	//�ð�����
	/*
		hWnd		: ������ �ڵ� ����
		nIDEvent	: Ÿ�̸��� ��ȣ�� ����, Ÿ�̸Ӱ��� ������ �ϱ� ���� ���
					 ( windows���� ���ÿ� ���� ���� Ÿ�̸Ӱ� ��ġ�� �� ���� )
		wElapse		: WM_TIMER �޽����� �����Ǵ� �ð� ������ ����.
					 ( 1 / 1000 �� ������ ������ �� �ִ�. ms )
		TimerFunc	: ���� NULL�� �����Ͽ� WM_TIMER �޽����� WndProc�� ���޵� �� �ֵ��� �Ѵ�.
	*/
	SetTimer(_hWnd, 1, 10, NULL);

	return S_OK;
}

//����
void gameNode::release()
{
	//Ÿ�̸� ������
	KillTimer(_hWnd, 1);
}

//�ǽð� ����
void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, TRUE);
}

//�׸��� ��
void gameNode::render(HDC hdc)
{
	//���� �׸��� ����
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
