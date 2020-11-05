/*--------------------------------------------------------------

	[Scene.h]
	�V�[���֘A�̏������Ǘ�
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Scene.h"
#include "Bg.h"
#include "InputDevice.h"
#include "Manager.h"
#include "Camera.h"
#include "SettingShader.h"
#include "TestScene.h"

// �^�C�g���V�[��
#pragma region GameScene_Title_Func
void GameScene::Title::Init()
{
	AddGameObject<SettingShader>(LAYER_3D);
	AddGameObject<DrawBg::Title>(LAYER_2D_BG);
}

void GameScene::Title::Uninit()
{

}

void GameScene::Title::Update()
{
	Scene::Update();
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0, BTN_2))
	{
		Manager::SetScene<Game>();
	}
	Test::Run();
}

void GameScene::Title::Draw()
{
	Scene::Draw();
}
#pragma endregion Title�̃N���X�̊֐���`

// �Q�[���V�[��
#pragma region GameScene_Game_Func
// ������
void GameScene::Game::Init()
{
	AddGameObject<Camera>(LAYER_CAMERA);
	AddGameObject<DrawBg::Game>(LAYER_2D_BG);
}

void GameScene::Game::Uninit()
{

}

// �X�V
void GameScene::Game::Update()
{
	Scene::Update();
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0, BTN_2))
	{
		Manager::SetScene<Title>();
	}
}

// �`��
void GameScene::Game::Draw()
{
	Scene::Draw();
}
#pragma endregion Game�N���X�̊֐���`
