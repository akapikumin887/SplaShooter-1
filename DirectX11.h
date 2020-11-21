/*---------------------------------------------------------

	[DirectX11.h]
	DirectX11�֘A�̏���
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <stdio.h>
#include <windows.h>
#include <assert.h> // �G���[����
#include <iostream>

#pragma warning(push)
#pragma warning(disable:4005)

// DirectX��API
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
// �Z�p���C�u����
#include <DirectXMath.h>
// �V�F�[�_�[�̃R���p�C��
#include <d3dcompiler.h>

#pragma warning(pop)

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

// �����^�C���G���[�}�N��
#define STRINGFY(s)  #s
#define TO_STRING(x) STRINGFY(x)
#define FILE_PREFIX __FILE__ "(" TO_STRING(__LINE__) "): " 
#define ThrowIfFailed(hr, msg) Utility::CheckResultCode( hr, FILE_PREFIX msg)

namespace Utility
{
	class Exception : public std::runtime_error
	{
	public:
		Exception(const std::string& msg) : std::runtime_error(msg.c_str()) {}
	};

	inline void CheckResultCode(HRESULT hr, const std::string& errorMsg)
	{
		if (FAILED(hr))
		{
			throw Exception(errorMsg);
		}
	}
}

// DirectX11�̃��b�p�[
namespace Wrapper
{
	// ���_�\����
	struct VERTEX_3D
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR4 Diffuse;
		D3DXVECTOR2 TexCoord;
	};

	// �}�e���A���\����
	struct MATERIAL
	{
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emission;
		float		Shininess;
		float		Dummy[3];//16byte���E�p
	};

	// �}�e���A���\����
	struct DX11_MODEL_MATERIAL
	{
		MATERIAL		Material;
		class Texture*	Texture;
	};

	// �`��T�u�Z�b�g�\����
	struct DX11_SUBSET
	{
		DX11_MODEL_MATERIAL	Material;
		unsigned __int32	StartIndex;
		unsigned __int32	IndexNum;
	};

	// ���C�g�\����
	struct LIGHT
	{
		BOOL		Enable;
		BOOL		Dummy[3];//16byte���E�p
		D3DXVECTOR4	Direction;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Ambient;
	};

	// DirectX11
	class DirectX11
	{
	private:
		ID3D11Device*				m_Device = nullptr;
		ID3D11DeviceContext*		m_ImmediateContext = nullptr;
		IDXGISwapChain*				m_SwapChain = nullptr;
		ID3D11RenderTargetView*		m_RenderTargetView = nullptr;
		ID3D11DepthStencilView*		m_DepthStencilView = nullptr;
		ID3D11Buffer*				m_WorldBuffer = nullptr;
		ID3D11Buffer*				m_ViewBuffer = nullptr;
		ID3D11Buffer*				m_ProjectionBuffer = nullptr;
		ID3D11Buffer*				m_MaterialBuffer = nullptr;
		ID3D11Buffer*				m_LightBuffer = nullptr;
		ID3D11Buffer*				m_CameraBuffer = nullptr;
		ID3D11Buffer*				m_ParameterBuffer = nullptr;
		ID3D11DepthStencilState*	m_DepthStateEnable = nullptr;
		ID3D11DepthStencilState*	m_DepthStateDisable = nullptr;

		// private�R���X�g���N�^
		DirectX11() {}
		// �R�s�[�Ƒ�����֎~
		DirectX11(const DirectX11&) = delete;
		void operator= (const DirectX11&) = delete;
	public:
		static DirectX11& Instance();
		void Init();
		void Uninit();
		void Begin();
		void End();
		void SetDepthEnable(bool Enable);
		void SetWorldViewProjection2D();
		void SetWorldMatrix(D3DXMATRIX * WorldMatrix);
		void SetViewMatrix(D3DXMATRIX * ViewMatrix);
		void SetProjectionMatrix(D3DXMATRIX * ProjectionMatrix);
		void SetMaterial(MATERIAL Material);
		void SetLight(LIGHT Light);
		void SetCameraPosition(D3DXVECTOR3 CameraPosition);
		void SetParameter(D3DXVECTOR4 Parameter);

		// �V�F�[�_�[����
		void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** InputLayout, const char* FileName);
		void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

		ID3D11Device* GetDevice() { return m_Device; }
		ID3D11DeviceContext* GetDeviceContext() { return m_ImmediateContext; }
	};
}