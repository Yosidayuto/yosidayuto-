//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	returntitlebutton.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "returntitlebutton.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CReturnTitleButton::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CReturnTitleButton::CReturnTitleButton()
  : CButton(3)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CReturnTitleButton::~CReturnTitleButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CReturnTitleButton::Load(void)
{
    CRenderer* pRenderer      = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    // �e�N�X�`���̐���
    D3DXCreateTextureFromFile(pDevice,                      // �f�o�C�X�ւ̃|�C���^
                              "Data/Texture/GiveUp.png",    // �t�@�C���̖��O
                              &m_pTexture);                 // �ǂݍ��ރ������[
    return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CReturnTitleButton::Unload(void)
{
    // �e�N�X�`���̔j��
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//=============================================================================
// �����֐�
//=============================================================================
CReturnTitleButton* CReturnTitleButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CReturnTitleButton* pReturnTitleButton = NULL;
    pReturnTitleButton                     = new CReturnTitleButton;
    pReturnTitleButton->SetPos(pos);
    pReturnTitleButton->SetSize(size);
    pReturnTitleButton->Init();

    return pReturnTitleButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CReturnTitleButton::Init(void)
{
    BindTexture(m_pTexture);    //�e�N�X�`���̊��蓖��
    CButton::Init();
    return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CReturnTitleButton::Uninit(void)
{
    CButton::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CReturnTitleButton::Update(void)
{
    CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CReturnTitleButton::Draw(void)
{
    CButton::Draw();
}

void CReturnTitleButton::Push(void)
{
    //�T�E���h�̎擾
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
    CManager::GetFade()->SetFade(CManager::MODE_TITLE);
}

void CReturnTitleButton::Select(void)
{
    //�T�E���h�̎擾
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CReturnTitleButton::Unselect(void)
{
    SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
