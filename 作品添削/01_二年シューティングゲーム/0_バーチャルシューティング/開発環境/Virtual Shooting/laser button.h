//=============================================================================
//
//	���[�U�[�{�^��[laser button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LASER_BUTTON_H_
#define _LASER_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button.h"
#include "player.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLaserButton :public CButton
{
public:

	CLaserButton(int nPriorit = PRIORITY_UI_1);	//�R���X�g���N�^
	~CLaserButton();								//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CLaserButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


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
