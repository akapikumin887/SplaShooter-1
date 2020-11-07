/*-----------------------------------------------------------

	[Object3D.h]

	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

class Object3D
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
public:
	Object3D() = delete; // ��̃R���X�g���N�^���Ă΂Ȃ��悤��
	Object3D(Wrapper::DirectX11& dx, Wrapper::VERTEX_3D Vertex[4]);
	~Object3D();
	// Slot = �Z�b�g����X���b�g��,Texture = �e�N�X�`��
	void SetTexture(Wrapper::DirectX11 & instance, int Slot, ID3D11ShaderResourceView* Texture);
	void Draw(Wrapper::DirectX11& instance, D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale);
};

