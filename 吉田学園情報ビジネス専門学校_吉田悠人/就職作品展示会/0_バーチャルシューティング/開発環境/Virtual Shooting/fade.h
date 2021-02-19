//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _FADE_H
#define _FADE_H
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_FADE	(3)
#define FADE_RATE	(0.03f)

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include"main.h"
#include"manager.h"

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		//�����Ȃ����
		FADE_IN,			//�t�F�[�h����
		FADE_OUT,			//�t�F�[�h�A�E�g����
		FADE_MAX
	}FADE;

	CFade();
	~CFade();
	static CFade *Create(void);		// �쐬����
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	SetFade(GAME_MODE mode);		// �t�F�[�h�ݒ�
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	GAME_MODE	m_ModeNext;					//���̉�ʁi���[�h�j
	D3DXCOLOR	m_Color;				//�t�F�[�h�F
	FADE		m_Fade;					//�t�F�[�h���
};

#endif