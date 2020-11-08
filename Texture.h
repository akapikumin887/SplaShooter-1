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
	unsigned int m_ImageCount = -1;
	ID3D11ShaderResourceView* m_Texture;
public:
	Texture() {};
	~Texture() {};
	unsigned int Load(Wrapper::DirectX11& dx, std::string FileName); // ���[�h
	void Unload();
	ID3D11ShaderResourceView* SetTexture(); // �Z�b�g
};

