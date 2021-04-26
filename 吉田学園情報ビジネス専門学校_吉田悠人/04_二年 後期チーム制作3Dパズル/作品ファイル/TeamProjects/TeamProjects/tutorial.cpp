//=============================================================================
//
// �`���[�g���A�� [tutorial.cpp]
// Author : ��� ����
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_PATH_TUTORIAL "Data/Texture/tutorial.png"
#define TUTORIAL_POS (D3DXVECTOR3((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2),0.0f))
#define TUTORIAL_SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial(int nPriority) :CUi(nPriority)
{
	m_pObject2d = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// �Z���t�̐���
//=============================================================================
CTutorial * CTutorial::Create(void)
{
	// �������̊m��
	CTutorial * pTutorial = NULL;
	pTutorial = new CTutorial;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTutorial->m_nTexture);

	if (pTutorial != NULL)
	{
		// ���W��set
		pTutorial->SetPos(TUTORIAL_POS);
		// �T�C�Y��set
		pTutorial->SetSize(TUTORIAL_SIZE);
		// �e�N�X�`���w��
		pTutorial->BindTexture(Texture);
		// ����������
		pTutorial->Init();
	}

	return pTutorial;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//�w�i����
	m_pObject2d = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0) / 2, D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0), 0.0f, NULL, PRIORITY_UI_3);
	//�w�i�J���[�ݒ�
	m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 128));

	CUi::Init();

	//BGM�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CUi::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CUi::Update();

	//�w�i�p�I�u�W�F�N�g�X�V
	if (m_pObject2d != NULL)
	{
		m_pObject2d->Update();
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorial::Draw(void)
{
	CUi::Draw();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorial::TutorialUninit(void)
{
	if (m_pObject2d != NULL)
	{
		m_pObject2d->Uninit();
	}
	Uninit();
}
