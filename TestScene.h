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
	static void TestMap2(); // 2
};


namespace Test
{
	// �e�X�g�̎��s
	inline void Run()
	{
		ChangeScene::TestMap1();
		ChangeScene::TestMap2();
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

	class TestMap2 : public TestMap1
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}

