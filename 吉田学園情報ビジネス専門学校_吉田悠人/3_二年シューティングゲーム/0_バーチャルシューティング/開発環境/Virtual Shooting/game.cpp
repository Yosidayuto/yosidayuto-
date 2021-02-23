//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"		
#include "score.h"		
#include "life.h"		
#include "player.h"		
#include "bullet base.h"		
#include "explosion.h"
#include "effect.h"		
#include "fade.h"		
#include "manager.h"	
#include "warning.h"	
#include "result.h"		
#include "sound.h"		
#include "game pointer.h"
#include "sound.h"
#include "game bg manager.h"
#include "stage_1.h"
#include "stage_2.h"
#include "stage_3.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
CScore *CGame::m_Score			= NULL;
CPlayer *CGame::m_pPlayer		= NULL;
STAGE_TYPE CGame::m_StageType	= STAGE_TYPE_1;
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CGame::CGame()
{
	m_pPlayer= NULL;
	m_pStage = NULL;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CGame::~CGame()
{
	m_StageType;
	if (m_StageType == STAGE_TYPE_MAX)
	{
		m_StageType = STAGE_TYPE_1;
	}
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CGame::Load(void)
{
	//�e�N�X�`���̓ǂݍ���
	CPlayer::Load();		
	CExplosion::Load();		
	CEffect::Load();		
	CWarning::Load();		
	CGameBgManager::Load();
	CEnemyBase::Load();
	CBulletBase::Load();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CGame::Unload(void)
{
	//�e�N�X�`���̔j��
	CPlayer::Unload();		
	CExplosion::Unload();	
	CEffect::Unload();		
	CWarning::Unload();		
	CGameBgManager::Unload();
	CEnemyBase::Unload();
	CBulletBase::Unload();

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//�T�E���h�N���X�擾
	CSound *pSound = CManager::GetSound();
	//=============================================================================
	//�N���G�C�g����
	//=============================================================================
	//�w�i
	CGameBgManager::Create();
	//�v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(780, 600, 0.0f));
	//�X�R�A�\�L
	m_Score	= CScore::Create(D3DXVECTOR3(35,670,0),D3DXVECTOR3(20,45,0.0f),true);
	m_Score->SetScore(CManager::GetScore());
	//�}�E�X�|�C���^����
	CGamePointer::Create();
	
	//�X�e�[�W����
	switch (m_StageType)
	{
	case STAGE_TYPE_1:
		m_pStage = CStage1::Create();
		break;
	case STAGE_TYPE_2:
		m_pStage = CStage2::Create();
		break;
	case STAGE_TYPE_3:
		m_pStage = CStage3::Create();
		break;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�T�E���h�擾
	CSound*	pSound = CManager::GetSound();

	if (m_pStage != NULL)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = NULL;
	}

	//�V�[���j��
	CScene::ReleaseAll();
	//�T�E���h��~
	pSound->Stop();

}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �X�R�A�擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// �X�e�[�W�Q�b�^�[
//=============================================================================
STAGE_TYPE CGame::GetStageType(void)
{
	return m_StageType;
}

//=============================================================================
// �X�e�[�W�Z�b�g
//=============================================================================
void CGame::SetStageType(STAGE_TYPE stage)
{
	m_StageType = stage;
}

//=============================================================================
// �v���C���[�Q�b�^�[
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}