#include "setDefine.h"
#include "image.h"

#pragma comment (lib, "msimg32.lib")
//↑ 알파블렌드를 사용하기 위한 라이브러리 추가

image::image()
	: _imageInfo(NULL), _fileName(NULL),
	_isTrans(FALSE), _transColor(RGB(0, 0, 0))
{
}

image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//재초기화 방지용(만약 이미지 정보에 값이 있을 경우엔 바로 release)
	if (_imageInfo != NULL) this->release();

	//DC 불러오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 세팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//만약 리소스를 얻어오는데 실패했을 경우
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용(만약 이미지 정보에 값이 있을 경우엔 바로 release)
	if (_imageInfo != NULL) this->release();

	//DC 불러오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 세팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//만약 리소스를 얻어오는데 실패했을 경우
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용(만약 이미지 정보에 값이 있을 경우엔 바로 release)
	if (_imageInfo != NULL) this->release();

	//DC 불러오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject
	(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//만약 리소스를 얻어오는데 실패했을 경우
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC,
		_imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일명
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//컬러
	_isTrans = isTrans;
	_transColor = transColor;

	//만약 리소스 불러오기가 실패한 경우
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC,
		_imageInfo->hBit);

	_imageInfo->width = width;
	_imageInfo->height = height;


	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;


	//파일명
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//컬러
	_isTrans = isTrans;
	_transColor = transColor;

	//만약 리소스 불러오기가 실패한 경우
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC,
		_imageInfo->hBit);

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;


	//파일명
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//컬러
	_isTrans = isTrans;
	_transColor = transColor;

	//만약 리소스 불러오기가 실패한 경우
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//이미지 정보
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap
	(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject
	(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//투명 키 세팅(1. 배경색 날리기, 2. 어떤 색 날릴 거?)
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//메모리에서 해제
void image::release()
{
	//이미지 정보가 남아 있으면 실행
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//렌더 : (0,0) 좌표에 그리기
void image::render(HDC hdc)
{
	if (_isTrans)	//이미지 파일의 배경 지우기
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,									        // 복사할 장소의 DC (화면에 출력되는 DC)
			0,											    // 복사될 장소의 시작 X좌표
			0,											    // 복사될 장소의 시작 Y좌표
			_imageInfo->width,			    // 복사될 이미지 가로 크기
			_imageInfo->height,			// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상의 메모리 DC
			0,											    // 복사 지점 (X)
			0,											    // 복사 지점 (Y)
			_imageInfo->width,			    // 복사 영역의 가로 크기
			_imageInfo->height,			// 복사 영역의 세로 크기
			_transColor							// 복사할 때 제외할 색상
		);
	}
	else  //지우지 않고 원본 이미지 그대로 출력
	{
		//BitBlt : DC 간의 영역끼리 서로 고속복사해주는 함수
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)	//이미지 파일의 배경 지우기
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,									        // 복사할 장소의 DC (화면에 출력되는 DC)
			destX,											    // 복사될 장소의 시작 X좌표
			destY,											    // 복사될 장소의 시작 Y좌표
			_imageInfo->width,			    // 복사될 이미지 가로 크기
			_imageInfo->height,			// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상의 메모리 DC
			0,											    // 복사 지점 (X)
			0,											    // 복사 지점 (Y)
			_imageInfo->width,			    // 복사 영역의 가로 크기
			_imageInfo->height,			// 복사 영역의 세로 크기
			_transColor							// 복사할 때 제외할 색상
		);
	}
	else  //지우지 않고 원본 이미지 그대로 출력
	{
		//BitBlt : DC 간의 영역끼리 서로 고속복사해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourceWidth, int sourceHeight)
{
	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sourceWidth,
			sourceHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourceWidth,
			sourceHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(hdc, destX, destY, sourceWidth, sourceHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파블렌드를 처음 사용하는 경우 초기화
	if (_blendImage) initAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//배경을 없앤 후에 알파블렌딩을 할 경우
	{
		//1. 출력해야될 DC에 그려져 있는 내용을 _blendImage에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);
		//2. 원본 이미지의 배경을 없앤 _blendImage에 그린다
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);
		//3. _blendImage를 화면에 그린다.
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파블렌드를 처음 사용하는 경우 초기화
	if (_blendImage) initAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//배경을 없앤 후에 알파블렌딩을 할 경우
	{
		//1. 출력해야될 DC에 그려져 있는 내용을 _blendImage에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. 원본 이미지의 배경을 없앤 _blendImage에 그린다
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		//3. _blendImage를 화면에 그린다.
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//화면에 그리는 영역 설정할 변수
	RECT rcSource;
	int sourceWidth;
	int sourceHeight;

	//DC 영역 (화면크기)
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourceHeight)
	{
		//영역의 높이 계산
		rcSource.top = (y + offsetY) % _imageInfo->height;
		rcSource.bottom = _imageInfo->height;
		sourceHeight = rcSource.bottom - rcSource.top;

		//영역이 그리는 화면 밖으로 넘어갔을 때
		if (y + sourceHeight > drawAreaH)
		{
			rcSource.top = y + drawAreaY;
			sourceHeight = rcSource.bottom - rcSource.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourceHeight;
	}

	//가로 루프 영역
	for (int x = 0; x < drawAreaW; x += sourceWidth)
	{
		//영역의 높이 계산
		rcSource.left = (x + offsetX) % _imageInfo->width;
		rcSource.right = _imageInfo->width;
		sourceWidth = rcSource.right - rcSource.left;

		//영역이 그리는 화면 밖으로 넘어갔을 때
		if (x + sourceWidth > drawAreaW)
		{
			rcSource.right -= (x + sourceWidth) - drawAreaW;
			sourceWidth = rcSource.right - rcSource.left;
		}

		rcDest.left = x + drawAreaX;
		rcDest.right = rcDest.left + sourceWidth;

		render(hdc, rcDest.left, rcDest.top, rcSource.left,
			rcSource.top, sourceWidth, sourceHeight);

		
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY
		);
	}


}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo-> currentFrameX = _imageInfo->maxFrameX;
	}

	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}


	if (_isTrans)
	{
		GdiTransparentBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY
		);
	}

}
