/*-----------------------------------------------------------

	[Audio.h]
	Author : �o���đ�

------------------------------------------------------------*/
#include "Audio.h"
#include "DirectX11.h"

IXAudio2* Audio::m_xAudio2 = nullptr;
IXAudio2MasteringVoice* Audio::m_masteringVoice = nullptr;
IXAudio2SourceVoice* Audio::m_sourceVoice[Sound::LABEL_MAX] = {};
BYTE* Audio::m_dataAudio[Sound::LABEL_MAX] = {};
DWORD Audio::m_sizeAudio[Sound::LABEL_MAX] = {};
Sound::Param Audio::m_param[Sound::LABEL_MAX] = {};

HRESULT Audio::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT Audio::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

void Audio::Init()
{
	using namespace Sound;
	HRESULT hr;
	
	// �T���v����
	//m_param[LABEL_SAMPLE].Filename = (char*)"Asset�t�@�C��"�G
	//m_param[LABEL_SAMPLE].LoopCount = -1; -1�Ȃ烋�[�v

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_xAudio2, 0);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr,"Xaudio2�I�u�W�F�N�g�쐬���s");

		// COM���C�u�����̏I������
		CoUninitialize();

		return;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "�}�X�^�[�{�C�X�̐����Ɏ��s");
		if (m_xAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_xAudio2->Release();
			m_xAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_param[nCntSound].Filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ThrowIfFailed(hr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(1)");
			return;
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			ThrowIfFailed(hr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(2)");
			return;
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)");
			return;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)");
			return;
		}
		if (dwFiletype != 'EVAW')
		{
			ThrowIfFailed(hr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)");
			return;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)");
			return;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)");
			return;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_sizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)");
			return;
		}
		m_dataAudio[nCntSound] = (BYTE*)malloc(m_sizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_dataAudio[nCntSound], m_sizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)");
			return;
		}

		// �\�[�X�{�C�X�̐���
		hr = m_xAudio2->CreateSourceVoice(&m_sourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "�\�[�X�{�C�X�̐����Ɏ��s�I");
			return;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_sizeAudio[nCntSound];
		buffer.pAudioData = m_dataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_param[nCntSound].LoopCount;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_sourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}
}

void Audio::Uninit()
{
	using namespace Sound;
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_sourceVoice[nCntSound])
		{
			// �ꎞ��~
			m_sourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			m_sourceVoice[nCntSound]->DestroyVoice();
			m_sourceVoice[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(m_dataAudio[nCntSound]);
			m_dataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_masteringVoice->DestroyVoice();
	m_masteringVoice = NULL;

	if (m_xAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_xAudio2->Release();
		m_xAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

void Audio::Play(Sound::Label label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio[label];
	buffer.pAudioData = m_dataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_param[label].LoopCount;

	// ��Ԏ擾
	m_sourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_sourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_sourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_sourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_sourceVoice[label]->Start(0);
}

void Audio::Stop()
{
	using namespace Sound;
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_sourceVoice[nCntSound])
		{
			// �ꎞ��~
			m_sourceVoice[nCntSound]->Stop(0);
		}
	}
}
