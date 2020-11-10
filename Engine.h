/*-----------------------------------------------------------

	[Engine.h]
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "Prefabs.h"

// DirectX�f�o�C�X����}�N��
#define SAFE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)

namespace Engine
{
	// �I�u�W�F�N�g�v�[��
	class ObjectPool
	{
	private:
		static Prefabs::Texture* m_Texture;
		static Prefabs::VertexShader* m_VertexShader;
		static Prefabs::PixelShader* m_PixelShader;
	public:
		static void Init();
		static void Uninit();
		static void Update();
		static void Draw();
		// �e�N�X�`����Getter / Setter
		static ID3D11ShaderResourceView* GetTexture(unsigned int Id);
		static void SetTexture(Wrapper::DirectX11& dx, int slot, unsigned int Id); // slot = �ݒ肷��X���b�g�AID = �i�[ID

		// �V�F�[�_�[�̐ݒ�
		static void SetVertexShader(Wrapper::DirectX11& dx, unsigned int Id);
		static void SetInputLayout(Wrapper::DirectX11& dx, unsigned int Id);
		static void SetPixelShader(Wrapper::DirectX11& dx, unsigned int Id);
	};
}
