/*--------------------------------------------------------------

	[Scene.h]
	�V�[���֘A�̏������Ǘ�
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Scene.h"
#include "Bg.h"
#include "InputDevice.h"
#include "Manager.h"

// �Q�[���V�[��
#pragma region Game_Func
// ���[�h
void GameScene::Game::Load()
{

}

// �A�����[�h
void GameScene::Game::Unload()
{
}

// ������
void GameScene::Game::Init()
{
	AddGameObject<DrawBg::Game>(LAYER_2D);
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

// �^�C�g���V�[��
#pragma region Title_Func
void GameScene::Title::Load()
{
}

void GameScene::Title::Unload()
{
}

void GameScene::Title::Init()
{
	AddGameObject<DrawBg::Title>(LAYER_2D);
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
