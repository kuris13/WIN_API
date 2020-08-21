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
		int width;					//이미지 가로
		int height;					//이미지 세로
		BYTE loadType;			//이미지 로드타입
		
		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
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

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }


private:
	LPIMAGE_INFO _imageInfo;		//이미지 정보
	CHAR* _fileName;							//이미지 이름
	BOOL _isTrans;								//배경색을 일일이 없앨 것인가
	COLORREF _transColor;				//배경색을 없애는데 필요한 RGB

	BLENDFUNCTION _blendFunc;	//알파블렌드에 쓰일 요소
	LPIMAGE_INFO _blendImage;	//알파블렌드 이미지
};

