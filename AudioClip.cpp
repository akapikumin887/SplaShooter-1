/*-----------------------------------------------------------

	[AudioClip.cpp]
	Author : ���c����

------------------------------------------------------------*/
#include "AudioClip.h"

#include "AudioManager.h"

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


AudioClip::AudioClip(std::string fileName)
{
	HRESULT hr;
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype = 0;
	WAVEFORMATEXTENSIBLE wfx;

	XAUDIO2_BUFFER buffer;

	//�\�[�X�{�C�X�z��̘g�쐬
	//pSourceVoice = nullptr;
	pSourceVoice.push_back(nullptr);
	pDataAudio = nullptr;
	SizeAudio = 0;

	//�t�@�C�����𑊑ΎQ�Ƃ�����
	fileName = "asset/sound/" + fileName;

	//�o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	// �t�@�C���|�C���^��擪�Ɉړ�
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = CheckChunk(hFile, 'atad', &SizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	//pDataAudio = (BYTE*)malloc(SizeAudio);
	pDataAudio = std::make_shared<BYTE>(SizeAudio);

	hr = ReadChunkData(hFile, pDataAudio.get(), SizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�ꕔ�̉��y�t�@�C���ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	// �\�[�X�{�C�X�̐���
	//IXAudio2SourceVoice* sourcevoice = pSourceVoice.get();
	IXAudio2SourceVoice* sourcevoice = pSourceVoice.front().get();
	hr = AudioManager::GetInstance().GetXAudio2()->CreateSourceVoice(&sourcevoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "�\�[�X�{�C�X�̍쐬�Ɏ��s���܂����B", NULL, MB_OK);	//���b�Z�[�W�\��
		return;
	}

	//fileVol�̏�����
	m_Volume = 0.0f;
}

AudioClip::~AudioClip()
{

}

void AudioClip::CopySourceVoice()
{
	pSourceVoice.push_back(pSourceVoice.front());
}


HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
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
		// �`�����N�̓ǂݍ���
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		// �`�����N�f�[�^�̓ǂݍ���
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			// �t�@�C���^�C�v�̓ǂݍ���
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{
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

HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	// �t�@�C���|�C���^���w��ʒu�܂ňړ�
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// �f�[�^�̓ǂݍ���
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
