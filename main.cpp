/*---------------------------------------------------------

	[main.cpp]
	Author : �o���đ�

----------------------------------------------------------*/
#include <Windows.h>
#include "Application.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = Application::Instance();
	if (!app.Init(hInstance))
	{
		return -1;
	}
	app.AppRun();
	return 0;
}
