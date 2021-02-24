//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	returntitlebutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _RETURNTITLEBUTTON_H_
#define _RETURNTITLEBUTTON_H_
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
class CReturnTitleButton : public CButton
{
public:
    CReturnTitleButton();
    ~CReturnTitleButton();
    static HRESULT Load(void);
    static void Unload(void);
    static CReturnTitleButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void Push(void);
    void Select(void);
    void Unselect(void);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
};
#endif
