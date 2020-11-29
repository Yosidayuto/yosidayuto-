//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	continuebutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _CONTINUEBUTTON_H_
#define _CONTINUEBUTTON_H_
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
class CContinueButton : public CButton
{
public:
    CContinueButton();
    ~CContinueButton();
    static HRESULT Load(void);
    static void Unload(void);
    static CContinueButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
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
