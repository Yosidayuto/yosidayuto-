//=============================================================================
//
// �A�T���g�{�^������ [assaultbutton.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "assaultbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAssaultButton::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAssaultButton::CAssaultButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAssaultButton::~CAssaultButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CAssaultButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/AR.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CAssaultButton::Unload(void)
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
CAssaultButton * CAssaultButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CAssaultButton* pAssaultButton = NULL;
	pAssaultButton = new CAssaultButton;
	pAssaultButton->SetPos(pos);
	pAssaultButton->SetSize(size);
	pAssaultButton->Init();

	return pAssaultButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CAssaultButton::Init(void)
{

	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CAssaultButton::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CAssaultButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CAssaultButton::Draw(void)
{
	CButton::Draw();
}

void CAssaultButton::Push(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::SetWeaponsMode(CManager::WEAPONS_MODE_AR);
	CManager::GetFade()->SetFade(CManager::MODE_MAP01);
}

void CAssaultButton::Select(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CAssaultButton::Unselect(void)
{
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 128));
}
