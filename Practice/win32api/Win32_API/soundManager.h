#pragma once
#include "singletonBase.h"
#include "inc/fmod.hpp"

#pragma comment(lib,"lib/fmodex64_vc.lib")

using namespace FMOD;
//ä��, ���� ���� ����


#define EXTRA_CHANNEL_BUFFER 5
#define SOUND_BUFFER 20

//��ü ���� ���� ����
#define TOTAL_SOUND_BUFFER ( EXTRA_CHANNEL_BUFFER + SOUND_BUFFER )
class soundManager :public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSound_Iter;

	System* _system;		//�ý��� Ŭ����
	Sound** _sound;		//���� Ŭ����
	Channel** _channel;		//ä�� Ŭ����
	arrSound _mTotalSound;	//map�� ��Ƶ� ���� ����


public:

	HRESULT init();
	void release();
	void update();
	void render();

	//���� �߰�
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	//���� �÷���
	void play(string keyName, float volume = 1.0f);

	//���� ����
	void stop(string keyName);

	//���� �Ͻ�����
	void pause(string keyName);

	//���� �����
	void resume(string keyName);

	soundManager():_system(nullptr),_sound(nullptr),_channel(nullptr) {};
	~soundManager() {};
};

