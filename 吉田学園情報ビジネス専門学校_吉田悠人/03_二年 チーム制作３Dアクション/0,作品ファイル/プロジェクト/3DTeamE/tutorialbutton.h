//=============================================================================
//
// �`���[�g���A���{�^������[tutorialbutton.h]
// Author : ��K������
//
//=============================================================================
#ifndef _TUTORIALBUTTON_H_
#define _TUTORIALBUTTON_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "button.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorialButton :public CButton
{
public:
	CTutorialButton();
	~CTutorialButton();
	static HRESULT Load(void);
	static void Unload(void);
	static CTutorialButton * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Push(void);
	void Select(void);
	void Unselect(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_DefaultSize;
};
#endif