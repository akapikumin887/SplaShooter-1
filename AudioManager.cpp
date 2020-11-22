/*-----------------------------------------------------------

	[AudioManager.cpp]
	Author : 太田朋希

------------------------------------------------------------*/
#include "AudioManager.h"

#include <thread>
#include <vector>

#include "AudioClip.h"

void AudioManager::Init()
{
	HRESULT hr;

	//COMの初期化
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (!hr == S_OK) return;

	//XAudio2の初期化
	//ここでエラーになった際はpXAudio2にロクな値が入っていないのでアクセスしないこと
	pXAudio2 = nullptr;
	hr = XAudio2Create(&pXAudio2);
	if (!hr == S_OK) return;

	//マスターボイスの取得
	//PCが音を出せる環境でない場合はここでエラーが出る可能性あり
	pMasteringVoice = nullptr;
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (!hr == S_OK) return;
}

void AudioManager::Uninit()
{
	//マスターボイスの破棄
	pMasteringVoice->DestroyVoice();

	//XAudio2の破棄
	//pXAudio2->Release();
	//pXAudio2 = nullptr;

	//COMの破棄
	CoUninitialize();
}

void AudioManager::PlaySound(std::shared_ptr<AudioClip> clip,int count)
{
	//第2引数はループの回数、0なら1回だけ流れる

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	int playFile = -1;

	auto sourceVoice = clip->GetSourceVoice();

	//バッファのクリア
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));


	//増やした配列内のソースボイスが働いていなかったら削除する
	for (int i = sourceVoice.size(); i > 1; i--)
	{
		//後ろから現在の状態を取得する
		sourceVoice[i - 1]->GetState(&xa2state);
		if (xa2state.BuffersQueued == 0)
		{
			//使われていなければ削除する
			sourceVoice[i - 1]->DestroyVoice();
			sourceVoice.pop_back();
		}
		else
			break;
	}


	//i番目に使いたいソースボイスが入っている
	//使用中なら複製、そうでなければここを使って音を出す
	for (int i = 0; i < sourceVoice.size(); i++)
	{
		sourceVoice[i]->GetState(&xa2state);

		//使用されていないのでここを使って曲を再生
		if (xa2state.BuffersQueued == 0)
		{
			playFile = i;
			break;
		}
	}

	//ソースボイスすべてが使用中なら複製してそこで再生する
	if (playFile == -1)
	{
		playFile = sourceVoice.size();
		clip->CopySourceVoice();
	}

	// バッファの値設定
	buffer.AudioBytes = clip->GetSizeAudio();
	buffer.pAudioData = clip->GetDateAudio();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = count;

	sourceVoice[playFile]->SubmitSourceBuffer(&buffer);

	//セットボリュームの回数を減らしたい
	//if (fileVol[playFile] != vol)
	//{
	//	fileVol[playFile] = vol;
	//	pSourceVoice[playFile]->SetVolume(vol);
	//}

	sourceVoice[playFile]->SetVolume(clip->GetVolume());
	sourceVoice[playFile]->Start(0);

}