#include "setDefine.h"
#include "soundManager.h"




HRESULT soundManager::init()
{
	//사운드 시스템 생성
	System_Create(&_system);

	//사운드 채널 수 설정
	_system->init(3, FMOD_INIT_NORMAL, 0);

	//사운드 채널 수만큼 클래스 동적할당
	_sound = new Sound*[3];
	_channel = new Channel*[3];

	//메모리 초기화
	memset(_sound, 0, sizeof(Sound*) * 3);
	memset(_channel, 0, sizeof(Channel*) * 3);


	return E_NOTIMPL;
}

void soundManager::release()
{
	//사운드 채널 제거
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < 3; i++)
		{
			if (_channel != nullptr) _channel[i]->stop();
			if (_sound != nullptr) _sound[i]->release();
		}
	}


	SAFE_DELETE_ARRAY(_sound);
	SAFE_DELETE_ARRAY(_channel);

	//사운드 시스템 닫기
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}

}

void soundManager::update()
{
	//사운드 시스템의 볼륨 조절이나 재생 후 사운드 변경
	//또는 그에 상응하는 컨텐츠 관리용
	_system->update();
}

void soundManager::render()
{

}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		//BGM 재생
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
		//브금은 아닌데 반복 재생이 필요한 사운드일 경우
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
	}
	else	//SE (효과음)
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	//사운드를 키값과 함께 map에 담아둔다.
	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));


}

void soundManager::play(string keyName, float volume)
{
	//채널을 선택하는 용도
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//빈 채널을 찾아서 볼륨 설정 후, 값을 저장한 뒤 재생
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			//볼륨설정
			_channel[count]->setVolume(volume);
		}
	}

	/*
	for (const auto &each : _mTotalSound)
	{
		if (keyName == each.first)
		{
			//빈 채널을 찾아서 볼륨 설정 후, 값을 저장한 뒤 재생
			_system->playSound(FMOD_CHANNEL_FREE, each.second, false, &_channel[count]);

			//볼륨설정
			_channel[count]->setVolume(volume);
		}
	}
	*/

}

void soundManager::stop(string keyName)
{
	//채널을 선택하는 용도
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->stop();
			break;
		}

	}
}

void soundManager::pause(string keyName)
{
	//채널을 선택하는 용도
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시 정지
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	//채널을 선택하는 용도
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시 정지
			_channel[count]->setPaused(false);
			break;
		}
	}
}
