//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	continuebutton.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "continuebutton.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CContinueButton::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CContinueButton::CContinueButton()
  : CButton(3)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinueButton::~CContinueButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CContinueButton::Load(void)
{
    CRenderer* pRenderer      = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    // �e�N�X�`���̐���
    D3DXCreateTextureFromFile(pDevice,                        // �f�o�C�X�ւ̃|�C���^
                              "Data/Texture/continue.png",    // �t�@�C���̖��O
                              &m_pTexture);                   // �ǂݍ��ރ������[
    return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CContinueButton::Unload(void)
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
CContinueButton* CContinueButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CContinueButton* pRetryButton = NULL;
    pRetryButton                  = new CContinueButton;
    pRetryButton->SetPos(pos);
    pRetryButton->SetSize(size);
    pRetryButton->Init();
    return pRetryButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CContinueButton::Init(void)
{
    BindTexture(m_pTexture);    //�e�N�X�`���̊��蓖��
    CButton::Init();
    return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CContinueButton::Uninit(void)
{
    CButton::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CContinueButton::Update(void)
{
    CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CContinueButton::Draw(void)
{
    CButton::Draw();
}

void CContinueButton::Push(void)
{
    //�T�E���h�̎擾
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
    SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	while(ShowCursor(false)>=0);
    CManager::EndPause();
}

void CContinueButton::Select(void)
{
    //�T�E���h�̎擾
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
}

void CContinueButton::Unselect(void)
{
    SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
