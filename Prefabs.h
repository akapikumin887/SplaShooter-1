/*-----------------------------------------------------------

	[Prefabs.h]
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include <vector>

#pragma region BaseClass_PrefabsBase
class PrefabsBase
{
protected:
	std::vector<unsigned int> m_Id;
	virtual void Create(int size) {};
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
		class Loader::Texture* m_Texture;
		void Create(int size)override; // size = ���v���n�u�̐�
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

	class VertexShader : public PrefabsBase
	{
	private:
		Loader::VertexShader* m_VertexShader;
		void Create(int size)override;
		void Destory()override;
	public:
		enum ID : int
		{

		};
		void Load(Wrapper::DirectX11& dx)override;
		void Unload()override;
		ID3D11VertexShader* GetVertexShader(unsigned int Id);
		ID3D11InputLayout* GetInputLayout(unsigned int Id);
	};
}
#pragma endregion Prefabs���܂Ƃ߂�����
