//=============================================================================
//
//	�^�C�g�����S[title logo.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "inputmouse.h"
#include "ui.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CTitleLoge :public CUi
{
public:

	CTitleLoge(int nPriority = PRIORITY_UI_0);	// �R���X�g���N�^
	~CTitleLoge();								// �f�X�g���N�^
	static CTitleLoge*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT		 Init(void);			// ����������
	void		 Update(void);			// �X�V����

private:
	const int m_nTexture = 41;			// �e�N�X�`���ԍ�

};
#endif
