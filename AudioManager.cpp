/*-----------------------------------------------------------

	[AudioManager.cpp]
	Author : ���c����

------------------------------------------------------------*/
#include "AudioManager.h"

#include <thread>
#include <vector>

#include "AudioClip.h"

void AudioManager::Init()
{
	HRESULT hr;

	//COM�̏�����
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (!hr == S_OK) return;

	//XAudio2�̏�����
	//�����ŃG���[�ɂȂ����ۂ�pXAudio2�Ƀ��N�Ȓl�������Ă��Ȃ��̂ŃA�N�Z�X���Ȃ�����
	pXAudio2 = nullptr;
	hr = XAudio2Create(&pXAudio2);
	if (!hr == S_OK) return;

	//�}�X�^�[�{�C�X�̎擾
	//PC�������o������łȂ��ꍇ�͂����ŃG���[���o��\������
	pMasteringVoice = nullptr;
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (!hr == S_OK) return;
}

void AudioManager::Uninit()
{
	//�}�X�^�[�{�C�X�̔j��
	pMasteringVoice->DestroyVoice();

	//XAudio2�̔j��
	//pXAudio2->Release();
	//pXAudio2 = nullptr;

	//COM�̔j��
	CoUninitialize();
}

void AudioManager::PlaySound(std::shared_ptr<AudioClip> clip,int count)
{
	//��2�����̓��[�v�̉񐔁A0�Ȃ�1�񂾂������

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	int playFile = -1;

	auto sourceVoice = clip->GetSourceVoice();

	//�o�b�t�@�̃N���A
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));


	//���₵���z����̃\�[�X�{�C�X�������Ă��Ȃ�������폜����
	for (int i = sourceVoice.size(); i > 1; i--)
	{
		//��납�猻�݂̏�Ԃ��擾����
		sourceVoice[i - 1]->GetState(&xa2state);
		if (xa2state.BuffersQueued == 0)
		{
			//�g���Ă��Ȃ���΍폜����
			sourceVoice[i - 1]->DestroyVoice();
			sourceVoice.pop_back();
		}
		else
			break;
	}


	//i�ԖڂɎg�������\�[�X�{�C�X�������Ă���
	//�g�p���Ȃ畡���A�����łȂ���΂������g���ĉ����o��
	for (int i = 0; i < sourceVoice.size(); i++)
	{
		sourceVoice[i]->GetState(&xa2state);

		//�g�p����Ă��Ȃ��̂ł������g���ċȂ��Đ�
		if (xa2state.BuffersQueued == 0)
		{
			playFile = i;
			break;
		}
	}

	//�\�[�X�{�C�X���ׂĂ��g�p���Ȃ畡�����Ă����ōĐ�����
	if (playFile == -1)
	{
		playFile = sourceVoice.size();
		clip->CopySourceVoice();
	}

	// �o�b�t�@�̒l�ݒ�
	buffer.AudioBytes = clip->GetSizeAudio();
	buffer.pAudioData = clip->GetDateAudio();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = count;

	sourceVoice[playFile]->SubmitSourceBuffer(&buffer);

	//�Z�b�g�{�����[���̉񐔂����炵����
	//if (fileVol[playFile] != vol)
	//{
	//	fileVol[playFile] = vol;
	//	pSourceVoice[playFile]->SetVolume(vol);
	//}

	sourceVoice[playFile]->SetVolume(clip->GetVolume());
	sourceVoice[playFile]->Start(0);

}