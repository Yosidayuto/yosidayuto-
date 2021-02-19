//=============================================================================
//
//	�{�^���}�l�[�W���[[button manager.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "button manager.h"
#include "renderer.h"
#include "manager.h"
#include "select.h"
#include "button.h"
#include "start button.h"
#include "life button.h"
#include "speed button.h"
#include "bullet button.h"
#include "laser button.h"
#include "homing button.h"
#include "telop.h"
#include "score.h"
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CButtonManager::CButtonManager()
{
	ZeroMemory(m_pButton, sizeof(m_pButton));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CButtonManager::~CButtonManager()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CButtonManager::Load(void)
{
	CStartButton::Load();
	CLifeButton::Load();
	CSpeedButton::Load();
	CBulletButton::Load();
	CLaserButton::Load();
	CHomingButton::Load();
	CButton::Load();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CButtonManager::Unload(void)
{
	CStartButton::Unload();
	CLifeButton::Unload();
	CSpeedButton::Unload();
	CBulletButton::Unload();
	CLaserButton::Unload();
	CHomingButton::Unload();
	CButton::Unload();
}

//=============================================================================
// ��������
//=============================================================================
CButtonManager * CButtonManager::Create(void)
{
	CButtonManager* pButtonManager;
	pButtonManager = new CButtonManager;
	//����������
	pButtonManager->Init();
	return pButtonManager;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CButtonManager::Init(void)
{
	m_pButton[BUTTON_TYPE_START]	= CStartButton::Create(D3DXVECTOR3(140, 150, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_LIFE]		= CLifeButton::Create(D3DXVECTOR3(140, 250, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_SPEED]	= CSpeedButton::Create(D3DXVECTOR3(140, 300, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_BUTTOL]	= CBulletButton::Create(D3DXVECTOR3(140, 350, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_LASER]	= CLaserButton::Create(D3DXVECTOR3(140, 400, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));
	m_pButton[BUTTON_TYPE_HOMING]	= CHomingButton::Create(D3DXVECTOR3(140, 450, 0.0f), D3DXVECTOR3(270.0f, 35.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CButtonManager::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CButtonManager::Update(void)
{
	//�}�E�X�A�E�g�̏���
	MouseOut();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CButtonManager::Draw(void)
{
}

//=============================================================================
// �}�E�X�A�E�g�̏���
//=============================================================================
void CButtonManager::MouseOut(void)
{
	//�e���b�v�|�C���^
	CTelop*		pTelop = CSelect::GetTelop();
	//�X�R�A�����ʎ擾
	CScore*		pMinusScore = CSelect::GetMinusScore();

	//�ǂꂩ�{�^���Ƀ}�E�X�J�[�\�����d�Ȃ��Ă��邩
	for (int nCountType = 0; nCountType < BUTTON_TYPE_MAX; nCountType++)
	{
		if (m_pButton[nCountType]->Hit())
		{
			//�������I���
			return;
		}
	}

	//�}�E�X�J�[�\�����d�Ȃ��Ă��Ȃ������Ƃ�
	if (pTelop->GetTelopType() != TELOP_TYPE_TUTORIAL)
	{
		//�e���b�v�ؑ�
		pTelop->TypeChange(TELOP_TYPE_TUTORIAL);
	}
	//����X�R�A��0�ɕϊ�
	pMinusScore->SetScore(0);

}
