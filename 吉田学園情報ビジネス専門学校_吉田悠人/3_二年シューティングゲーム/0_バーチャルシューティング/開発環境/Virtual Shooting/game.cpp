//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "game.h"		
#include "score.h"		
#include "life.h"		
#include "player.h"		
#include "enemy.h"		
#include "Background.h"	
#include "bullet.h"		
#include "explosion.h"
#include "effect.h"		
#include "bg_game.h"	
#include "laser.h"		
#include "boss.h"		
#include "boss_anime.h"	
#include "fade.h"		
#include "manager.h"	
#include "warning.h"	
#include "homing.h"		
#include "result.h"		
#include "sound.h"		
#include "mouse pointer.h"
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
CLife *CGame::m_Life = NULL;
CScore *CGame::m_Score = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CGame::STAGE_TYPE CGame::m_StageType = STAGE_TYPE_1;
//---------------------------------
//�R���X�g���N�^
//---------------------------------
CGame::CGame()
{
	m_pPlayer = NULL;
	m_Life = NULL;
	m_pBg = NULL;
	m_nCountEnemy = 100;
	m_EnemyCreate = ENEMY_CREATE_NONE;
}

//---------------------------------
//�f�X�g���N�^
//---------------------------------
CGame::~CGame()
{
	if (m_StageType== STAGE_TYPE_MAX)
	{
		m_StageType = STAGE_TYPE_1;
	}
}


//---------------------------------
//����������
//---------------------------------
HRESULT CGame::Init(void)
{
	//�T�E���h�N���X�擾
	CSound *pSound = CManager::GetSound();
	//�e�N�X�`���̓ǂݍ���
	CBg::Load();			//�w�i
	CEnemy::Load();			//�G�l�~�[
	CBullet::Load();		//�o���b�g
	CPlayer::Load();		//�v���C���[
	CExplosion::Load();		//�G�N�X�v���[�W����
	CEffect::Load();		//�G�t�F�N�g
	CBgGame::Load();		//�w�i�Q�[��
	CLaser::Load();			//���[�U�[
	CBoss::Load();			//�{�X
	CBossAnime::Load();		//�{�X�G�t�F�N�g
	CWarning::Load();		//���[�j���O
	CHoming::Load();		//�z�[�~���O
	//�N���G�C�g����
	CBgGame::Create();		//�w�i�Q�[��
	m_pBg = CBg::Create();
	m_Life = CLife::Create(D3DXVECTOR3(100, 100, 0.0f));
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(780, 600, 0.0f));
	m_Score	= CScore::Create(D3DXVECTOR3(35,670,0),D3DXVECTOR3(20,45,0.0f),true);
	m_Score->SetScore(CManager::GetScore());
	CPointer::Create(CPointer::POINTER_TYPE_GAME);
	m_EnemyCreate = ENEMY_CREATE_NONE;
	switch (m_StageType)
	{
	case STAGE_TYPE_1:
		pSound->Play(CSound::LABEL_BGM_STAGE_1);

		break;
	case STAGE_TYPE_2:
		pSound->Play(CSound::LABEL_BGM_STAGE_2);

		break;

	case STAGE_TYPE_3:
		pSound->Play(CSound::LABEL_BGM_STAGE_3);

		break;

	}
	return S_OK;
}

//---------------------------------
//�I������
//---------------------------------
void CGame::Uninit(void)
{
	//�e�N�X�`���̔j��
	CBg::Unload();			//�w�i
	CEnemy::Unload();		//�G�l�~�[
	CBullet::Unload();		//�o���b�g
	CPlayer::Unload();		//�v���C���[
	CExplosion::Unload();	//�G�N�X�v���[�W����
	CEffect::Unload();		//�G�t�F�N�g
	CBgGame::Unload();	
	CLaser::Unload();		//���[�U�[
	CBoss::Unload();		//�{�X
	CBossAnime::Unload();	//�{�X�A�j���[�V����
	CWarning::Unload();		//���[�j���O
	CHoming::Unload();		//�z�[�~���O
	if (m_Life != NULL)
	{
		m_Life->Uninit();
	}

	//�V�[���j��
	CScene::ReleaseAll();

}

//---------------------------------
//�X�V����
//---------------------------------
void CGame::Update(void)
{

	EnemeyCreate();
}

//---------------------------------
//�`�揈��
//---------------------------------
void CGame::Draw(void)
{
}

