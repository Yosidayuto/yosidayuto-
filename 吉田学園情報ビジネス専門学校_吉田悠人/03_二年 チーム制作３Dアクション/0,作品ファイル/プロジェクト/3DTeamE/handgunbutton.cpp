//=============================================================================
//
// �n���h�K���{�^������ [handgunbutton.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "handgunbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHandgunButton::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHandgunButton::CHandgunButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHandgunButton::~CHandgunButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CHandgunButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/HG.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CHandgunButton::Unload(void)
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
CHandgunButton * CHandgunButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CHandgunButton* pHandgunButton = NULL;
	pHandgunButton = new CHandgunButton;
	pHandgunButton->SetPos(pos);
	pHandgunButton->SetSize(size);
	pHandgunButton->Init();

	return pHandgunButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CHandgunButton::Init(void)
{
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CHandgunButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CHandgunButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CHandgunButton::Draw(void)
{
	CButton::Draw();
}

void CHandgunButton::Push(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::SetWeaponsMode(CManager::WEAPONS_MODE_HG);
	CManager::GetFade()->SetFade(CManager::MODE_MAP01);
}

void CHandgunButton::Select(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CHandgunButton::Unselect(void)
{
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 128));
}