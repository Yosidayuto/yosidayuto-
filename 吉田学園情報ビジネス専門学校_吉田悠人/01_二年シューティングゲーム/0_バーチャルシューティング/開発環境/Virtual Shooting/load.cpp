//=============================================================================
//
// ���[�h��ʏ��� [load.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "load.h"
#include "renderer.h"
#include "sound.h"
#include "manager.h"
#include "load bg.h"
#include "clear.h"
#include "number.h"
#include "telop.h"
#include "mouse pointer.h"
#include "title bg.h"
#include "tutorial bg.h"
#include "select bg.h"
#include "life ui.h"
#include "weapon manager.h"
#include "button manager.h"
#include "result bg.h"
#include "score bar.h"
#include "stage.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoad::CLoad()
{
	m_bLoad = false;
	m_pLoadBg = NULL;
	nLoad = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoad::~CLoad()
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CLoad::Load(void)
{
	CLoadBg::Load();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CLoad::Unload(void)
{
	CLoadBg::Unload();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLoad::Init(void)
{
	//�T�E���h�擾
	CSound*	pSound = CManager::GetSound();
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_LOAD);
	//�w�i����
	m_pLoadBg = CLoadBg::Create();

	//�t�@�C�����[�h(�}���`�X���b�h)
	m_stLoad = std::thread (&CLoad::FileLoad, this);

	m_stLoad.detach();
	//�����܂�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLoad::Uninit(void)
{
	//�V�[���j��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
bool CLoad::GetLoad(void)
{
	return m_bLoad;
}

void CLoad::FileLoad(void)
{
	while (!m_bLoad)
	{
		File();
	}
}

void CLoad::File(void)
{
	switch (nLoad)
	{
	case 0:
		CClear::Load();
		break;
	case 1:
		CNumber::Load();
		break;
	case 2:
		CTelop::Load();
		break;
	case 3:
		CPointer::Load();
		break;
	case 4:
		CTitleBg::Load();
		break;
	case 5:
		CTutorialBg::Load();
		break;
	case 6:
		CSelectBg::Load();
		break;
	case 7:
		CLifeUi::Load();
		break;
	case 8:
		CWeaponManager::Load();
		break;
	case 9:
		CButtonManager::Load();
		break;
	case 10:
		CGame::Load();
		break;
	case 11:
		CResultBg::Load();
		break;
	case 12:
		CScoreBar::Load();
		break;
	case 13:
		CStage::LoadEnemyData();
		//�ǂݏI������
		m_bLoad = true;
		break;
	}
	nLoad++;
}
