/*---------------------------------------------------------

	[Application.cpp]
	Author : �o���đ�

----------------------------------------------------------*/
#include "Application.h"
#include "InputDevice.h"

#pragma region Fps_Func
Fps & Fps::Instance()
{
	static Fps instance;
	return instance;
}

void Fps::Init()
{
	timeBeginPeriod(1);
	m_dwExcLastTime = timeGetTime();
}

void Fps::Uninit()
{
	timeEndPeriod(1);
}

bool Fps::Update()
{
	m_dwOldCurrentTime = m_dwCurrentTime;
	m_dwCurrentTime = timeGetTime();
	if (m_dwCurrentTime - m_dwExcLastTime >= (1000 / m_Framerate))
	{
		m_deltaTime = (m_dwCurrentTime - m_dwExcLastTime) / 1000.0f;
		if (m_deltaTime >= 1 / m_Framerate)
		{
			m_deltaTime = 1 / m_Framerate;
		}
		if (m_isReset == true)
		{
			m_deltaTime = 0;
			m_isReset = false;
		}
		m_dwExcLastTime = m_dwCurrentTime;
		return true;
	}
	else
	{
		return false;
	}
}

void Fps::Reset()
{
	m_isReset = true;
}
#pragma endregion Fps�N���X�̊֐�

#pragma region Application_Func
// �E�B���h�E�v���V�[�W��
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Application::CreateGameWindow(HWND & hwnd, WNDCLASSEX & windowClass)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	// �E�B���h�E�̐������o�^
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = (WNDPROC)WndProc; // �R�[���o�b�N�֐��̎w��
	windowClass.lpszClassName = "Dx11";			// �A�v���P�[�V������
	windowClass.hInstance = GetModuleHandle(0);	// �n���h���̎w��
	RegisterClassEx(&windowClass);				// �A�v���P�[�V�����N���X
	RECT wrc = { 0,0,m_Width, m_Height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// �E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(windowClass.lpszClassName,	// �N���X��
		"�Q�[���A�v��",								// �^�C�g���o�[
		WS_OVERLAPPEDWINDOW,						// �E�B���h�E�^�C�v
		CW_USEDEFAULT, CW_USEDEFAULT,				// �\��xy���W��OS�ɔC����
		wrc.right - wrc.left, wrc.bottom - wrc.top, // �E�B���h�E���ƍ���
		NULL, NULL, windowClass.hInstance, NULL);	// �E�B���h�E�n���h��, ���j���[�n���h��,�Ăяo���A�v���P�[�V�����n���h��, �ǉ��p�����[�^
}

Application & Application::Instance()
{
	static Application instance;
	return instance;
}

bool Application::Init(HINSTANCE hInstance)
{
	auto result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	CreateGameWindow(m_hwnd, m_WindowClass); // �Q�[���E�B���h�E
	InputDevice::Init(hInstance, m_hwnd);	 // �R���g���[���̏�����
	return true;
}

void Application::AppRun()
{
	// �E�B���h�E�\��
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
	
	// �t���[�����[�g�̏�����
	Fps& fps = Fps::Instance();
	fps.Init();
	//Manager::Init();

	// ���b�Z�[�W���[�v
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(fps.Update())
			{
				// �X�V����
				InputDevice::Update(); // �R���g���[���̍X�V
				//Manager::Update();
				// �`�揈��
				//Manager::Draw();
			}
		}
	}

//	Manager::Uninit();
	fps.Uninit();
	InputDevice::Uninit();  // �R���g���[���̏I������ 
	timeEndPeriod(1);		// ����\��߂�
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // �E�B���h�E�N���X�̓o�^������
}

SIZE Application::GetWindowSize() const
{
	SIZE ret;
	ret.cx = m_Width;
	ret.cy = m_Height;
	return ret;
}

HWND Application::Gethwnd() const
{
	return m_hwnd;
}
#pragma endregion Application�N���X�̊֐