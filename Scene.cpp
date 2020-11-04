/*--------------------------------------------------------------

	[Scene.h]
	�V�[���֘A�̏������Ǘ�
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Scene.h"
#include "Bg.h"
#include "InputDevice.h"
#include "Manager.h"

// �^�C�g���V�[��
#pragma region GameScene_Title_Func
void GameScene::Title::Init()
{
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

