//=============================================================================
//
// �`���[�g���A���{�^������ [tutorialbutton.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "tutorialbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialButton::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorialButton::CTutorialButton()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorialButton::~CTutorialButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CTutorialButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/tutorial.png",								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CTutorialButton::Unload(void)
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
CTutorialButton * CTutorialButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTutorialButton* pTutorialButton = NULL;
	pTutorialButton = new CTutorialButton;
	pTutorialButton->SetPos(pos);
	pTutorialButton->m_DefaultSize = size;
	pTutorialButton->SetSize(size);
	pTutorialButton->Init();

	return pTutorialButton;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CTutorialButton::Init(void)
{
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CTutorialButton::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CTutorialButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorialButton::Draw(void)
{
	CButton::Draw();
}

void CTutorialButton::Push(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
}

void CTutorialButton::Select(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetSize(m_DefaultSize * 1.1f);
}

void CTutorialButton::Unselect(void)
{
	SetSize(m_DefaultSize);
}
