#pragma once

//윈도우 헤더 파일
#include <Windows.h>

//C언어 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//C++ 런타임 헤더 파일
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

/* ===================================
내가 만든 헤더 파일들
=================================== */
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"

/* ===================================
싱글톤
=================================== */
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()

/* ===================================
		윈도우 define 관련
=================================== */
#define WIN_NAME (LPTSTR)(TEXT("Window API"))
#define WINSTART_X 400
#define WINSTART_Y 100
#define WINSIZE_X 1280
#define WINSIZE_Y 720
#define WIN_STYLE CS_HREDRAW | CS_VREDRAW

/* ===================================
		Extern
=================================== */
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

/* ===================================
	동적할당된 객체를 해제하는 매크로 함수
=================================== */
#define SAFE_DELETE(p) {if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL;}}