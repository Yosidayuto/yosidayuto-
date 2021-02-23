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
	if (m_EnemyCreate < m_StageData.nCountPhase)
	{
		m_EnemyCreate = (STAGE_ENEMY)(m_EnemyCreate + 1);
	}

	//�G�l�~�[�����p�̃t�F�[�Y���I����Ă��邩
	if (m_StageData.Phase[m_EnemyCreate].nEnemyCount>m_EnemyCreate)
	{
		EnemyCreate();
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
		//�i�߂�
		m_nBossPhase++;

	}
	SetEnemyCount(PHASE_COUNT);
}

//=============================================================================
// �G�l�~�[�̐�������
//=============================================================================
void CStage2::EnemyCreate(void)
{
	//�G�l�~�[�̃|�C���^
	CEnemyBase* pEnemy = NULL;

	//�G�l�~�[�̐���
	for (int nEnemy = 0; nEnemy<m_StageData.Phase[m_EnemyCreate].nEnemyCount + 1; nEnemy++)
	{
		//�G�l�~�[�̍s������
		for (int nMoveCount = 0; nMoveCount<m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nEnemyMoveNumber; nMoveCount++)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].MoveData[nMoveCount].pos;
			//�ʒu�C��
			pos.x += STAGE_POS - (STAGE_SIZE / 2);
			//�G�l�~�[�̃N���G�C�g
			if (nMoveCount == 0)
			{
				//�ʒu�C��
				pos.y -= 200;

				switch (m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].EnemyType)
				{
				case ENEMY_TYPE_1:
					pEnemy = CEnemyType1::Create(pos);
					break;
				case ENEMY_TYPE_2:
					pEnemy = CEnemyType2::Create(pos);
					break;
				case ENEMY_TYPE_3:
					pEnemy = CEnemyType3::Create(pos);
					break;
				case ENEMY_TYPE_4:
					pEnemy = CEnemyType4::Create(pos);
					break;
				}
			}
			//�G�l�~�[�̍s���ʒu�ݒ�
			else
			{
				//�X�s�[�h�擾
				float fSpeed = m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].MoveData[nMoveCount].fSpeed;
				//�Ō�̍s���̏ꍇ
				if (nMoveCount + 1 == m_StageData.Phase[m_EnemyCreate].EnemySpawn[nEnemy].nEnemyMoveNumber)
				{
					//�ʒu�C��
					pos.y += 200;
				}
				//�ړ�����|�C���g�ݒ�
				pEnemy->SetMovePointer(pos, nMoveCount, fSpeed);
			}
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
