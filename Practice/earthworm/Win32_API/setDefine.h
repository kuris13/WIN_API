#pragma once

//윈도우 헤더 파일
#include <Windows.h>

//C언어 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/* ===================================
내가 만든 헤더 파일들
=================================== */
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "box.h"
#include "worm.h"
/* ===================================
싱글톤
=================================== */
#define KEYMANAGER keyManager::getSingleton()
//#define MOUSEMANAGER mouseManager::getSingleton()
#define RND randomFunction::getSingleton()


/* ===================================
		윈도우 define 관련
=================================== */
#define WIN_NAME (LPTSTR)(TEXT("Window API"))
#define WINSTART_X 400
#define WINSTART_Y 100
#define WINSIZE_X 800
#define WINSIZE_Y 800
#define WIN_STYLE CS_HREDRAW | CS_VREDRAW

#define FOCUSBOX 5
/* ===================================
		Extern
=================================== */
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;