/*---------------------------------------------------------

	[Application.h]
	�Q�[���A�v���P�[�V�����̊Ǘ�
	Author : �o���đ�

----------------------------------------------------------*/
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

// �Q�[���A�v�����Ǘ� ���V���O���g��
class Application
{
private:
	WNDCLASSEX	m_WindowClass;
	HWND m_hwnd;
	const unsigned int m_Width = 1200;
	const unsigned int m_Height = 720;

	// �Q�[���p�E�B���h�E�쐬
	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& windowclass); 
	// private�R���X�g���N�^
	Application() {}
	// �R�s�[�A����͋֎~
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;
public:
	~Application() {};
	static Application& Instance(); // �C���X�^���X
	bool Init(HINSTANCE hinstance); // ������
	void AppRun();					
	SIZE GetWindowSize()const;
	HWND Gethwnd()const;
};

