//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	button.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CButton::CButton(int nPriority)
  : CObject2D(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CButton::~CButton()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CButton::Init(void)
{
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    CObject2D::Init();
    return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CButton::Uninit(void)
{
    CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CButton::Update(void)
{
    D3DXVECTOR3 pos  = GetPos();
    D3DXVECTOR3 size = GetSize();
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
    CObject2D::Update();
    if(point.x > pos.x - size.x / 2 && point.x < pos.x + size.x / 2 && point.y > pos.y - size.y / 2 && point.y < pos.y + size.y / 2)
    {
        //�傫�����鏈��
        Select();
        if(((CInputMouse*)CManager::GetInputMou())->GetKeyTrigger(CInputMouse::MOUSE_LEFT))
        {
            Push();
        }
    }
    else
    {
        Unselect();
    }
}

//=============================================================================
// �`��֐�
//=============================================================================
void CButton::Draw(void)
{
    CObject2D::Draw();
}
