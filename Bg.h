/*----------------------------------------------------------

	[Bg.h]
	�w�i�Ɋւ���N���X���܂Ƃ߂�
	Author : �o���đ�

-----------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "DirectX11.h"
#include "Fps.h"

// �w�i�`��p�Ɋ��N���X
class Bg : public GameObject
{
protected:
	D3DXVECTOR2 m_Scrren;
	SpriteRenderer m_Sprite;
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	D3DXVECTOR2 GetScrren(); // �X�N���[���T�C�Y�̃Q�b�^�[
};

// �t�F�[�h
class Fade : public Bg
{
private:
	float m_Alpha = 1.0f;	// a�l
	float m_FadeTime;
	Fps& m_Fps;
public:
	enum FadeState : int
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};
	FadeState m_FadeState = FADE_NONE;
	static class Scene* m_NextScene;
	
	Fade() : m_Fps(Fps::Instance()) {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

// �w�i�̕`��
namespace DrawBg
{
	// �^�C�g���w�i
	class Title : public Bg
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
	// �Q�[���w�i
	class Game : public Bg
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}