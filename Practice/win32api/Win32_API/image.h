#pragma once
class image
{
public:
	image();
	~image();

	enum IMAGE_LOAD_CATEGORY
	{
		LOAD_RESOURCE,			//���ҽ� �ε�(�̹����� ��� �� �� ����)
		LOAD_FILE,					//���Ϸ� �ε�
		LOAD_EMPTY,				//�� ��Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;			//���ҽ�ID
		HDC hMemDC;			//�޸�DC
		HBITMAP hBit;			//��Ʈ��
		HBITMAP hOBit;		//�õ� ��Ʈ��

		float x;				//�̹��� x��ǥ
		float y;				//�̹��� y��ǥ


		int width;					//�̹��� ����
		int height;					//�̹��� ����

		int currentFrameX;			//���� ������ X��
		int currentFrameY;			//���� ������ Y��
		int maxFrameX;				//�ִ� ������ X�� ����
		int maxFrameY;				//�ִ� ������ Y�� ����
		int frameWidth;				//1�������� ���� ũ��
		int frameHeight;			//1�������� ���� ũ��
		

		BYTE loadType;			//�̹��� �ε�Ÿ��
		
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

	//�ʱ�ȭ
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//FrameImage �ʱ�ȭ1
	HRESULT init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	//FrameImage �ʱ�ȭ2
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//���ĺ��� �ʱ�ȭ
	HRESULT initAlphaBlend(void);











	//pngó�� ���̰� �ϱ� ���� Ư�� �÷�(���) ����
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//�޸� ����
	void release();

	//ȭ�鿡 �׸��� (���� ������ ��ǥ�� �̹��� ���)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	//ȭ�鿡 �׸���(���� ������ ��ǥ�� ���� ���ϴ� ��ŭ�� ���)
	void render(HDC hdc, int destX, int destY,
		int sourceX, int sourceY, int sourceWidth, int sourceHeight);

	//���� ���� (���İ��� �Բ� �̹����� ����Ѵ�.)
	void alphaRender(HDC hdc, BYTE alpha);
	//���� ���� (���� ������ ��ǥ�� �̹����� ����Ѵ�.)
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	//���� ����
	void loopRender(HDC hdc, const LPRECT drawArea,
		int offsetX, int offsetY);

	//������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY);



	//DC�޾ƿ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//�̹��� ��ǥ X
	inline float getX(void) { return _imageInfo->x;}
	inline void setX(float x) { _imageInfo->x = x; }

	//�̹��� ��ǥ Y
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� ���� ��ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}


	//���� ���� ����
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//�ٿ�� �ڽ�
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height };
	}

	//������ �̹����� �ٿ�� �ڽ� (�浹�� ��Ʈ)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };
	}

	//������ X (get & set)
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//������ Y (get & set)
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//�̹��� 1�����Ӵ� ���ο� ���� ũ�� ���ϱ�
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ִ� �������� X, Y��
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }



private:
	LPIMAGE_INFO _imageInfo;		//�̹��� ����
	CHAR* _fileName;							//�̹��� �̸�
	BOOL _isTrans;								//������ ������ ���� ���ΰ�
	COLORREF _transColor;				//������ ���ִµ� �ʿ��� RGB

	BLENDFUNCTION _blendFunc;	//���ĺ��忡 ���� ���
	LPIMAGE_INFO _blendImage;	//���ĺ��� �̹���
};

