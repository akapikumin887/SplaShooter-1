/*------------------------------------------------------------

	[Input.cpp]
	�C�x���g�쓮�^���s�����߂̉�cpp
	�L�[�{�[�h�̒l��ǂݎ��A�����ɑΉ������C�x���g�����̏�Ŏ��s����
	Author : ���c����

-------------------------------------------------------------*/
#pragma once

class Input
{
private:
	//std::list<int*> m_CodeList;

	BYTE m_OldKeyState[256];
	BYTE m_KeyState[256];

	static Input instance;

public:
	void Init();
	void Uninit();
	void Update();

	bool GetKeyPress(BYTE KeyCode);
	bool GetKeyTrigger(BYTE KeyCode);
	bool GetKeyRelease(BYTE KeyCode);

	static Input& GetInstance() { return instance; }
};
