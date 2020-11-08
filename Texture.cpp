/*-----------------------------------------------------------

	[Texture.cpp]
	Author : �o���đ�

------------------------------------------------------------*/
#include "Texture.h"
#include "Engine.h"

#pragma region Texture_Func
Texture::Texture()
{
}

// ���[�h
unsigned int Texture::Load(Wrapper::DirectX11& dx, std::string FileName)
{
	m_ImageCount++;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName.c_str(), NULL, NULL, &m_Texture, NULL);
	return m_ImageCount;
}
/*
void Texture::Load(Wrapper::DirectX11 & dx, std::string FileName)
{
	unsigned int texture = 0;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName.c_str(), NULL, NULL, &m_Texture[m_ImageCount++], NULL);
	texture = m_ImageCount - 1;
}
*/
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

/*
int Texture::m_MaxID = -1;

void Texture::Load(std::string FileName)
{
	auto& dx = Wrapper::DirectX11::Instance();
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), m_FileName.c_str(), NULL, NULL, &m_Texture, NULL);
}

void Texture::Init()
{
	m_MaxID++;
	// �e�N�X�`�����v�[�����Ă��邱�Ƃ��瓯��ID�̃e�N�X�`����������
	Texture* p_texture = Engine::ObjectPool::GetTexture(m_Id);
	if (p_texture != nullptr)
	{
		if (p_texture->m_Id == m_Id)
		{
			m_FileName = p_texture->m_FileName;
			m_Texture = p_texture->m_Texture;
			m_MaxID--;
			return;
		}
	}
}

void Texture::Uninit()
{
	SAFE_RELEASE(m_Texture);
}

void Texture::SetID(unsigned int id)
{
	m_Id = id;
}

int Texture::GetTextureId()
{
	return m_Id;
}

void Texture::SetTextureName(std::string TextureName)
{
	m_FileName = TextureName;
}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return m_Texture;
}
*/