/*------------------------------------------------------------

	[Input.cpp]
	�C�x���g�쓮�^���s�����߂̉�cpp
	�L�[�{�[�h�̒l��ǂݎ��A�����ɑΉ������C�x���g�����̏�Ŏ��s����
	Author : ���c����

-------------------------------------------------------------*/
#pragma once
#include <list>

#define KEY_LIMIT 6

class GameObject;

//�L�[�{�[�h�̏��
enum KEYSTATE : int
{
	STATE_TRIGGER,
	STATE_PRESS,
	STATE_RELEASE,
	STATE_MAX
};

//�L�[�{�[�h�̉����L�[�̎��
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

//���݉����Ă���L�[�Ə�Ԃ��m�F����
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
