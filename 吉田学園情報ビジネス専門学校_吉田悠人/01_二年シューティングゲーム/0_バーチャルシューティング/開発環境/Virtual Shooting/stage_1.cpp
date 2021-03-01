//=============================================================================
//
// �X�e�[�W1���� [stage_1.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stage_1.h"
#include "manager.h"
#include "sound.h"
#include "warning.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "boss base.h"
#include "boss type1.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PHASE_COUNT (200)	//�t�F�[�Y���ʒu�i�K�ς��܂ł̃J�E���g��

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CStage1::CStage1()
{
	m_EnemyCreate = ENEMY_CREATE_NULL;
	memset(&m_StageData, NULL, sizeof(m_StageData));
	m_nBossPhase = 0;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CStage1::~CStage1()
{
}

//=============================================================================
// ��������
//=============================================================================
CStage1 * CStage1::Create(void)
{
	//�������̊m��
	CStage1* pStage1 = NULL;
	pStage1 = new CStage1;

	//NULL�`�F�b�N
	if (pStage1 != NULL)
	{
		//����������
		pStage1->Init();
	}
	return pStage1;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStage1::Init(void)
{
	//�T�E���h�N���X�擾
	CSound *pSound = CManager::GetSound();
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_STAGE_1);

	//�X�e�[�W�̃G�l�~�[�o���f�[�^�擾
	m_StageData = GetStageEnemy(STAGE_TYPE_1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStage1::Uninit(void)
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
void CStage1::Update(void)
{
	CStage::Update();
}

//=============================================================================
// �X�e�[�W�̐i�s����
//=============================================================================
void CStage1::StageMode(void)
{
	//�X�e�[�W�i�s
	if (m_EnemyCreate <= m_StageData.nCountPhase)
	{
		m_EnemyCreate = (STAGE_ENEMY)(m_EnemyCreate + 1);
	}

	//�G�l�~�[�����p�̃t�F�[�Y���I����Ă��邩
	if (m_EnemyCreate<= m_StageData.nCountPhase)
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
			Result(STAGE_TYPE_1);
			break;
		}
		SetEnemyCount(PHASE_COUNT);

		//�i�߂�
		m_nBossPhase++;
	}

}

//=============================================================================
// �G�l�~�[�̐�������
//=============================================================================
void CStage1::EnemyCreate(void)
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

		}
	}

}

//=============================================================================
// �{�X�̐�������
//=============================================================================
void CStage1::BossCreate(void)
{
	//�T�E���h�|�C���^�擾
	CSound *pSound = CManager::GetSound();

	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_BOSS_1);
	//�{�X����
	CBossType1::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
}
