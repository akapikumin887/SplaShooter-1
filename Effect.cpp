/*---------------------------------------------------------

	[Effect.cpp]
	Author : �o���đ�

----------------------------------------------------------*/
#include "Effect.h"
#include "Application.h"

void Effect::Water::Init()
{
	auto& app = Application::Instance();
	m_Parameter.m_Screen.x = app.GetWindowSize().cx;
	m_Parameter.m_Screen.y = app.GetWindowSize().cy;
	m_Parameter.m_Speed = 5.0f;
	m_Parameter.m_Distortion = 5.0f;
	
	// �V�F�[�_�[����->�R���p�C���p�̊֐�������Ίy�ɂȂ�H

}

void Effect::Water::Uninit()
{
}

void Effect::Water::Render()
{
	auto& dx = Wrapper::DirectX11::Instance();
	// �S��ʃ|���S���̕`��
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}
