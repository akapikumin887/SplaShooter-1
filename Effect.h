/*---------------------------------------------------------

	[Effect.h]
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

namespace Effect
{
	// 2D���W
	struct Float2
	{
		float x;
		float y;
	};

	// 3D���W->�ꉞ���������
	struct float3
	{
		float x;
		float y;
		float z;
	};

	// ���̃G�t�F�N�g -> �|�X�g�G�t�F�N�g�ŕ\��
	class Water
	{
	private:
		// �G�t�F�N�g�̃p�����[�^
		struct Parameter
		{
			Float2 m_Screen;	// �X�N���[�����W
			float m_Speed;		// ����鑬�x
			float m_Distortion;	// �c�݂̋��x
		};
		Parameter m_Parameter;
		// �V�F�[�_�[
		ID3D11VertexShader* m_VertexShader = NULL;
		ID3D11PixelShader* m_PixelShader = NULL;
	public:
		void Init();
		void Uninit();
		void Render();	// �����_�����O
	};
};

