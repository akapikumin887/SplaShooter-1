/*-----------------------------------------------------------

	[AudioClip.cpp]
	Author : 太田朋希

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

	//ソースボイス配列の枠作成
	//pSourceVoice = nullptr;
	pSourceVoice.push_back(nullptr);
	pDataAudio = nullptr;
	SizeAudio = 0;

	//ファイル名を相対参照させる
	fileName = "asset/sound/" + fileName;

	//バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	// ファイルポインタを先頭に移動
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	// オーディオデータ読み込み
	hr = CheckChunk(hFile, 'atad', &SizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	//pDataAudio = (BYTE*)malloc(SizeAudio);
	pDataAudio = std::make_shared<BYTE>(SizeAudio);

	hr = ReadChunkData(hFile, pDataAudio.get(), SizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "一部の音楽ファイル読み込みに失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	// ソースボイスの生成
	//IXAudio2SourceVoice* sourcevoice = pSourceVoice.get();
	IXAudio2SourceVoice* sourcevoice = pSourceVoice.front().get();
	hr = AudioManager::GetInstance().GetXAudio2()->CreateSourceVoice(&sourcevoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "ソースボイスの作成に失敗しました。", NULL, MB_OK);	//メッセージ表示
		return;
	}

	//fileVolの初期化
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		// チャンクの読み込み
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		// チャンクデータの読み込み
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			// ファイルタイプの読み込み
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			// ファイルポインタをチャンクデータ分移動
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

	// ファイルポインタを指定位置まで移動
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// データの読み込み
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
