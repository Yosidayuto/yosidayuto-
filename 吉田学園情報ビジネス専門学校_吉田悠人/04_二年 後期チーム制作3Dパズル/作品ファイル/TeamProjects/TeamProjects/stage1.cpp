//=============================================================================
//
// �X�e�[�W1 [stage1.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "stage1.h"
#include "manager.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "game.h"
#include "player.h"
#include "red sand block.h"
#include "hole block.h"
#include "garbage block.h"
#include "luggage block.h"
#include "building block.h"
#include "building break block.h"
#include "stagenumber.h"
#include <stdio.h>
#include "talk_stage1.h"
#include "sound.h"
#include "sea.h"
#include "camera.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define STAGENUMBER_POS_X	(1100.0f)	//�X�e�[�W�i���o�[�p�̈ʒu
#define STAGENUMBER_POS_Y	(80.0f)		//�X�e�[�W�i���o�[�p�̈ʒu
#define STAGENUMBER_SIZE_X	(150.0f)	//�X�e�[�W�i���o�[�p�̃T�C�Y
#define STAGENUMBER_SIZE_Y	(50.0f)		//�X�e�[�W�i���o�[�p�̃T�C�Y

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
char* CStage1::m_pFileName = "Data/Text/stage_1.csv";
MAP_DATA CStage1::m_pMapData = {};
CTalkStage1* CStage1::m_pTalkStage1 = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage1::CStage1()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStage1::~CStage1()
{

}

