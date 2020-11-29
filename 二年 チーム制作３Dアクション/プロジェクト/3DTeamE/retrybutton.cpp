//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	retrybutton.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "retrybutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CRetryButton::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRetryButton::CRetryButton() :CButton(3)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRetryButton::~CRetryButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CRetryButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/retry.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CRetryButton::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CRetryButton * CRetryButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CRetryButton* pRetryButton = NULL;
	pRetryButton = new CRetryButton;
	pRetryButton->SetPos(pos);
	pRetryButton->SetSize(size);
	pRetryButton->Init();
	return pRetryButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CRetryButton::Init(void)
{
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CRetryButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CRetryButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CRetryButton::Draw(void)
{
	CButton::Draw();
}

void CRetryButton::Push(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::GetFade()->SetFade(CManager::GetMode());
}

void CRetryButton::Select(void)
{
	//�T�E���h�̎擾
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
}

void CRetryButton::Unselect(void)
{
	SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
