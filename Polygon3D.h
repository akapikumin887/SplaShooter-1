/*-----------------------------------------------------------

	[Object3D.h]

	Author : �o���đ�

------------------------------------------------------------*/
#pragma once

class Polygon3D
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
public:
	Polygon3D() = delete; // ��̃R���X�g���N�^���Ă΂Ȃ��悤��
	Polygon3D(Wrapper::DirectX11& dx, Wrapper::VERTEX_3D Vertex[4]);
	~Polygon3D();
	void Draw(Wrapper::DirectX11& instance, D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale);
	//void DrawPolygon(Wrapper::DirectX11 & instance);
};