//=============================================================================
// ���[�h�֐�
//=============================================================================
void CStage1::Load(void)
{
	//�t�@�C���|�C���^
	FILE*	pFile;
	//�ǂݍ��ݗp�f�[�^
	char cFileString[258];
	//�����F��
	int nFileText;
	//��A�s
	int nCol, nRow;
	//�u���b�N��
	int nBlock;
	//������
	pFile = NULL;
	nCol = 1;
	nRow = 0;
	nBlock = 0;
	memset(cFileString, 0, sizeof(cFileString));

	//�t�@�C���ǂݍ���
	fopen_s(&pFile, m_pFileName, "r");

	if (pFile != NULL)
	{
		//�w�b�_�[�ǂݔ�΂�
		while (fgetc(pFile) != '\n');

		while (1)
		{
			while (1)
			{
				nFileText = fgetc(pFile);

				//�����Ȃ烋�[�v�𔲂���B
				if (nFileText == EOF)
				{
					goto out;
				}
				//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
				if (nFileText != ',' && nFileText != '\n')
				{
					strcat_s(cFileString, (const char*)&nFileText);
				}
				//�J���}�����s�Ȃ烋�[�v������B
				else
				{
					break;
				}
			}
			//������ǂݍ���
			switch (atoi(cFileString))
			{
			case 0:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_NONE;
				break;

			case 1:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_START;
				break;
			case 2:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_GOAL;
				break;
			case 3:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_TILE_RED_SAMD;
				break;
			case 4:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_HINDRANCE_BUILDING_1;
				break;
			case 5:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_HINDRANCE_BUILDING_2;
				break;
			case 6:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_GARBAGE;
				break;
				
			}
			//�o�b�t�@�̏�����
			memset(cFileString, 0, sizeof(cFileString));
			//�񐔂𑫂�
			nCol++;

			//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
			if (nFileText == '\n')
			{
				//�s���ۑ�
				m_pMapData.BlockData[nRow].nStageSizeX = nCol;
				//�s��������
				nCol = 1;
				//��̐i�s
				nRow++;
			}

		}
		out:							//�����Ȃ炱���ɒ���
		m_pMapData.nStageSizeY = nRow;	//�u���b�N����ۑ�
		fclose(pFile);					//�t�@�C�������
	}
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CStage1::Init(void)
{
	//�J�����̒����ʒu
	CManager::GetCamera()->SetPos(D3DXVECTOR3(-275,0.0f,300.0f));
	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 0.002f,CSea::TYPE_DIRTY);
	CSea::Create(D3DXVECTOR3(0.0f, -60.0f, 0.0f), 0.005f,CSea::TYPE_DIRTY);
	CSea::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), 0.008f,CSea::TYPE_DIRTY);
	
	//�}�b�v����
	MapCreate();

	//�Z���t�𐶐�
	m_pTalkStage1 = CTalkStage1::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f),
										D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	////�X�e�[�W�i���o�[�쐬
	//CStageNumber::Create(D3DXVECTOR3(STAGENUMBER_POS_X, STAGENUMBER_POS_Y, 0.0f), 
	//	D3DXVECTOR3(STAGENUMBER_SIZE_X, STAGENUMBER_SIZE_Y, 0.0f),
	//	CStageNumber::STAGE_NUM_1);

	//BGM�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_1);

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CStage1::Uninit(void)
{
	//BGM�̏I��
	CManager::GetSound()->StopSound();

	CObject::ReleaseAll();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CStage1::Draw(void)
{
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CStage1::Update(void)
{
#ifdef _DEBUG

	//�t�F�C�h�擾
	CFade*	pBlackout = CManager::GetFadeout();
	//�L�[���͎擾
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();

	//�X�e�B�b�N����
	if (pInputKey->GetKeyTrigger(DIK_RETURN))
	{
		pBlackout->SetWhiteout(CGame::MAP_TYPE_2);
	}
#endif

}

//=============================================================================
// �}�b�v�����֐�
//=============================================================================
void CStage1::MapCreate(void)
{
	//�}�b�v�f�[�^�����邩
	if (&m_pMapData != NULL)
	{
		for (int nBlockY = 0; nBlockY < m_pMapData.nStageSizeY; nBlockY++)
		{
			for (int nBlockX = 0; nBlockX < m_pMapData.BlockData[nBlockY].nStageSizeX; nBlockX++)
			{
				//�}�X�ڂ̃^�C�v�擾
				switch (m_pMapData.BlockData[nBlockY].nBlockType[nBlockX])
				{
				case BLOCK_TYPE_NONE:	//�Ȃ�

					break;
				case BLOCK_TYPE_START:	//�X�^�[�g�n�_
					CPlayer::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_GOAL:	//�S�[���n�_
					CLuggageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_1);
					break;
				case BLOCK_TYPE_TILE_RED_SAMD:			//�ԍ�
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_HINDRANCE_BUILDING_1:	//�r��
					CBuildingBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;

				case BLOCK_TYPE_HINDRANCE_BUILDING_2:	//�r���i����j
					CBuildingBreakBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_ITEM_GARBAGE:			//�S�~�u���b�N
					CGarbageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				}

			}
		}
		
	}
}

//=============================================================================
// �^�C�g���ǂݍ��ݗp�}�b�v�����֐�
//=============================================================================
void CStage1::TitleMapCreate(void)
{
	//�}�b�v�f�[�^�����邩
	if (&m_pMapData != NULL)
	{
		for (int nBlockY = 0; nBlockY < m_pMapData.nStageSizeY; nBlockY++)
		{
			for (int nBlockX = 0; nBlockX < m_pMapData.BlockData[nBlockY].nStageSizeX; nBlockX++)
			{
				//�}�X�ڂ̃^�C�v�擾
				switch (m_pMapData.BlockData[nBlockY].nBlockType[nBlockX])
				{
				case BLOCK_TYPE_NONE:	//�Ȃ�

					break;
				case BLOCK_TYPE_START:	//�X�^�[�g�n�_
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_GOAL:	//�S�[���n�_
					CLuggageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_2);
					break;
				case BLOCK_TYPE_TILE_RED_SAMD:			//�ԍ�
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_HINDRANCE_BUILDING_1:	//�r��
					CBuildingBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;

				case BLOCK_TYPE_HINDRANCE_BUILDING_2:	//�r���i����j
					CBuildingBreakBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				case BLOCK_TYPE_ITEM_GARBAGE:			//�S�~�u���b�N
					CGarbageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CRedSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				}

			}
		}

	}

}

//=============================================================================
// �Z���t�|�C���^�̃Q�b�^�[����
//=============================================================================
CTalkStage1 * CStage1::GetTalkStage1(void)
{
	return m_pTalkStage1;
}