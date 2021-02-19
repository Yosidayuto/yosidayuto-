//=============================================================================
//
//	�o���b�g�{�^��[bullet button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _BULLET_BUTTON_H_
#define _BULLET_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBulletButton :public CButton
{
public:

	CBulletButton(int nPriorit = PRIORITY_UI_1);	//�R���X�g���N�^
	~CBulletButton();								//�f�X�g���N�^
	static HRESULT			Load(void);
	static void				Unload(void);
	static CBulletButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


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
