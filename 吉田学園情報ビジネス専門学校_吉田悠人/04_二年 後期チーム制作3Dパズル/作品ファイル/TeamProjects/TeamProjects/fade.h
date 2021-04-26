//=============================================================================
//
// �t�F�[�h�x�[�X���� [fade base.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _FADE_BASE_H_
#define _FADE_BASE_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FADE_RATE	(0.03f)

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// �����Ȃ����
		FADE_IN,		// �t�F�[�h�C������
		FADE_OUT,		// �t�F�[�h�A�E�g����
		FADE_MAX
	}FADE;

	typedef enum
	{
		FADE_TYPE_MANAGER,
		FADE_TYPE_STAGE,
		FADE_TYPE_MAX
	}FADE_TYPE;


	CFade();						// �R���X�g���N�^
	~CFade();						// �f�X�g���N�^
	static CFade *Create(void);	// �쐬����

	HRESULT Init(void);				// ����������
	void	Uninit(void);			// �I������
	void	Update(void);			// �X�V����
	void	Draw(void);				// �`�揈��
	void	Fadeout(void);			// �Ó]����
	void	SetBlackout(CManager::MODE mode);	//�u���b�N�A�E�g����
	void	SetWhiteout(CGame::MAP_TYPE mode);	//�z���C�g�A�E�g����

	FADE    GetFade(void) { return m_fade; }	//�t�F�[�h�̏��������擾
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXCOLOR		m_color;				// �J���[
	FADE			m_fade;					// �t�F�[�h
	CManager::MODE	m_ManagerMode;			// �}�l�[�W���[���[�h
	CGame::MAP_TYPE m_StageMode;			// �X�e�[�W���[�h
	FADE_TYPE		m_FadeType;				// �t�F�[�h�^�C�v
};
#endif