#include "setDefine.h"
#include "soundManager.h"




HRESULT soundManager::init()
{
	//���� �ý��� ����
	System_Create(&_system);

	//���� ä�� �� ����
	_system->init(3, FMOD_INIT_NORMAL, 0);

	//���� ä�� ����ŭ Ŭ���� �����Ҵ�
	_sound = new Sound*[3];
	_channel = new Channel*[3];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * 3);
	memset(_channel, 0, sizeof(Channel*) * 3);


	return E_NOTIMPL;
}

void soundManager::release()
{
	//���� ä�� ����
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

	//���� �ý��� �ݱ�
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}

}

void soundManager::update()
{
	//���� �ý����� ���� �����̳� ��� �� ���� ����
	//�Ǵ� �׿� �����ϴ� ������ ������
	_system->update();
}

void soundManager::render()
{

}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		//BGM ���
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
		//����� �ƴѵ� �ݺ� ����� �ʿ��� ������ ���
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
	}
	else	//SE (ȿ����)
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	//���带 Ű���� �Բ� map�� ��Ƶд�.
	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));


}

void soundManager::play(string keyName, float volume)
{
	//ä���� �����ϴ� �뵵
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//�� ä���� ã�Ƽ� ���� ���� ��, ���� ������ �� ���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			//��������
			_channel[count]->setVolume(volume);
		}
	}

	/*
	for (const auto &each : _mTotalSound)
	{
		if (keyName == each.first)
		{
			//�� ä���� ã�Ƽ� ���� ���� ��, ���� ������ �� ���
			_system->playSound(FMOD_CHANNEL_FREE, each.second, false, &_channel[count]);

			//��������
			_channel[count]->setVolume(volume);
		}
	}
	*/

}

void soundManager::stop(string keyName)
{
	//ä���� �����ϴ� �뵵
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->stop();
			break;
		}

	}
}

void soundManager::pause(string keyName)
{
	//ä���� �����ϴ� �뵵
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ� ����
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	//ä���� �����ϴ� �뵵
	int count = 0;
	arrSound_Iter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �Ͻ� ����
			_channel[count]->setPaused(false);
			break;
		}
	}
}
