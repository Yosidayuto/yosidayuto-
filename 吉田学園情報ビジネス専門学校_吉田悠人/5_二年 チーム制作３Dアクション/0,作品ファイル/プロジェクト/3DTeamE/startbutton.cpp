//=============================================================================
//
// �X�^�[�g�{�^������ [startbutton.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "startbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CStartButton::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStartButton::CStartButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStartButton::~CStartButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CStartButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/gamestart.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CStartButton::Unload(void)
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
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CStartButton* pStartButton = NULL;
	pStartButton = new CStartButton;
	pStartButton->SetPos(pos);
	pStartButton->m_DefaultSize = size;
	pStartButton->SetSize(size);
	pStartButton->Init();

	return pStartButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CStartButton::Init(void)
{
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CStartButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CStartButton::Update(void)
{

	CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CStartButton::Draw(void)
{
	CButton::Draw();
}

void CStartButton::Push(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::GetFade()->SetFade(CManager::MODE_WEAPONSELECT);
}

void CStartButton::Select(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetSize(m_DefaultSize * 1.1f);
}

void CStartButton::Unselect(void)
{
	SetSize(m_DefaultSize);
}