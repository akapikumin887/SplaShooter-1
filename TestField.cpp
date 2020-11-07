#include "TestField.h"
#include "Shader.h"
#include "Object3D.h"

void TestField::CreateVertex(Wrapper::VERTEX_3D Vertex[4])
{
	Vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	Vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	
	Vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	Vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[1].TexCoord = D3DXVECTOR2(10.0f, 0.0f);
	
	Vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	Vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[2].TexCoord = D3DXVECTOR2(0.0f, 10.0f);
	
	Vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	Vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex[3].TexCoord = D3DXVECTOR2(10.0f, 10.0f);
}

void TestField::Init()
{
	auto& dx = Wrapper::DirectX11::Instance();
	Wrapper::VERTEX_3D vertex[4];
	CreateVertex(vertex);
	// ���C���X�^���X����
	m_Object = new Object3D(dx,vertex);
	// �V�F�[�_�[�̓ǂݍ���
	// ����ʐ^���Â̌���
	//m_Shader = new Shader("MappingVS.cso", "MappingPS.cso");
	m_Shader = new Shader("vertexShader.cso", "pixelShader.cso");

	// �e�N�X�`���̓ǂݍ���
	m_TextureStorge[1] = m_Texture[0].Load(dx, "Asset/Texture/field004.jpg");
	m_TextureStorge[1] = m_Texture[1].Load(dx, "Asset/Texture/waffuru.tif");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestField::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		m_Texture[i].Unload(m_TextureStorge[i]);
	}
	delete m_Shader;
	delete m_Object;
}

void TestField::Update()
{
}

void TestField::Draw()
{
	auto & dx = Wrapper::DirectX11::Instance();
	// �V�F�[�_�[�̕`��
	m_Shader->Draw();
	// �e�N�X�`����ݒ�
	for (int i = 0; i < 2; i++)
	{
		m_Object->SetTexture(dx, i, m_Texture[i].SetTexture(m_TextureStorge[i]));
	}
	// �`��
	m_Object->Draw(dx,m_Position,m_Position,m_Scale);
}
