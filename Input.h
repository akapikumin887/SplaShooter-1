/*------------------------------------------------------------

	[Input.cpp]
	イベント駆動型を行うための仮cpp
	キーボードの値を読み取り、そこに対応したイベントをその場で実行する
	Author : 太田朋希

-------------------------------------------------------------*/
#pragma once
#include <list>

#define KEY_LIMIT 6

class GameObject;

//キーボードの状態
enum KEYSTATE : int
{
	STATE_TRIGGER,
	STATE_PRESS,
	STATE_RELEASE,
	STATE_MAX
};

//キーボードの押すキーの種類
enum KEYTYPE : int
{
	KEY_W = 'W',
	KEY_A = 'A',
	KEY_S = 'S',
	KEY_D = 'D',
	KEY_ENTER = VK_RETURN,
	KEY_SPACE = VK_SPACE,
	KEY_MAX = 6
};

//現在押しているキーと状態を確認する
struct Key
{
	KEYTYPE keytype;
	KEYSTATE keystate;
};

class Input
{
private:
	std::list<Key> m_key;
	std::list<GameObject*> m_GameObject;
	bool m_IsKey[KEY_LIMIT * 3];

	BYTE m_OldKeyState[256];
	BYTE m_KeyState[256];

public:
	void Init();
	void Uninit();
	void Update();

	bool GetKeyPress(BYTE KeyCode);
	bool GetKeyTrigger(BYTE KeyCode);
	bool GetKeyRelease(BYTE KeyCode);

	static Input& GetInstance() 
	{
		static Input instance;
		return instance; 
	}
};
