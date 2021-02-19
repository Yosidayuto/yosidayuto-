//=============================================================================
//
//	���C�t�{�^��[life button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LIFE_BUTTON_H_
#define _LIFE_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button.h"
#include "player.h"

//=============================================================================
//�O���錾
//=============================================================================
class CNumber;

//=============================================================================
// �N���X��`
//=============================================================================
class CLifeButton :public CButton
{
public:

	CLifeButton(int nPriorit = PRIORITY_UI_1);	//�R���X�g���N�^
	~CLifeButton();								//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CLifeButton*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT		Init(void);		// ����������
	void		Uninit(void);	// �I������
	void		Update(void);	// �X�V����
	void		Draw(void);		// �`�揈��
	void		MouseOver(void);// �}�E�X�I�[�o�[����
	void		Push(void);		// �v�b�V�����菈��
	bool		LifeUp(void);	// ���C�t�A�b�v����
	bool		LifeDown(void);	// ���C�t�_�E������
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
	static int	m_nScoreCount[PLAYER_LIFE_UP];			// �X�R�A�̏����
	int			m_LifeCount;			// ���C�t������	
};
#endif
