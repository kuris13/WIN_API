#include "setDefine.h"
#include "mainGame.h"

//핸들(handle)에 대하여
/*
	1. 핸들은 정수값이며, 대부분의 경우 32비트값이다.
	    사용 목적은 오로지 구분을 하기 위함이고, 핸들끼리 중복이 안 되도록 해야 한다.

	2. 핸들은 OS가 발급해주므로 사용자는 그대로 받아쓰기만 하면 된다.
	    윈도우를 만들거나 파일을 열면 OS는 그 윈도우나 파일에 핸들을 붙여준다.
		
	3. 같은 종류의 핸들끼리는 절대로 중복된 값을 가지지 않는다.

	4. 핸들은 정수형이므로 값을 가지지만 실제 무슨 값인지는 몰라도 전혀 상관없다.
		일종의 표식으로써만 사용되기 때문.
*/

//HINSTANCE
/*
	HINSTANCE : 프로그램 코드 덩어리를 OS에서 관리하기 위한 고유 식별 객체
	프로그램을 여러 개 실행했을 때 각각을 프로그램 인스턴스라 가리키는데,
	이것을 구분하고 관리하기 위해 적어두는 식별용 값
*/
HINSTANCE _hInstance;

//OS에서 해당 프로그램의 각 윈도우를 구별하고 관리하기 위한 객체
HWND _hWnd;

//윈도우 창 이름
LPTSTR _lpszClass = WIN_NAME;

//마우스 포인터 좌표값을 담을 객체
POINT _ptMouse = { 0,0 };

//동적할당
mainGame* _mg;

//윈도우의 실제 작업영역을 설정
void setWindowSize(int x, int y, int width, int height);

//함수 전방 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
	hInstance : 프로그램 인스턴스 핸들
	hPrevInstance : 바로 앞(이전)에 실행되었던 인스턴스 핸들. WIN32에서는 항상 NULL.
	lpszCmdParam : 명령행으로 입력된 프로그램 인수
	nCmdShow : 프로그램이 실행될 형태 (최대/최소화나 윈도우 모양 등 전달)
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//사용자가 입출력을 하게 도와주는 윈도우 클래스
	//프로그램의 모든 윈도우는 이것을 기반으로 만들어진다.
	WNDCLASS wndClass;

	//Windows가 내부적으로 사용하는 일종의 예약 영역
	//이것을 사용할 일은 없다고 봐도 좋다. 그래서 보통 0을 대입시켜 초기화.
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	//윈도우의 배경색 지정
	//윈도우의 배경을 채색할 브러쉬를 지정하는 구조체 멤버
	//보통 흰색을 많이 사용
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//이 윈도우가 사용할 마우스 커서와 최소화됐을 경우 출력될 아이콘 지정
	//사용자가 직접 아이콘과 커서를 따로 만들어 사용할 수도 있다
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//윈도우 클래스를 사용하는 프로그램 번호
	//WinMain의 인수로써 전달된 hInstance 값을 그대로 사용
	wndClass.hInstance = hInstance;

	//윈도우의 메시지 처리 함수를 지정
	//메시지가 발생할 때마다 지정된 함수가 호출되며, 이 함수가 모든 메시지를 처리한다.
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;

	//윈도우의 스타일을 정의한다.
	//윈도우의 수직(또는 수평) 크기가 변할 경우 윈도우를 다시 그린다.
	wndClass.style = WIN_STYLE;

	//어떠한 특성을 가진 윈도우를 사용하겠다고 등록하는 RegisterClass 함수
	RegisterClass(&wndClass);

	//CreateWindow로 화면에 출력될 모습을 설정
	_hWnd = CreateWindow(

		//lpszClassName : 생성하고자 하는 윈도우의 클래스를 지정하는 문자열
		_lpszClass, 

		//lpszWindowName : 윈도우의 타이틀 바에 나타날 문자열
		_lpszClass,

		//dwStyle : 만들고자 하는 윈도우 형태를 지정
		/*
			윈도우가 경계선을 가질 것인가, 타이틀 바를 가질 것인가, 스크롤바 유무 등
			WS_OVERLAPPEDWINDOW는 가장 기본적인 형태이다.
			시스템 메뉴, 최대/최소화 버튼, 타이틀바, 경계선을 가진 윈도우를 만든다.
		*/
		WS_OVERLAPPEDWINDOW,

		//X,Y, nWidth, nHeight : 윈도우의 크기와 위치를 지정 (픽셀 단위)
		//좌표에 CW_USEDEFAULT를 입력하면 OS가 알아서 적당한 크기와 위치를 설정
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,

		//hWndParent : 부모 윈도우가 있을 경우 부모 윈도우의 핸들을 지정
		//없을 경우엔 NULL로 둔다
		NULL,

		//hmenu : 윈도우에서 사용할 메뉴의 핸들을 지정
		(HMENU)NULL,

		//hinst : 윈도우를 만드는 주체, 프로그램 핸들을 지정
		//주로 WinMain의 인수로써 전달된 hInstance를 넣으면 된다.
		hInstance,

		//lpvParam : CREATESTRUCT라는 구조체의 번지(주소)이며 특수목적에 사용]
		//보통은 NULL을 입력해둔다.
		NULL);

	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	//윈도우를 화면에 출력하는 방법을 넘겨주는 함수
	ShowWindow(_hWnd, nCmdShow);

	//========================================================

	_mg = new mainGame();
	
	//만약 초기화에 실패한다면 그대로 프로세스 종료
	if (FAILED(_mg->init())) return 0;

	//========================================================



	//메시지 구조체
	MSG message;

	//GetMessage() : 시스템이 유지하고 있는 메시지 큐(Queue)에서 메시지를 읽어들인다.
	//WM_QUIT 메시지 입력됐다 => 이것만 false로 리턴, 나머지 메시지를 true 리턴
	//다시 말해서 WM_QUIT 관련 내용이 발생하기 전까진 계속 프로그램이 유지된다.
	while (GetMessage(&message, 0, 0, 0))
	{
		//TranslateMessage : 키보드 관련 입력 담당
		/*
			입력 또는 입력해제가 발생했을 때, 입력됐다는 메시지를 만듦.
			예를 들어 A키를 누른 후 다시 A키에서 손을 떼면 A라는 문자가
			입력됐다는 메시지를 내부에서 만든다.
		*/
		TranslateMessage(&message);

		//DispatchMessage : 메시지를 메시지 처리 함수(WndProc)에 전달
		//해당 메시지를 점검한 후에 다음 동작을 결정하게 도와준다.
		DispatchMessage(&message);
	}

	//========================================================
		
	//프로세스가 종료되면 메모리에서 해제
	_mg->release();

	//등록해둔 윈도우 클래스를 해제
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

	//경계선, 메뉴, 스크롤바를 제외한 작업 영역을 재설정
	AdjustWindowRect(&rc, WIN_STYLE, false);

	//위 정보로 윈도우 크기와 위치를 변경
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

/*
	연습용 문제

	1. 지금까지 배운 도형을 이용하여 대~충 사람 얼굴 만들어보기
	(Rectangle, Ellipse, Line 등등)
	
	2. 만들고 난 뒤에 키보드 방향키 입력으로 사람 눈 움직여보기
	3. 코 또는 입은 마우스 드래그로 움직이게 만든다
*/