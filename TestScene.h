/*----------------------------------------------------------

	[TestScene.h]
	Author : �o���đ�

-----------------------------------------------------------*/
#pragma once
#include "Scene.h"

namespace Test
{
	// �w��̃e�X�g�}�b�v�փV�[���`�F���W����֐����܂Ƃ߂�
	struct ChangeScene
	{
		static void TestMap1(); // �P
	};

	// �e�X�g�V�[���P
	class TestMap1 : public Scene
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}

