#pragma once
class image
{
public:
	image();
	~image();

	enum IMAGE_LOAD_CATEGORY
	{
		LOAD_RESOURCE,			//리소스 로딩(이미지가 사용 안 된 상태)
		LOAD_FILE,					//파일로 로딩
		LOAD_EMPTY,				//빈 비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;			//리소스ID
		HDC hMemDC;			//메모리DC
		HBITMAP hBit;			//비트맵
		HBITMAP hOBit;		//올드 비트맵

		float x;				//이미지 x좌표
		float y;				//이미지 y좌표


		int width;					//이미지 가로
		int height;					//이미지 세로

		int currentFrameX;			//현재 프레임 X값
		int currentFrameY;			//현재 프레임 Y값
		int maxFrameX;				//최대 프레임 X의 개수
		int maxFrameY;				//최대 프레임 Y의 개수
		int frameWidth;				//1프레임의 가로 크기
		int frameHeight;			//1프레임의 세로 크기
		

		BYTE loadType;			//이미지 로드타입
		
		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;

			x = y = 0;
			width = height = 0;
			currentFrameX = currentFrameY = 0;
			maxFrameX = maxFrameY = 0;
			
			//frameWidth = frameHeight = 0;

			width = height = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

	//초기화
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//FrameImage 초기화1
	HRESULT init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	//FrameImage 초기화2
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//알파블렌드 초기화
	HRESULT initAlphaBlend(void);











	//png처럼 보이게 하기 위해 특정 컬러(배경) 삭제
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//메모리 해제
	void release();

	//화면에 그리기 (내가 지정한 좌표에 이미지 출력)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	//화면에 그리기(내가 지정한 좌표에 내가 원하는 만큼만 출력)
	void render(HDC hdc, int destX, int destY,
		int sourceX, int sourceY, int sourceWidth, int sourceHeight);

	//알파 렌더 (알파값과 함께 이미지를 출력한다.)
	void alphaRender(HDC hdc, BYTE alpha);
	//알파 렌더 (내가 지정한 좌표에 이미지를 출력한다.)
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea,
		int offsetX, int offsetY);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY);



	//DC받아오기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//이미지 좌표 X
	inline float getX(void) { return _imageInfo->x;}
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 좌표 Y
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터 좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}


	//가로 세로 길이
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height };
	}

	//프레임 이미지용 바운딩 박스 (충돌용 렉트)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };
	}

	//프레임 X (get & set)
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//프레임 Y (get & set)
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//이미지 1프레임당 가로와 세로 크기 구하기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대 프레임의 X, Y값
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }



private:
	LPIMAGE_INFO _imageInfo;		//이미지 정보
	CHAR* _fileName;							//이미지 이름
	BOOL _isTrans;								//배경색을 일일이 없앨 것인가
	COLORREF _transColor;				//배경색을 없애는데 필요한 RGB

	BLENDFUNCTION _blendFunc;	//알파블렌드에 쓰일 요소
	LPIMAGE_INFO _blendImage;	//알파블렌드 이미지
};

