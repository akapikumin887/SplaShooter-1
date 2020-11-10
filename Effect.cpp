/*---------------------------------------------------------

	[Effect.cpp]
	Author : �o���đ�

----------------------------------------------------------*/
#include "Effect.h"
#include "Application.h"

void Effect::Water::Init()
{
	m_Parameter.m_Speed = 5.0f;
	m_Parameter.m_Distortion = 5.0f;
	//m_Shader = new Shader("waterVS.cso", "waterPS.cso");

}

void Effect::Water::Uninit()
{
	//delete m_Shader;
}

void Effect::Water::Render()
{
	auto& app = Application::Instance();
	
	m_Parameter.m_Screen.x = app.GetWindowSize().cx;
	m_Parameter.m_Screen.y = app.GetWindowSize().cy;
	 

	m_Parameter.m_Speed -= 0.1f;
	m_Parameter.m_Distortion -= 0.1f;
	auto& dx = Wrapper::DirectX11::Instance();
	// �S��ʃ|���S���̕`��
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//m_Shader->Draw();
}
