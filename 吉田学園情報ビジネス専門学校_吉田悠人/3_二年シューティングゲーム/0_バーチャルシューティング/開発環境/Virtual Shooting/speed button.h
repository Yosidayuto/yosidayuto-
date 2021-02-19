//=============================================================================
//
//	�X�s�[�h�{�^��[speed button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _SPEED_BUTTON_H_
#define _SPEED_BUTTON_H_

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
class CSpeedButton :public CButton
{
public:

	CSpeedButton(int nPriorit = PRIORITY_UI_1);	//�R���X�g���N�^
	~CSpeedButton();								//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CSpeedButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
	void			MouseOver(void);// �}�E�X�I�[�o�[����
	void			Push(void);		// �v�b�V�����菈��
	bool			SpeedUp(void);	// �X�s�[�h�A�b�v����
	bool			SpeedDown(void);// �X�s�[�h�_�E������
private:
	static TEXTURE_DATA	m_TextureData;			// �e�N�X�`���f�[�^
	static int	m_nScoreCount[PLAYER_LIFE_UP];	// �X�R�A�̏����
	int			m_SpeedCount;					// ���C�t������	
};
#endif
