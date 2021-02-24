//=============================================================================
//
// �X�e�[�W���� [stage.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stage.h"
#include "scene.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "warning.h"
#include "score.h"
#include<thread>
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
char* CStage::pFileName[STAGE_TYPE_MAX] = {
"data/TEXT/stage1", 
"data/TEXT/stage2",
""};
STAGE_DATA CStage::m_Stage[STAGE_TYPE_MAX] = {};
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CStage::CStage()
{
	m_nCountEnemy = 0;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStage::Init(void)
{

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStage::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CStage::Update(void)
{
	//�J�E���g
	EnemeyCreate();
}

//=============================================================================
// ���U���g
//=============================================================================
void CStage::Result(STAGE_TYPE stage)
{
	//�X�R�A�Z�b�g
	CManager::SetScore(CGame::GetScore()->GetScore());
	//�X�e�[�W�Z�b�g
	CGame::SetStageType((STAGE_TYPE)(stage + 1));
	//���U���g�\��
	CResult::Create(stage);

}

//=============================================================================
// �G�l�~�[�o���܂ł̃J�E���g
//=============================================================================
void CStage::SetEnemyCount(int nConut)
{
	m_nCountEnemy = nConut;
}

//=============================================================================
// �X�R�A�|�C���^�Z�b�^�[
//=============================================================================
void CStage::SetScore(CScore * pScore)
{
	m_pScore = pScore;
}

//=============================================================================
// �G�l�~�[�o���܂ł̃J�E���g
//=============================================================================
void CStage::EnemeyCreate(void)
{
	//�{�X���o�����Ă��邩
	if (!BossSearch())
	{
		m_nCountEnemy--;
	}

	//�J�E���g��0�ɂȂ�����
	if (m_nCountEnemy <= 0)
	{
		//�X�e�[�W��i�߂�
		StageMode();
	}

}

//=============================================================================
// ���[�h�t�@�C��
//=============================================================================
void CStage::LoadFile(void)
{
	//�t�@�C���|�C���^
	FILE*	pFile[STAGE_TYPE_MAX];
	// �G�l�~�[��
	int		nEnemyCount;
	// �t�F�[�Y��
	int		nPhase;
	// �ǂݍ��񂾈ړ���
	int		nMoveNumber;
	// �����ړ���
	int		nTotalMove;

	//�ǂݍ��ݗp�̃f�[�^
	char cFileString[256];
	//������
	memset(&cFileString, 0, sizeof(cFileString));

	//�e�L�X�g�t�@�C���ǂݍ���
	for (int nStage = 0; nStage < STAGE_TYPE_MAX; nStage++)
	{
		//������
		nPhase		= 0;
		nEnemyCount = 0;
		memset(cFileString, 0, sizeof(cFileString));

		//�e�L�X�g�ǂݍ���
		fopen_s(&pFile[nStage], pFileName[nStage], "r");
		if (pFile[nStage] != NULL)
		{
			//���̃f�[�^�����I���܂œǂݍ���
			while (strcmp(cFileString, "STAGE_END") != 0)
			{
				//������
				memset(cFileString, 0, sizeof(cFileString));
				//�ǂݍ���
				fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));

				//�����̔�r
				if (strcmp(cFileString, "PHASE_START") == 0)
				{
					while (strcmp(cFileString, "PHASE_END") != 0)
					{
						//������
						memset(cFileString, 0, sizeof(cFileString));
						//�ǂݍ���
						fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));
						
						//�G�l�~�[�f�[�^
						if (strcmp(cFileString, "ENEMY_DATA") == 0)
						{
							//������
							nTotalMove = 0;

							while (strcmp(cFileString, "ENEMY_END") != 0)
							{
								//������
								memset(cFileString, 0, sizeof(cFileString));
								//�ǂݍ���
								fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));

								//�G�l�~�[�^�C�v�擾
								if (strcmp(cFileString, "ENEMY_TYPE") == 0)
								{

									int nType;
									fscanf_s(pFile[nStage], " = %d", &nType);

									//�ǂݍ��񂾐��l�Ń^�C�v����
									switch (nType)
									{
									case 0:
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType= ENEMY_TYPE_1;
										break;		   
									case 1:			   
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_2;
										break;		   
									case 2:			   
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_3;
										break;
									case 3:
										m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_4;
										break;

									}									
								}
								//�G�l�~�[�̈ړ����擾
								if (strcmp(cFileString, "STATUS_DATA") == 0)
								{
									//�G�l�~�[�̈ړ�����ǂݏI���܂�
									while (strcmp(cFileString, "STATUS_EMD") != 0)
									{
										//������
										memset(cFileString, 0, sizeof(cFileString));
										//�ǂݍ���
										fscanf_s(pFile[nStage], "%s", cFileString, sizeof(cFileString));

										//����ڂ��̈ړ����擾
										if (strcmp(cFileString, "ENEMY_MOVE_NUMBER") == 0)
										{
											fscanf_s(pFile[nStage], " = %d", &nMoveNumber);
											nTotalMove++;
										}
										if (strcmp(cFileString, "ENEMY_SPEED") == 0)
										{
											fscanf_s(pFile[nStage], " = %f", &m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].MoveData[nMoveNumber].fSpeed);
										}
										if (strcmp(cFileString, "ENEMY_POS") == 0)
										{
											fscanf_s(pFile[nStage], " = %f %f",
												&m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].MoveData[nMoveNumber].pos.x,
												&m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].MoveData[nMoveNumber].pos.y);
										}
									}
									//�s���񐔎擾
									m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemyCount].nEnemyMoveNumber = nTotalMove;
								}

							}
							//�G�l�~�[���J�E���g
							nEnemyCount++;
						}
					}
					//�G�l�~�[����
					m_Stage[nStage].Phase[nPhase].nEnemyCount = nEnemyCount;
					//�t�F�[�Y��i�߂�
					nPhase++;
				}
			}
			m_Stage[nStage].nCountPhase = nPhase;
			fclose(pFile[nStage]);	//�t�@�C�������

		}

	}
}

//=============================================================================
// �X�e�[�W���Q�b�^�[
//=============================================================================
STAGE_DATA CStage::GetStageEnemy(STAGE_TYPE stage)
{
	return m_Stage[stage];
}

//=============================================================================
// �{�X�����邩
//=============================================================================
bool CStage::BossSearch(void)
{
	//�I�u�W�F�N�g�擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����I�u�W�F�N�g�̃|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//�{�X���G����
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�{�X�������ꍇ
				if (pNext->GetObjType() == CScene::OBJ_TYPE_BOSS)
				{

					return true;
				}
				
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}
	//�{�X�����Ȃ��ꍇ
	return false;
}


//=============================================================================
// �{�X���o����
//=============================================================================
void CStage::WarningCreate(void)
{
	//�T�E���h�|�C���^�擾
	CSound *pSound = CManager::GetSound();

	//�T�E���h�X�g�b�v
	pSound->Stop();
	//���[�j���O����
	CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));

}

