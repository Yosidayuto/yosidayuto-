//=============================================================================
//
// �X�e�[�W2���� [stage_2.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stage_2.h"
#include "manager.h"
#include "sound.h"
#include "enemy base.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "boss base.h"
#include "boss type2.h"
#include "warning.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PHASE_COUNT (200)	//�t�F�[�Y���ʒu�i�K�ς��܂ł̃J�E���g��

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CStage2::CStage2()
{
	m_EnemyCreate	= ENEMY_CREATE_NULL;
	m_nBossPhase	= 0;
	memset(&m_StageData, NULL, sizeof(m_StageData));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CStage2::~CStage2()
{
}

//=============================================================================
// ��������
//=============================================================================
CStage2 * CStage2::Create(void)
{
	//�������̊m��
	CStage2* pStage2 = NULL;
	pStage2 = new CStage2;

	//NULL�`�F�b�N
	if (pStage2 != NULL)
	{
		//����������
		pStage2->Init();
	}
	return pStage2;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStage2::Init(void)
{
	//�T�E���h�N���X�擾
	CSound *pSound = CManager::GetSound();
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_STAGE_2);
	//�X�e�[�W�̃G�l�~�[�o���f�[�^�擾
	m_StageData = GetStageEnemy(STAGE_TYPE_2);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStage2::Uninit(void)
{
	//�T�E���h�擾
	CSound*	pSound = CManager::GetSound();
	//�V�[���j��
	CScene::ReleaseAll();
	//�T�E���h��~
	pSound->Stop();

}

//=============================================================================
// �X�V����
//=============================================================================
void CStage2::Update(void)
{
	CStage::Update();
}

//=============================================================================
// �G�l�~�[�̃X�|�[�����[�h
//=============================================================================
void CStage2::StageMode(void)
{
	//�X�e�[�W�i�s
	if (m_EnemyCreate <= m_StageData.nCountPhase)
	{
		m_EnemyCreate = (STAGE_ENEMY)(m_EnemyCreate + 1);
	}

	//�G�l�~�[�����p�̃t�F�[�Y���I����Ă��邩
	if (m_EnemyCreate<=m_StageData.nCountPhase)
	{
		//�G�l�~�[����
		EnemyCreate();
		//���̃t�F�[�Y�܂ł̎��Ԑݒ�
		SetEnemyCount(m_StageData.Phase[m_EnemyCreate].nPhaseCount);

	}
	//�{�X��������
	else
	{
		switch (m_nBossPhase)
		{
			//�{�X�o������
		case 0:
			WarningCreate();
			break;

			//�{�X�o��
		case 1:
			BossCreate();
			break;

			//���U���g
		case 2:
			//���U���g�\��			
			Result(STAGE_TYPE_2);
			break;
		}
		//�t�F�[�Y�܂ł̃J�E���g�Z�b�g
		SetEnemyCount(PHASE_COUNT);
		//�i�߂�
		m_nBossPhase++;

	}
}

//=============================================================================
// �G�l�~�[�̐�������
//=============================================================================
void CStage2::EnemyCreate(void)
{
	//�G�l�~�[�̃|�C���^
	CEnemyBase* pEnemy = NULL;

	//�G�l�~�[�̐���
	for (int nEnemy = 0; nEnemy<m_StageData.Phase[m_EnemyCreate].nEnemyCount; nEnemy++)
	{
		switch (m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyType)
		{
		case ENEMY_TYPE_1:
			CEnemyType1::Create(m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyMovePattern,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyAttack,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nSpwan,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nActionTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nAttackTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nReturnTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].pos,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].fSpeed,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nLife);
			break;

		case ENEMY_TYPE_2:
			CEnemyType2::Create(m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyMovePattern,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyAttack,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nSpwan,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nActionTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nAttackTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nReturnTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].pos,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].fSpeed,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nLife);
			break;

		case ENEMY_TYPE_3:
			CEnemyType3::Create(m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyMovePattern,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyAttack,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nSpwan,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nActionTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nAttackTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nReturnTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].pos,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].fSpeed,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nLife);
			break;

		case ENEMY_TYPE_4:
			CEnemyType4::Create(m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyMovePattern,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyAttack,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nSpwan,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nActionTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nAttackTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nReturnTime,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].pos,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].fSpeed,
				m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nLife);
			break;
		}
	}
}

//=============================================================================
// �{�X�̐�������
//=============================================================================
void CStage2::BossCreate(void)
{
	//�T�E���h�|�C���^�擾
	CSound *pSound = CManager::GetSound();
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_BOSS_2);
	//�{�X����
	CBossType2::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
}
