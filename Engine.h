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
		static Prefabs::PrefabsTexture* m_Texture;
	public:
		static void Init();
		static void Uninit();
		static void Update();
		static void Draw();
		static ID3D11ShaderResourceView* GetTexture(unsigned int Id);
	};
}
