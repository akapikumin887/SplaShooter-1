/*---------------------------------------------------------

	[Effect.h]
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#include "DirectX11.h"
#include "Shader.h"

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
		Shader* m_Shader = NULL;
		// �G�t�F�N�g�̃p�����[�^
		struct Parameter
		{
			Float2 m_Screen;	// �X�N���[�����W
			float m_Speed;		// ����鑬�x
			float m_Distortion;	// �c�݂̋��x
		};
		Parameter m_Parameter;
	public:
		void Init();
		void Uninit();
		void Render();	// �����_�����O
	};
};

