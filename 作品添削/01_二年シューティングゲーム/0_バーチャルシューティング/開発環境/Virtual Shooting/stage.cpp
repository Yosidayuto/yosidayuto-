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
"data/TEXT/stage1.csv", 
"data/TEXT/stage2.csv",
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
// �X�e�[�W�G�l�~�[�̏�񃍁[�h
//=============================================================================
void CStage::LoadEnemyData(void)
{
	//�t�@�C���|�C���^
	FILE*	pFile[STAGE_TYPE_MAX];
	//�ǂݍ��ݗp�̃f�[�^
	char cFileString[256];
	//�����F��
	int nFile;
	//��
	int nCol = 1;
	//�s
	int nRow = 0;
	//�t�F�[�X��
	int nPhase = 0;
	//�G�l�~�[��
	int nEnemy = 0;

	memset(cFileString, 0, sizeof(cFileString));
	//�e�L�X�g�t�@�C���ǂݍ���
	for (int nStage = 0; nStage < STAGE_TYPE_MAX; nStage++)
	{
		//�t�@�C���ǂݍ���
		fopen_s(&pFile[nStage], pFileName[nStage], "r");
		//�t�F�[�Y���̏�����
		nPhase = 0;
		//�G�N�Z���̃Z��������
		nCol = 1;
		nRow = 0;
		//�G�l�~�[���̏�����
		nEnemy = 0;

		if (pFile[nStage] != NULL)
		{
			//�w�b�_�[�ǂݔ�΂�
			while(fgetc(pFile[nStage]) != '\n');

			while (1)
			{
				while (1) 
				{
					nFile = fgetc(pFile[nStage]);

					//�����Ȃ烋�[�v�𔲂���B
					if (nFile == EOF)
					{
						goto out;
					}
					//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
					if (nFile != ',' && nFile != '\n')
					{
						strcat_s(cFileString, (const char*)&nFile);
					}
					//�J���}�����s�Ȃ烋�[�v������B
					else
					{
						break;
					}
				}

				if (strcmp(cFileString, "PHASE_END") != 0)
				{
					//������ǂݍ���
					switch (nCol)
					{
						//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
					case 1: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].EnemyType = (ENEMY_TYPE)atoi(cFileString); break;
						//2��ڂ͍s���p�^�[���B	
					case 2: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].EnemyMovePattern = (ENEMY_MOVE_PATTERN)atoi(cFileString); break;
						//3��ڂ͍U���p�^�[��
					case 3: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].EnemyAttack = (ENEMY_ATTACK_PATTERN)atoi(cFileString); break;
						//4��ڂ͏o���܂ł̎���
					case 4: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nSpwan = atoi(cFileString); break;
						//5��ڂ̓A�N�V�����܂ł̃J�E���g
					case 5: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nActionTime = atoi(cFileString); break;
						//6��ڂ͍U���̃J�E���g
					case 6: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nAttackTime = atoi(cFileString); break;
						//7��ڂ͍ŏ���X�̏o���ʒu
					case 7: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nReturnTime = atoi(cFileString); break;
						//8��ڂ͍ŏ���X�̏o���ʒu
					case 8: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].pos.x = (float)atoi(cFileString) + STAGE_POS; break;
						//9��ڂ͍ŏ���Y�̏o���ʒu
					case 9: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].pos.y = (float)atoi(cFileString); break;
						//10��ڂ̓X�s�[�h
					case 10: m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].fSpeed =(float)atoi(cFileString); break;
						//11��ڂ̗͑�+�G�l�~�[���̃J�E���g
					case 11:
						m_Stage[nStage].Phase[nPhase].EnemySpawn[nEnemy].nLife = atoi(cFileString); 
						nEnemy++;
						break;
					}

				}
				else
				{

					//�t�F�[�Y�ڍs�̃J�E���g�擾
					fscanf_s(pFile[nStage], " %d", &m_Stage[nStage].Phase[nPhase].nPhaseCount);
					//�G�l�~�[���擾
					m_Stage[nStage].Phase[nPhase].nEnemyCount = nEnemy;
					//�G�l�~�[���̏�����
					nEnemy = 0;
					//�t�F�[�Y�̃J�E���g
					nPhase++;
					
					//���s
					nRow++;
					nCol = 0;

				}
				//�o�b�t�@�̏�����
				memset(cFileString, 0, sizeof(cFileString));
				//�񐔂𑫂�
				nCol++;

				//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
				if (nFile == '\n')
				{
					nCol = 1;
					nRow++;
				}

			}
			out:										//�����Ȃ炱���ɒ���
			m_Stage[nStage].nCountPhase = nPhase;		//�ő�t�F�[�Y���擾
			fclose(pFile[nStage]);						//�t�@�C�������
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

