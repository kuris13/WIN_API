#include "setDefine.h"
#include "image.h"

#pragma comment (lib, "msimg32.lib")
//�� ���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�

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
	//���ʱ�ȭ ������(���� �̹��� ������ ���� ���� ��쿣 �ٷ� release)
	if (_imageInfo != NULL) this->release();

	//DC �ҷ�����
	HDC hdc = GetDC(_hWnd);

	//�̹��� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���� ���ҽ��� �����µ� �������� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������(���� �̹��� ������ ���� ���� ��쿣 �ٷ� release)
	if (_imageInfo != NULL) this->release();

	//DC �ҷ�����
	HDC hdc = GetDC(_hWnd);

	//�̹��� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���� ���ҽ��� �����µ� �������� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������(���� �̹��� ������ ���� ���� ��쿣 �ٷ� release)
	if (_imageInfo != NULL) this->release();

	//DC �ҷ�����
	HDC hdc = GetDC(_hWnd);

	//�̹��� ����
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

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���� ���ҽ��� �����µ� �������� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	return E_FAIL;
}

HRESULT image::initAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//�̹��� ����
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

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���� Ű ����(1. ���� ������, 2. � �� ���� ��?)
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//�޸𸮿��� ����
void image::release()
{
	//�̹��� ������ ���� ������ ����
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//����Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//���� : (0,0) ��ǥ�� �׸���
void image::render(HDC hdc)
{
	if (_isTrans)	//�̹��� ������ ��� �����
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,									        // ������ ����� DC (ȭ�鿡 ��µǴ� DC)
			0,											    // ����� ����� ���� X��ǥ
			0,											    // ����� ����� ���� Y��ǥ
			_imageInfo->width,			    // ����� �̹��� ���� ũ��
			_imageInfo->height,			// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		// ����� ����� �޸� DC
			0,											    // ���� ���� (X)
			0,											    // ���� ���� (Y)
			_imageInfo->width,			    // ���� ������ ���� ũ��
			_imageInfo->height,			// ���� ������ ���� ũ��
			_transColor							// ������ �� ������ ����
		);
	}
	else  //������ �ʰ� ���� �̹��� �״�� ���
	{
		//BitBlt : DC ���� �������� ���� ��Ӻ������ִ� �Լ�
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)	//�̹��� ������ ��� �����
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,									        // ������ ����� DC (ȭ�鿡 ��µǴ� DC)
			destX,											    // ����� ����� ���� X��ǥ
			destY,											    // ����� ����� ���� Y��ǥ
			_imageInfo->width,			    // ����� �̹��� ���� ũ��
			_imageInfo->height,			// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		// ����� ����� �޸� DC
			0,											    // ���� ���� (X)
			0,											    // ���� ���� (Y)
			_imageInfo->width,			    // ���� ������ ���� ũ��
			_imageInfo->height,			// ���� ������ ���� ũ��
			_transColor							// ������ �� ������ ����
		);
	}
	else  //������ �ʰ� ���� �̹��� �״�� ���
	{
		//BitBlt : DC ���� �������� ���� ��Ӻ������ִ� �Լ�
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
	//���ĺ��带 ó�� ����ϴ� ��� �ʱ�ȭ
	if (_blendImage) initAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//����� ���� �Ŀ� ���ĺ����� �� ���
	{
		//1. ����ؾߵ� DC�� �׷��� �ִ� ������ _blendImage�� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);
		//2. ���� �̹����� ����� ���� _blendImage�� �׸���
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);
		//3. _blendImage�� ȭ�鿡 �׸���.
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
	//���ĺ��带 ó�� ����ϴ� ��� �ʱ�ȭ
	if (_blendImage) initAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//����� ���� �Ŀ� ���ĺ����� �� ���
	{
		//1. ����ؾߵ� DC�� �׷��� �ִ� ������ _blendImage�� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. ���� �̹����� ����� ���� _blendImage�� �׸���
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		//3. _blendImage�� ȭ�鿡 �׸���.
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

	//ȭ�鿡 �׸��� ���� ������ ����
	RECT rcSource;
	int sourceWidth;
	int sourceHeight;

	//DC ���� (ȭ��ũ��)
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourceHeight)
	{
		//������ ���� ���
		rcSource.top = (y + offsetY) % _imageInfo->height;
		rcSource.bottom = _imageInfo->height;
		sourceHeight = rcSource.bottom - rcSource.top;

		//������ �׸��� ȭ�� ������ �Ѿ�� ��
		if (y + sourceHeight > drawAreaH)
		{
			rcSource.top = y + drawAreaY;
			sourceHeight = rcSource.bottom - rcSource.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourceHeight;
	}

	//���� ���� ����
	for (int x = 0; x < drawAreaW; x += sourceWidth)
	{
		//������ ���� ���
		rcSource.left = (x + offsetX) % _imageInfo->width;
		rcSource.right = _imageInfo->width;
		sourceWidth = rcSource.right - rcSource.left;

		//������ �׸��� ȭ�� ������ �Ѿ�� ��
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
