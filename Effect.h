/*---------------------------------------------------------

	[Effect.h]
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#include "DirectX11.h"

namespace Effect
{
	struct Float2
	{
		float x;
		float y;
	};
	class Water
	{
	private:
		struct Parameter
		{
			Float2 m_Screen;
			float m_Speed;		// ����鑬�x
			float m_Distortion;	// �c�݂̋��x
		};
		Parameter m_Parameter;
		ID3D11VertexShader* m_VertexShader = NULL;
		ID3D11PixelShader* m_PixelShader = NULL;
	public:
		void Init();
		void Uninit();
		void Render();
	};
};

