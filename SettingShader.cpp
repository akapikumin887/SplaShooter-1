/*----------------------------------------------------------
	
	[SettingShader.cpp]
	Author : �o���đ�

-----------------------------------------------------------*/
#include "SettingShader.h"

void SettingShader::Init()
{
	m_Shader = new Shader("Asset/Shader/vertexShader.cso", "Asset/Shader/pixelShader.cso");
}

void SettingShader::Uninit()
{
	delete m_Shader;
}

void SettingShader::Update()
{
}

void SettingShader::Draw()
{
	m_Shader->Draw();
}
