/*-----------------------------------------------------------

	[Polygon3D.cpp]
	Author : �o���đ�

------------------------------------------------------------*/
#include "DirectX11.h"
#include "Polygon3D.h"

Polygon3D::Polygon3D(Wrapper::DirectX11& dx, Wrapper::VERTEX_3D Vertex[4])
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Wrapper::VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = Vertex;
	dx.GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

Polygon3D::~Polygon3D()
{
	m_VertexBuffer->Release();
	m_VertexBuffer = NULL;
}

void Polygon3D::DrawPolygon(Wrapper::DirectX11& dx, D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale)
{
	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	dx.SetWorldMatrix(&world);
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Wrapper::VERTEX_3D);
	UINT offset = 0;
	dx.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// �}�e���A���ݒ�
	Wrapper::MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	dx.SetMaterial(material);

	// �v���~�e�B�u�g�|���W�ݒ�
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	dx.GetDeviceContext()->Draw(4, 0);
}
