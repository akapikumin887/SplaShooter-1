/*----------------------------------------------------------

	[SettingShader.h]
	Author : �o���đ�

-----------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Shader.h"

// �Q�[���V�[���ȊO�ŃV�F�[�_�[���Z�b�g����Ƃ�
class SettingShader : public GameObject
{
private:
	Shader* m_Shader = NULL;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
