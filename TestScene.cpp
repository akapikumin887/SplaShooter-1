#include "TestScene.h"
#include "Manager.h"
#include "InputDevice.h"
#include "TestPlayer.h"
#include "Camera.h"
#include "Effect.h"
#include "TestField.h"
#include "Test.h"

// ��ʑJ��
void ChangeScene::ReturnTitle()
{
	if (KeyBoard::IsTrigger(DIK_R))
	{
		Manager::SetScene<GameScene::Title>();
	}
}

void ChangeScene::TestMap1()
{
	if (KeyBoard::IsTrigger(DIK_1))
	{
		Manager::SetScene<Test::TestMap1>();
	}
}

void ChangeScene::TestMap2()
{
	if (KeyBoard::IsTrigger(DIK_2))
	{
		Manager::SetScene<Test::TestMap2>();
	}
}

// �e�X�g�}�b�v�P
void Test::TestMap1::Init()
{
	AddGameObject<Camera>(LAYER_CAMERA);
	AddGameObject<TestField>(LAYER_3D);
}

void Test::TestMap1::Uninit()
{
	Scene::Uninit();
}

void Test::TestMap1::Update()
{
	Scene::Update();
	ChangeScene::ReturnTitle();
}

void Test::TestMap1::Draw()
{
	Scene::Draw();
}

// �e�X�g�}�b�v�Q
void Test::TestMap2::Init()
{
	AddGameObject<Camera>(LAYER_CAMERA);
	AddGameObject<Test_Chinapan::Field>(LAYER_3D);
}

void Test::TestMap2::Uninit()
{
	TestMap1::Uninit();
}

void Test::TestMap2::Update()
{
	TestMap1::Update();
}

void Test::TestMap2::Draw()
{
	TestMap1::Draw();
}
