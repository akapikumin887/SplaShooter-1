/*----------------------------------------------

	[ModelManager.h]
	Author : �o���đ�

-----------------------------------------------*/
#pragma once

#include <map>
#include <vector>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

#pragma comment (lib,"assimp.lib")

#include "DirectX11.h"

// �X�^�e�B�b�N���b�V��
namespace StaticMesh
{
	// �}�e���A��
	struct Material
	{
		char m_Name[256];
		char m_TextureName[256];
		ID3D11ShaderResourceView* m_Texture;
		Wrapper::MATERIAL m_Material;
	};

	// �`��T�u�Z�b�g
	struct Subset
	{
		unsigned __int32 m_StartIndex;
		unsigned __int32 m_IndexNum;
		Material m_Material;
	};

	// ���b�V��
	struct Mesh
	{
		unsigned __int32 m_VertexNum;
		unsigned __int32* m_IndexArray;
		unsigned __int32 m_IndexNum;
		unsigned __int32 m_SubsetNum;
		Subset* m_SubsetArray;
		Wrapper::VERTEX_3D* m_VertexArray;
	};

	// ���f��
	class Model
	{
	private:
		unsigned __int32 m_SubsetNum;
		ID3D11Buffer* m_VertexBuffer;
		ID3D11Buffer* m_IndexBuffer;
		Subset* m_SubsetArray;
		Wrapper::DirectX11& m_dx = Wrapper::DirectX11::Instance();

		void LoadObject(const char* FileName, Mesh* Mesh);
		void LoadMaterial(const char* FileName, Material** MaterialArray, unsigned __int32* MaterialNum);
	public:
		void Load(const char* FileName);
		void Unload();
		void Draw();
		D3DXCOLOR GetColor() { return m_SubsetArray->m_Material.m_Material.Diffuse; }
		void SetColor(D3DXCOLOR Color) { m_SubsetArray->m_Material.m_Material.Diffuse = Color; }
	};
}