//---------------------------------
//���C�t�擾
//---------------------------------
CLife * CGame::GetLife(void)
{
	return m_Life;
}

//---------------------------------
//�X�R�A�擾
//---------------------------------
CScore * CGame::GetScore(void)
{
	return m_Score;
}

void CGame::EnemeyCreate(void)
{
	if (CBoss::GetEnemyNumber() == false)
	{
		m_nCountEnemy--;
	}
	

	if (m_nCountEnemy <= 0)
	{

	int nModo =	m_EnemyCreate +1;

		m_EnemyCreate = (ENEMY_CREATE)nModo;
		StageMode();
	}


}

void CGame::StageMode(void)
{
	CSound *pSound = CManager::GetSound();

	switch (m_StageType)
	{
	case STAGE_TYPE_1:
		//780���S�@��400
		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);


			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 50);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 55);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_CROSS, 60);

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_2:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -250, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -350, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_3:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_CORNER, 70);
			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_4:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);


			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -300, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);


			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -600, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_5:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);

			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_6:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN);

			m_nCountEnemy += 450;

			break;
		case ENEMY_CREATE_7:
			//�T�E���h�X�g�b�v
			pSound->Stop(CSound::LABEL_BGM_STAGE_1);
			//���[�j���O����
			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
			m_nCountEnemy += 350;

			break;

		case ENEMY_CREATE_8:
			//�T�E���h�Đ�
			pSound->Play(CSound::LABEL_BGM_BOSS_1);

			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));


			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_9:
			CManager::SetScore(m_Score->GetScore());

			CResult::Create();
			int nStage = m_StageType + 1;
			m_StageType = (STAGE_TYPE)nStage;

			break;


		}

		break;
	case STAGE_TYPE_2:
		//780���S�@��400
		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH ,		-100, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STOP, 75);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_SIDE, 60);
			m_nCountEnemy += 350;
			break;
		case ENEMY_CREATE_2:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -100, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_U_TURN, 70);
			
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT, 100);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -150, 0.0f), CEnemy::ENEMY_TYPE_2, CEnemy::PATTERN_MODE_STRAIGHT);

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_3:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -70, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);
			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_4:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_4, CEnemy::PATTERN_MODE_STRAIGHT, 70, CEnemy::BULLET_PATTERN_SPIRAL);

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_5:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH+100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH-100, -200, 0.0f), CEnemy::ENEMY_TYPE_1, CEnemy::PATTERN_MODE_U_TURN, 80);

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_6:
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -50, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH + 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 50, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 100, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 150, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 200, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 250, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 300, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 350, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			CEnemy::Create(D3DXVECTOR3(GAME_WIDTH - 400, -200, 0.0f), CEnemy::ENEMY_TYPE_3, CEnemy::PATTERN_MODE_STRAIGHT);
			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_7:
			//�T�E���h�X�g�b�v
			pSound->Stop(CSound::LABEL_BGM_STAGE_2);

			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
			m_nCountEnemy += 350;

			break;

		case ENEMY_CREATE_8:
			//�T�E���h�Đ�
			pSound->Play(CSound::LABEL_BGM_BOSS_2);

			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));


			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_9:
			CManager::SetScore(m_Score->GetScore());

			CResult::Create();
			int nStage = m_StageType + 1;
			m_StageType = (STAGE_TYPE)nStage;
			break;


		}


		break;
	case STAGE_TYPE_3:

		switch (m_EnemyCreate)
		{
		case ENEMY_CREATE_1:
			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));

			m_nCountEnemy += 350;
			break;
		case ENEMY_CREATE_2:
			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_3:
			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_4:
			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_5:
			//�T�E���h�X�g�b�v
			pSound->Stop(CSound::LABEL_BGM_STAGE_3);

			CWarning::Create(D3DXVECTOR3(GAME_WIDTH, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));

			m_nCountEnemy += 300;
			break;
		case ENEMY_CREATE_6:
			//�T�E���h�Đ�
			pSound->Play(CSound::LABEL_BGM_BOSS_3);

			CBoss::Create(D3DXVECTOR3(GAME_WIDTH, 100, 0.0f), CBoss::BOSS_TYPE_3, D3DXVECTOR3(500, 500, 0));

			m_nCountEnemy += 450;
			break;
		case ENEMY_CREATE_7:


			CManager::SetScore(m_Score->GetScore());

			CResult::Create();
			m_StageType = STAGE_TYPE_1;


			m_nCountEnemy += 450;
			break;

		}
		break;


	}
}
