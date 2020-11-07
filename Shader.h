/*-----------------------------------------------------------

	[Shader.h]
	�V�F�[�_�[�ɕK�v�Ȃ��̂��܂Ƃ߂�
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#include "DirectX11.h"
#include "GameObject.h"

// �V�F�[�_�[�\����
class Shader
{
private:	
	// �V�F�[�_�[
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11InputLayout*	m_InputLayout = NULL;
	ID3D11PixelShader*	m_PixelShader = NULL;

	// �V�F�[�_�[����
	void CreateVertexShader(Wrapper::DirectX11& dx, ID3D11VertexShader** VertexShader, ID3D11InputLayout** InputLayout, const char* FileName);
	void CreatePixelShader(Wrapper::DirectX11& dx, ID3D11PixelShader** PixelShader, const char* FileName);
public:
	Shader() = delete; // ��̃R���X�g���N�^���Ă΂Ȃ��悤��
	Shader(const char* VertexShader_FileName, const char* PixelShader_FileName);
	~Shader();
	void Draw();
};
