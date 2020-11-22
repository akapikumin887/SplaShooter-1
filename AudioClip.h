/*-----------------------------------------------------------

	[AudioClip.h]
	Author : ���c����

------------------------------------------------------------*/
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

class AudioClip
{
private:
	float m_Volume;

	//std::shared_ptr<IXAudio2SourceVoice> pSourceVoice;		// �\�[�X�{�C�X
	std::vector<std::shared_ptr<IXAudio2SourceVoice>> pSourceVoice;		// �\�[�X�{�C�X
	std::shared_ptr<BYTE> pDataAudio;						// �I�[�f�B�I�f�[�^
	DWORD SizeAudio;										// �I�[�f�B�I�f�[�^�T�C�Y

	XAUDIO2_VOICE_STATE xa2state;

public:
	AudioClip() = delete;
	AudioClip(std::string fileName);
	~AudioClip();

	float GetVolume() { return m_Volume; }
	void SetVolume(float vol) { m_Volume = vol; }
	BYTE* GetDateAudio() { return pDataAudio.get(); }
	DWORD GetSizeAudio() { return SizeAudio; }

	//IXAudio2SourceVoice* GetSourceVoice() { return pSourceVoice.get(); }
	std::vector<std::shared_ptr<IXAudio2SourceVoice>> GetSourceVoice() { return pSourceVoice; }
	void CopySourceVoice();
};

