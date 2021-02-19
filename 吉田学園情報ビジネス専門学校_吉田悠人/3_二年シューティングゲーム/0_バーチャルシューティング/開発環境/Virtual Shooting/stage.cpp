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
#include "manager.h"
#include "renderer.h"
#include "boss.h"
#include "game.h"
#include "result.h"
#include "score.h"
#include<thread>
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
char* CStage::pFileName[STAGE_TYPE_MAX] = {
"data/TEXT/Data", 
"",
""};
PHASE_DATA CStage::m_Enemy[ENEMY_CREATE_MAX][MAX_STAGE] = {};
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
// �G�l�~�[�o���܂ł̃J�E���g
//=============================================================================
void CStage::EnemeyCreate(void)
{
	if (CBoss::GetEnemyNumber() == false)
	{
		m_nCountEnemy--;
	}

	if (m_nCountEnemy <= 0)
	{
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
	// �ړ���
	int		nMoveNumber;

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
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType= ENEMY_TYPE_1;
										break;
									case 1:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_2;
										break;
									case 2:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_3;
										break;
									case 3:
										m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].EnemyType = ENEMY_TYPE_4;
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
										}
										if (strcmp(cFileString, "ENEMY_SPEED") == 0)
										{
											fscanf_s(pFile[nStage], " = %f", &m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].moveData[nMoveNumber].fSpeed);
										}
										if (strcmp(cFileString, "ENEMY_POS") == 0)
										{
											fscanf_s(pFile[nStage], " = %f %f",
												&m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].moveData[nMoveNumber].pos.x,
												&m_Enemy[nPhase][nStage].EnemySpawn[nEnemyCount].moveData[nMoveNumber].pos.y);
										}
									}
								}

							}
							//�G�l�~�[���J�E���g
							nEnemyCount++;
						}
					}
					//�t�F�[�Y��i�߂�
					nPhase++;
				}
			}
			fclose(pFile[nStage]);	//�t�@�C�������

		}

	}
}

