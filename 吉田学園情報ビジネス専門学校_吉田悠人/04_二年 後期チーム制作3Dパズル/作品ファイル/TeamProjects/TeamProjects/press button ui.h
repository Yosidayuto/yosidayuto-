//=============================================================================
//
//	�v���X�{�^��UI[press button ui.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _PRESS_BUTTON_H_
#define _PRESS_BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "inputmouse.h"
#include "ui.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CPressUi :public CUi
{
public:

	CPressUi(int nPriority = PRIORITY_UI_0);	// �R���X�g���N�^
	~CPressUi();								// �f�X�g���N�^
	static CPressUi*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT		 Init(void);			// ����������
	void		 Update(void);			// �X�V����

private:
	const int m_nTexture = 40;			// �e�N�X�`���ԍ�


};
#endif
