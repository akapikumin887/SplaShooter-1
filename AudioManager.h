/*-----------------------------------------------------------

	[AudioManager.h]
	Author : ���c����

------------------------------------------------------------*/
#pragma once

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include <vector>
#include <memory>
#include <wrl.h>

class AudioClip;

class AudioManager
{
private:
	Microsoft::WRL::ComPtr<IXAudio2> pXAudio2;			// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* pMasteringVoice;			// �}�X�^�[�{�C�X

public:
	void Init();
	void Uninit();

	void PlaySound(std::shared_ptr<AudioClip> clip,int count = 0);

	//void PlayBGM(std::string fName, float vol = 1.0f, float time = 0.0f);
	//void PlaySE(std::string fName, float vol = 1.0f);
	void StopBGM(float time = 2.0f);
	void StopBGM(std::string fName);
	void ChangeVolume(std::string fName, float vol);

	static AudioManager& GetInstance()
	{
		static AudioManager instance;
		return instance; 
	}

	Microsoft::WRL::ComPtr<IXAudio2> GetXAudio2() {return pXAudio2;}
};

