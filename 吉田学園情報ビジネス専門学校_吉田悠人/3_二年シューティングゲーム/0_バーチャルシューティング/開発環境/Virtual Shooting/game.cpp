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
#include "enemy.h"		
#include "bullet base.h"		
#include "explosion.h"
#include "effect.h"		
#include "boss.h"		
#include "boss_anime.h"	
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
	if (m_StageType== STAGE_TYPE_MAX)
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
	CEnemy::Load();			
	CBoss::Load();			
	CExplosion::Load();		
	CBossAnime::Load();		
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
	CEnemy::Unload();		
	CBoss::Unload();		
	CExplosion::Unload();	
	CEffect::Unload();		
	CBossAnime::Unload();	
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
		m_StageType = STAGE_TYPE_2;
		break;
	case STAGE_TYPE_2:
		m_pStage = CStage2::Create();
		m_StageType = STAGE_TYPE_3;
		break;
	case STAGE_TYPE_3:
		m_pStage = CStage3::Create();
		m_StageType = STAGE_TYPE_MAX;
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
// �v���C���[�Q�b�^�[
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

////=============================================================================
//// �G�l�~�[�̃X�|�[�����[�h
////=============================================================================
//void CGame::StageMode(void)
//{
//	CSound *pSound = CManager::GetSound();
//
//	switch (m_StageType)
//	{
//	case STAGE_TYPE_1:
//		//780���S�@��400
//		switch (m_EnemyCreate)
//		{
//		case ENEMY_CREATE_1:
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);
//
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);
//
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_2:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -250, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -350, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_3:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_4:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_5:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_6:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN);
//
//			m_nCountEnemy += 450;
//
//			break;
//		case ENEMY_CREATE_7:
//			//�T�E���h�X�g�b�v
//			pSound->Stop(CSound::LABEL_BGM_STAGE_1);
//			//���[�j���O����
//			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
//			m_nCountEnemy += 350;
//
//			break;
//
//		case ENEMY_CREATE_8:
//			//�T�E���h�Đ�
//			pSound->Play(CSound::LABEL_BGM_BOSS_1);
//
//			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));
//
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_9:
//			CManager::SetScore(m_Score->GetScore());
//
//			CResult::Create();
//			m_StageType = STAGE_TYPE_2;
//			break;
//		}
//
//		break;
//	case STAGE_TYPE_2:
//		//780���S�@��400
//		switch (m_EnemyCreate)
//		{
//		case ENEMY_CREATE_1:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH ,		-100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STOP, 75);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
//			m_nCountEnemy += 350;
//			break;
//		case ENEMY_CREATE_2:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
//			
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_3:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_4:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_5:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH+100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH-100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
//
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_6:
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_7:
//			//�T�E���h�X�g�b�v
//			pSound->Stop(CSound::LABEL_BGM_STAGE_2);
//
//			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
//			m_nCountEnemy += 350;
//
//			break;
//
//		case ENEMY_CREATE_8:
//			//�T�E���h�Đ�
//			pSound->Play(CSound::LABEL_BGM_BOSS_2);
//
//			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));
//
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_9:
//			CManager::SetScore(m_Score->GetScore());
//
//			CResult::Create();
//			m_StageType = STAGE_TYPE_3;
//			break;
//
//
//		}
//
//
//		break;
//	case STAGE_TYPE_3:
//
//		switch (m_EnemyCreate)
//		{
//		case ENEMY_CREATE_1:
//			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
//
//			m_nCountEnemy += 350;
//			break;
//		case ENEMY_CREATE_2:
//			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_3:
//			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
//
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_4:
//			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_5:
//			//�T�E���h�X�g�b�v
//			pSound->Stop(CSound::LABEL_BGM_STAGE_3);
//
//			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
//
//			m_nCountEnemy += 300;
//			break;
//		case ENEMY_CREATE_6:
//			//�T�E���h�Đ�
//			pSound->Play(CSound::LABEL_BGM_BOSS_3);
//
//			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_3, D3DXVECTOR3(500, 500, 0));
//
//			m_nCountEnemy += 450;
//			break;
//		case ENEMY_CREATE_7:
//
//
//			CManager::SetScore(m_Score->GetScore());
//
//			CResult::Create();
//			m_StageType = STAGE_TYPE_MAX;
//
//
//			m_nCountEnemy += 450;
//			break;
//
//		}
//		break;
//
//
//	}
//}
