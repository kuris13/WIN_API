#include "setDefine.h"
#include "mainGame.h"

//�ڵ�(handle)�� ���Ͽ�
/*
	1. �ڵ��� �������̸�, ��κ��� ��� 32��Ʈ���̴�.
	    ��� ������ ������ ������ �ϱ� �����̰�, �ڵ鳢�� �ߺ��� �� �ǵ��� �ؾ� �Ѵ�.
aaasdasdsad
	2. �ڵ��� OS�� �߱����ֹǷ� ����ڴ� �״�� �޾ƾ��⸸ �ϸ� �ȴ�.
	    �����츦 ����ų� ������ ���� OS�� �� �����쳪 ���Ͽ� �ڵ��� �ٿ��ش�.
		
	3. ���� ������ �ڵ鳢���� ����� �ߺ��� ���� ������ �ʴ´�.

	4. �ڵ��� �������̹Ƿ� ���� �������� ���� ���� �������� ���� ���� �������.
		������ ǥ�����νḸ ���Ǳ� ����.
*/

//HINSTANCE
/*
	HINSTANCE : ���α׷� �ڵ� ����� OS���� �����ϱ� ���� ���� �ĺ� ��ü
	���α׷��� ���� �� �������� �� ������ ���α׷� �ν��Ͻ��� ����Ű�µ�,
	�̰��� �����ϰ� �����ϱ� ���� ����δ� �ĺ��� ��
*/
HINSTANCE _hInstance;

//OS���� �ش� ���α׷��� �� �����츦 �����ϰ� �����ϱ� ���� ��ü
HWND _hWnd;

//������ â �̸�
LPTSTR _lpszClass = WIN_NAME;

//���콺 ������ ��ǥ���� ���� ��ü
POINT _ptMouse = { 0,0 };

//�����Ҵ�
mainGame* _mg;

//�������� ���� �۾������� ����
void setWindowSize(int x, int y, int width, int height);

//�Լ� ���� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
	hInstance : ���α׷� �ν��Ͻ� �ڵ�
	hPrevInstance : �ٷ� ��(����)�� ����Ǿ��� �ν��Ͻ� �ڵ�. WIN32������ �׻� NULL.
	lpszCmdParam : ��������� �Էµ� ���α׷� �μ�
	nCmdShow : ���α׷��� ����� ���� (�ִ�/�ּ�ȭ�� ������ ��� �� ����)
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//����ڰ� ������� �ϰ� �����ִ� ������ Ŭ����
	//���α׷��� ��� ������� �̰��� ������� ���������.
	WNDCLASS wndClass;

	//Windows�� ���������� ����ϴ� ������ ���� ����
	//�̰��� ����� ���� ���ٰ� ���� ����. �׷��� ���� 0�� ���Խ��� �ʱ�ȭ.
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	//�������� ���� ����
	//�������� ����� ä���� �귯���� �����ϴ� ����ü ���
	//���� ����� ���� ���
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//�� �����찡 ����� ���콺 Ŀ���� �ּ�ȭ���� ��� ��µ� ������ ����
	//����ڰ� ���� �����ܰ� Ŀ���� ���� ����� ����� ���� �ִ�
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	//WinMain�� �μ��ν� ���޵� hInstance ���� �״�� ���
	wndClass.hInstance = hInstance;

	//�������� �޽��� ó�� �Լ��� ����
	//�޽����� �߻��� ������ ������ �Լ��� ȣ��Ǹ�, �� �Լ��� ��� �޽����� ó���Ѵ�.
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;

	//�������� ��Ÿ���� �����Ѵ�.
	//�������� ����(�Ǵ� ����) ũ�Ⱑ ���� ��� �����츦 �ٽ� �׸���.
	wndClass.style = WIN_STYLE;

	//��� Ư���� ���� �����츦 ����ϰڴٰ� ����ϴ� RegisterClass �Լ�
	RegisterClass(&wndClass);

	//CreateWindow�� ȭ�鿡 ��µ� ����� ����
	_hWnd = CreateWindow(

		//lpszClassName : �����ϰ��� �ϴ� �������� Ŭ������ �����ϴ� ���ڿ�
		_lpszClass, 

		//lpszWindowName : �������� Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		_lpszClass,

		//dwStyle : ������� �ϴ� ������ ���¸� ����
		/*
			�����찡 ��輱�� ���� ���ΰ�, Ÿ��Ʋ �ٸ� ���� ���ΰ�, ��ũ�ѹ� ���� ��
			WS_OVERLAPPEDWINDOW�� ���� �⺻���� �����̴�.
			�ý��� �޴�, �ִ�/�ּ�ȭ ��ư, Ÿ��Ʋ��, ��輱�� ���� �����츦 �����.
		*/
		WS_OVERLAPPEDWINDOW,

		//X,Y, nWidth, nHeight : �������� ũ��� ��ġ�� ���� (�ȼ� ����)
		//��ǥ�� CW_USEDEFAULT�� �Է��ϸ� OS�� �˾Ƽ� ������ ũ��� ��ġ�� ����
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,

		//hWndParent : �θ� �����찡 ���� ��� �θ� �������� �ڵ��� ����
		//���� ��쿣 NULL�� �д�
		NULL,

		//hmenu : �����쿡�� ����� �޴��� �ڵ��� ����
		(HMENU)NULL,

		//hinst : �����츦 ����� ��ü, ���α׷� �ڵ��� ����
		//�ַ� WinMain�� �μ��ν� ���޵� hInstance�� ������ �ȴ�.
		hInstance,

		//lpvParam : CREATESTRUCT��� ����ü�� ����(�ּ�)�̸� Ư�������� ���]
		//������ NULL�� �Է��صд�.
		NULL);

	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	//�����츦 ȭ�鿡 ����ϴ� ����� �Ѱ��ִ� �Լ�
	ShowWindow(_hWnd, nCmdShow);

	//========================================================

	_mg = new mainGame();
	
	//���� �ʱ�ȭ�� �����Ѵٸ� �״�� ���μ��� ����
	if (FAILED(_mg->init())) return 0;

	//========================================================



	//�޽��� ����ü
	MSG message;

	//GetMessage() : �ý����� �����ϰ� �ִ� �޽��� ť(Queue)���� �޽����� �о���δ�.
	//WM_QUIT �޽��� �Էµƴ� => �̰͸� false�� ����, ������ �޽����� true ����
	//�ٽ� ���ؼ� WM_QUIT ���� ������ �߻��ϱ� ������ ��� ���α׷��� �����ȴ�.
	while (GetMessage(&message, 0, 0, 0))
	{
		//TranslateMessage : Ű���� ���� �Է� ���
		/*
			�Է� �Ǵ� �Է������� �߻����� ��, �Էµƴٴ� �޽����� ����.
			���� ��� AŰ�� ���� �� �ٽ� AŰ���� ���� ���� A��� ���ڰ�
			�Էµƴٴ� �޽����� ���ο��� �����.
		*/
		TranslateMessage(&message);

		//DispatchMessage : �޽����� �޽��� ó�� �Լ�(WndProc)�� ����
		//�ش� �޽����� ������ �Ŀ� ���� ������ �����ϰ� �����ش�.
		DispatchMessage(&message);
	}

	//========================================================
		
	//���μ����� ����Ǹ� �޸𸮿��� ����
	_mg->release();

	//����ص� ������ Ŭ������ ����
	UnregisterClass(WIN_NAME, hInstance);

	//========================================================


	return message.wParam;
}

//==============================================



//==============================================

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
													  WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0,0, width, height };

	//��輱, �޴�, ��ũ�ѹٸ� ������ �۾� ������ �缳��
	AdjustWindowRect(&rc, WIN_STYLE, false);

	//�� ������ ������ ũ��� ��ġ�� ����
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

/*
	������ ����

	1. ���ݱ��� ��� ������ �̿��Ͽ� ��~�� ��� �� ������
	(Rectangle, Ellipse, Line ���)
	
	2. ����� �� �ڿ� Ű���� ����Ű �Է����� ��� �� ����������
	3. �� �Ǵ� ���� ���콺 �巡�׷� �����̰� �����
*/