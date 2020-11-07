#include "TestField.h"
#include "Shader.h"
#include "Object3D.h"

void TestField::Init()
{
	auto& dx = Wrapper::DirectX11::Instance();
	// ���C���X�^���X����
	m_Object = new Object3D;
	// �V�F�[�_�[�̓ǂݍ���
	//m_Shader = new Shader("normalMappingVS.cso", "normalMappingPS.cso");
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
