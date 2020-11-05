/*----------------------------------------------------------

	[TestScene.h]
	Author : �o���đ�

-----------------------------------------------------------*/
#pragma once
#include "Scene.h"

// �w��̃e�X�g�}�b�v�փV�[���`�F���W����֐����܂Ƃ߂�
struct ChangeScene
{
	static void ReturnTitle(); // �^�C�g���ɖ߂�
	static void TestMap1(); // �P
};


namespace Test
{
	// �e�X�g�̎��s
	inline void Run()
	{
		ChangeScene::TestMap1();
	}

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

