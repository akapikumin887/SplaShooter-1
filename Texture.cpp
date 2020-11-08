/*-----------------------------------------------------------

	[Texture.cpp]
	Author : �o���đ�

------------------------------------------------------------*/
#include "Texture.h"
#include "Engine.h"

#pragma region Texture_Func
// ���[�h
unsigned int Texture::Load(Wrapper::DirectX11& dx, std::string FileName)
{
	m_ImageCount++;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName.c_str(), NULL, NULL, &m_Texture, NULL);
	return m_ImageCount;
}

// �A�����[�h
void Texture::Unload()
{
	SAFE_RELEASE(m_Texture);
}

// �Z�b�g
ID3D11ShaderResourceView* Texture::SetTexture()
{
	return m_Texture;
}
#pragma endregion Texture�N���X�̊֐���`
