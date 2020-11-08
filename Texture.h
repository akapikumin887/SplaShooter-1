/*-----------------------------------------------------------

	[Texture.h]
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "Component.h"
#include "DirectX11.h"


// �e�N�X�`�����Ǘ�
class Texture
{
private:
	//unsigned int m_Id;
	unsigned int m_ImageCount = -1;
	ID3D11ShaderResourceView* m_Texture;
public:
	Texture();
	~Texture() {};
	unsigned int Load(Wrapper::DirectX11& dx, std::string FileName); // ���[�h
	//void Load(Wrapper::DirectX11& dx, std::string FileName);
	void Unload();
	ID3D11ShaderResourceView* SetTexture(); // �Z�b�g
};

/*
// �e�N�X�`�����Ǘ�
class Texture : public Component
{
private:
	static int m_MaxID;
	std::string m_FileName;
	ID3D11ShaderResourceView* m_Texture = NULL;
	void Load(std::string FileName);
public:
	void Init()override;
	void Uninit()override;
	void SetID(unsigned int id);
	int GetTextureId();
	void SetTextureName(std::string TextureName);
	ID3D11ShaderResourceView* GetTexture();
};*/
