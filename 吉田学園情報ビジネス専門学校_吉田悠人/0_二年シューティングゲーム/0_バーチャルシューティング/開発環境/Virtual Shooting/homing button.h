//=============================================================================
//
//	�z�[�~���O�{�^��[homing button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _HOMING_BUTTON_H_
#define _HOMING_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CHomingButton :public CButton
{
public:

	CHomingButton(int nPriorit = PRIORITY_UI_1);	//�R���X�g���N�^
	~CHomingButton();								//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CHomingButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT			Init(void);		// ����������
	void			Uninit(void);	// �I������
	void			Update(void);	// �X�V����
	void			Draw(void);		// �`�揈��
	void			MouseOver(void);// �}�E�X�I�[�o�[����
	void			Push(void);		// �v�b�V�����菈��
private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
