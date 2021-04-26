//=============================================================================
//
//	�Z���tNo.3[talk no3.h]
//	Author:����@�r�H
//
//=============================================================================

// ��d�C���N���[�h�h�~
#ifndef _TALK_NO3_H_
#define _TALK_NO3_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "talk_base.h"

//====================================
// �O���錾
//====================================
class CTutorial;
class CChild;
//=============================================================================
// �N���X��`
//=============================================================================
class CTalkNo3 :public CTalkbase
{
public:

	CTalkNo3(int nPriorit = PRIORITY_UI_0);	// �R���X�g���N�^
	static CTalkNo3* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT		Init(void);				// ����������
	void		Update(void);			// �X�V����
	void		Talk(void);				// �g�[�N��i�߂�֐�
protected:
	bool		m_bTutorial;	//�`���[�g���A�������X�C�b�`
	CTutorial*	m_pTutorial;	//�`���[�g���A���|�C���^
	CChild*		m_pChild;		//�`���C���h�u���b�N�̃|�C���^
	const int m_nTexture = 12;			// �e�N�X�`���ԍ�

};
#endif
