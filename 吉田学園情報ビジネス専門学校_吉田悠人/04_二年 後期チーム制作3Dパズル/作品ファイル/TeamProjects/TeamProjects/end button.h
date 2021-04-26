//=============================================================================
//
//	�I���{�^��[end button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _END_BUTTONP_H_
#define _END_BUTTONP_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "button.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CEndButton :public CButton
{
public:

	CEndButton();		// �R���X�g���N�^
	~CEndButton();		// �f�X�g���N�^
	static CEndButton*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


	HRESULT		Init(void);		// ����������
	void		Uninit(void);	// �I������
	void		Update(void);	// �X�V����
	void		Draw(void);		// �`�揈��
	void		Push(void);		// �v�b�V�����菈��

private:
	const int m_nTexture = 1;			// �e�N�X�`���ԍ�
};
#endif
