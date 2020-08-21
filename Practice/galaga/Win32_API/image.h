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
		int width;					//�̹��� ����
		int height;					//�̹��� ����
		BYTE loadType;			//�̹��� �ε�Ÿ��
		
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

	//�ʱ�ȭ
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

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

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }


private:
	LPIMAGE_INFO _imageInfo;		//�̹��� ����
	CHAR* _fileName;							//�̹��� �̸�
	BOOL _isTrans;								//������ ������ ���� ���ΰ�
	COLORREF _transColor;				//������ ���ִµ� �ʿ��� RGB

	BLENDFUNCTION _blendFunc;	//���ĺ��忡 ���� ���
	LPIMAGE_INFO _blendImage;	//���ĺ��� �̹���
};

