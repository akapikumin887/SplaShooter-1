/*-----------------------------------------------------------

	[Shader.cpp]
	Author : �o���đ�

------------------------------------------------------------*/
#include "Shader.h"
#include <io.h>

#pragma region Shader_Func
// ���_�V�F�[�_�[����
void Shader::CreateVertexShader(Wrapper::DirectX11& dx, ID3D11VertexShader ** VertexShader, ID3D11InputLayout ** VertexLayout, const char * FileName)
{
	FILE* file;
	long int fsize;
	file = fopen(FileName, "rb");
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
	dx.GetDevice()->CreateInputLayout(layout, numElements, buffer, fsize, VertexLayout);
	delete[] buffer;
}

// �s�N�Z���V�F�[�_�[����
void Shader::CreatePixelShader(Wrapper::DirectX11& dx, ID3D11PixelShader ** PixelShader, const char * FileName)
{
	FILE* file;
	long int fsize;
	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);
	dx.GetDevice()->CreatePixelShader(buffer, fsize, NULL, PixelShader);
	delete[] buffer;
}

// �R���X�g���N�^
Shader::Shader(const char * VertexShader_FileName, const char * PixelShader_FileName)
{
	auto& dx = Wrapper::DirectX11::Instance();
	CreateVertexShader(dx, &m_VertexShader, &m_InputLayout, VertexShader_FileName);
	CreatePixelShader(dx, &m_PixelShader, PixelShader_FileName);
}

// �f�X�g���N�^
Shader::~Shader()
{
	m_InputLayout->Release();
	m_InputLayout = NULL;
	m_VertexShader->Release();
	m_VertexShader = NULL;
	m_PixelShader->Release();
	m_PixelShader = NULL;
}

// �`��
void Shader::Draw()
{
	auto& dx = Wrapper::DirectX11::Instance();
	dx.GetDeviceContext()->IASetInputLayout(m_InputLayout);
	dx.GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	dx.GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
}
#pragma endregion Shader�N���X�̊֐���` 
