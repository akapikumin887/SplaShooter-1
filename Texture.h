/*-----------------------------------------------------------

	[Texture.h]
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

// �e�N�X�`�����Ǘ�
class Texture
{
private:
	unsigned int m_ImageCount = 0;
	ID3D11ShaderResourceView* m_Texture[32];
public:
	Texture();
	~Texture() {};
	unsigned int Load(Wrapper::DirectX11& dx, const char* FileName); // ���[�h
	void Unload(unsigned int Texture);
	ID3D11ShaderResourceView* SetTexture(unsigned int Texture); // �Z�b�g
};
