/*----------------------------------------------------------------

	[Fps.h]
	Author : �o���đ�

-----------------------------------------------------------------*/
#pragma once
#include <Windows.h>

// �t���[�����[�g���Ǘ� ���V���O���g��
class Fps
{
private:
	const float m_Framerate;
	DWORD m_dwExcLastTime;
	DWORD m_dwCurrentTime;
	DWORD m_dwOldCurrentTime;
	bool m_isReset;

	// private�R���X�g���N�^
	Fps() : m_Framerate(60), m_dwExcLastTime(0), m_dwCurrentTime(0), m_dwOldCurrentTime(0), m_isReset(false), m_deltaTime(0) { }
	// �R�s�[�A����͋֎~
	Fps(const Fps&) = delete;
	void operator= (const Fps&) = delete;
public:
	float m_deltaTime;
	static Fps& Instance(); // �C���X�^���X
	void Init();			// ������
	void Uninit();			// �I��
	bool Update();			// �X�V
	void Reset();			// ���Z�b�g
};
