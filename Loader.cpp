/*-----------------------------------------------------------

	[Loader.cpp]
	Author : �o���đ�

------------------------------------------------------------*/
#include "Loader.h"
#include "Engine.h"
#include <io.h>

#pragma region Loader_Texture_Func
// ���[�h
unsigned int Loader::Texture::Load(Wrapper::DirectX11& dx, std::string FileName)
{
	m_Count++;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName.c_str(), NULL, NULL, &m_Texture, NULL);
	return m_Count;
}

// �A�����[�h
void Loader::Texture::Unload()
{
	SAFE_RELEASE(m_Texture);
}

// �Z�b�g
ID3D11ShaderResourceView* Loader::Texture::GetTexture() const
{
	return m_Texture;
}
#pragma endregion Texture�N���X�̊֐���`

#pragma region Loader_VertexShader_Func
void Loader::VertexShader::CreateVertexShader(Wrapper::DirectX11 & dx, ID3D11VertexShader ** VertexShader, ID3D11InputLayout ** InputLayout, std::string FileName)
{
	FILE* file;
	long int fsize;
	file = fopen(FileName.c_str(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	dx.GetDevice()->CreateVertexShader(buffer, fsize, NULL, VertexShader);

	// ���̓��C�A�E�g����
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	dx.GetDevice()->CreateInputLayout(layout, numElements, buffer, fsize, InputLayout);
	delete[] buffer;
}

unsigned int Loader::VertexShader::Load(Wrapper::DirectX11 & dx, std::string VertexShader_FileName)
{
	m_Count++;
	CreateVertexShader(dx, &m_VertexShader, &m_InputLayout, VertexShader_FileName);
	return m_Count;
}


void Loader::VertexShader::Unload()
{
	m_InputLayout->Release();
	m_VertexShader->Release();
}

ID3D11VertexShader * Loader::VertexShader::GetVertexShader() const
{
	return m_VertexShader;
}

ID3D11InputLayout * Loader::VertexShader::GetInputLayout() const
{
	return m_InputLayout;
}
#pragma endregion Loader_VertexShader�N���X�̊֐���`

#pragma region Loader_PixelShader_Func
void Loader::pixelShader::CreatePixelShader(Wrapper::DirectX11 & dx, ID3D11PixelShader ** PixelShader, std::string FileName)
{
	FILE* file;
	long int fsize;
	file = fopen(FileName.c_str(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	dx.GetDevice()->CreatePixelShader(buffer, fsize, NULL, PixelShader);
	delete[] buffer;
}

unsigned int Loader::pixelShader::Load(Wrapper::DirectX11 & dx, std::string PixelShader_FileName)
{
	m_Count++;
	CreatePixelShader(dx, &m_PixelShader, PixelShader_FileName);
	return m_Count;
}

void Loader::pixelShader::Unload()
{
	m_PixelShader->Release();
}

ID3D11PixelShader * Loader::pixelShader::GetPixelShader() const
{
	return m_PixelShader;
}
#pragma endregion Loader_PixelShader�N���X�̊֐���`