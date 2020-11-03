/*---------------------------------------------------------

	[Application.h]
	�Q�[���A�v���P�[�V�����̊Ǘ�
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#include <Windows.h>

// �Q�[���A�v�����Ǘ� ���V���O���g��
class Application
{
private:
	WNDCLASSEX	m_WindowClass;
	HWND m_hwnd;
	// �E�B���h�E�T�C�Y
	const unsigned int m_Width = 1920;
	const unsigned int m_Height = 1080;
	// �E�B���h�E���[�h true->WindowScrren false->FullScrren
	bool m_WindowMode = false; 

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

