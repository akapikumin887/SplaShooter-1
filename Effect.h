/*---------------------------------------------------------

	[Effect.h]
	Author : 出合翔太

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
			float m_Speed;		// 流れる速度
			float m_Distortion;	// 歪みの強度
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

