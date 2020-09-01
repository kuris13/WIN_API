#pragma once
#include "singletonBase.h"
#include "inc/fmod.hpp"

#pragma comment(lib,"lib/fmodex64_vc.lib")

using namespace FMOD;
//채널, 사운드 버퍼 설정


#define EXTRA_CHANNEL_BUFFER 5
#define SOUND_BUFFER 20

//전체 사운드 버퍼 설정
#define TOTAL_SOUND_BUFFER ( EXTRA_CHANNEL_BUFFER + SOUND_BUFFER )
class soundManager :public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSound_Iter;

	System* _system;		//시스템 클래스
	Sound** _sound;		//사운드 클래스
	Channel** _channel;		//채널 클래스
	arrSound _mTotalSound;	//map에 담아둘 사운드 정보


public:

	HRESULT init();
	void release();
	void update();
	void render();

	//사운드 추가
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	//사운드 플레이
	void play(string keyName, float volume = 1.0f);

	//사운드 정지
	void stop(string keyName);

	//사운드 일시정지
	void pause(string keyName);

	//사운드 재시작
	void resume(string keyName);

	soundManager():_system(nullptr),_sound(nullptr),_channel(nullptr) {};
	~soundManager() {};
};

