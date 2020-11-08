/*-----------------------------------------------------------

	[Prefabs.h]
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Loader.h"

#pragma region BaseClass_PrefabsBase
class PrefabsBase
{
protected:
	static const unsigned int m_Maxid = 256; // �z��̗v�f��
	unsigned int m_Id[m_Maxid];	// ID�̊i�[
	int m_Size; // �v���n�u�̐�

	//�@����
	virtual void Create(int size) {}; // size = ���v���n�u�̐�
	//�@�j��
	virtual void Destory() {};
public:
	virtual void Load(Wrapper::DirectX11& dx) = 0;
	virtual void Unload() = 0;
};
#pragma endregion Prefabs�̊��N���X

#pragma region Prefabs_Wrapper
namespace Prefabs
{
	// Texture�̃v���n�u
	class Texture : public PrefabsBase
	{
	private:
		Loader::Texture* m_Texture;
		void Create(int size)override; 
		void Destory()override;
	public:
		enum ID : int
		{
			FADE,
			TATILE_BG,
			GAME_BG
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11ShaderResourceView* GetTexture(unsigned int Id);
	};

	// ���_�V�F�[�_�[
	class VertexShader : public PrefabsBase
	{
	private:
		Loader::VertexShader* m_VertexShader;
		void Create(int size)override;
		void Destory()override;
	public:
		enum ID : int
		{
			DEFAULT,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11VertexShader* GetVertexShader(unsigned int Id);
		ID3D11InputLayout* GetInputLayout(unsigned int Id);
	};

	// �s�N�Z���V�F�[�_�[
	class PixelShader : public PrefabsBase
	{
	private:
		Loader::PixelShader* m_PixelShader;
		void Create(int size)override;
		void Destory();
	public:
		enum ID : int 
		{
			DEFAULT,
		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11PixelShader* GetPixelShader(unsigned int Id);
	};
}
#pragma endregion Prefabs���܂Ƃ߂�����
