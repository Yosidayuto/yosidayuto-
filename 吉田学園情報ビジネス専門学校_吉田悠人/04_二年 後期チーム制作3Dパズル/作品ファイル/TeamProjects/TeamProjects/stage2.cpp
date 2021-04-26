//=============================================================================
//
// �X�e�[�W2 [stage2.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "stage2.h"
#include "manager.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "game.h"
#include "player.h"
#include "sand block.h"
#include "sprout block.h"
#include "seeds block.h"
#include "stagenumber.h"
#include "hole block.h"
#include <stdio.h>
#include "talk_stage2.h"
#include "sound.h"
#include "luggage block.h"
#include "sea.h"
#include "camera.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define STAGENUMBER_POS_X 1100.0f
#define STAGENUMBER_POS_Y 80.0f
#define STAGENUMBER_SIZE_X 150.0f
#define STAGENUMBER_SIZE_Y 50.0f

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
char* CStage2::m_pFileName = "Data/Text/stage_2.csv";
MAP_DATA CStage2::m_pMapData = {};
CTalkStage2* CStage2::m_pTalkStage2 = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage2::CStage2()
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStage2::~CStage2()
{

}

//=============================================================================
// ���[�h�֐�
//=============================================================================
void CStage2::Load(void)
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
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_TILE_SAMD;
				break;
			case 4:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_TILE_SPROUT;
				break;
			case 5:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_SEEDS;
				break;
			case 6:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_CUBE;
				break;
			case 7:
				//�u���b�N�^�C�v�L��
				m_pMapData.BlockData[nRow].nBlockType[nCol] = BLOCK_TYPE_ITEM_SAMD_WALL;
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
HRESULT CStage2::Init(void)
{
	//�J�����̒����ʒu
	CManager::GetCamera()->SetPos(D3DXVECTOR3(-275, 0.0f, 300.0f));

	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 0.002f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -60.0f, 0.0f), 0.005f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), 0.008f, CSea::TYPE_NORMAL);

	//�}�b�v����
	MapCreate();

	////�X�e�[�W�i���o�[�쐬
	//CStageNumber::Create(D3DXVECTOR3(STAGENUMBER_POS_X, STAGENUMBER_POS_Y, 0.0f), D3DXVECTOR3(STAGENUMBER_SIZE_X, STAGENUMBER_SIZE_Y, 0.0f), CStageNumber::STAGE_NUM_2);

	//�Z���t�̐���
	m_pTalkStage2 = CTalkStage2::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//BGM�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_2);

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CStage2::Uninit(void)
{
	//BGM�̏I��
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_STAGE_2);

	CObject::ReleaseAll();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CStage2::Draw(void)
{
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CStage2::Update(void)
{
#ifdef _DEBUG

	//�t�F�C�h�擾
	CFade*	pBlackout = CManager::GetFadeout();
	//�L�[���͎擾
	CInputKeyboard* pInputKey = (CInputKeyboard*)CManager::GetInputKey();

	//�X�e�B�b�N����
	if (pInputKey->GetKeyTrigger(DIK_RETURN))
	{
		pBlackout->SetWhiteout(CGame::MAP_TYPE_3);
	}
#endif

}

//=============================================================================
// �}�b�v�����֐�
//=============================================================================
void CStage2::MapCreate(void)
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
					CSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_GOAL:	//�S�[���n�_
					CHoleBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_2);
					break;
				case BLOCK_TYPE_TILE_SAMD:		//��
					CSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_TILE_SPROUT:	//��
					CSproutBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));					
					break;
				case BLOCK_TYPE_ITEM_SEEDS:		//��
					CSeedsBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					break;
				case BLOCK_TYPE_ITEM_CUBE:		//��
					CLuggageBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CGame::MAP_TYPE_2, false);
					CSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 50.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;
				case BLOCK_TYPE_ITEM_SAMD_WALL:	//����
					CSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 0.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
					CSandBlock::Create(D3DXVECTOR3((float)SQUARE_SIZE * -nBlockX, 50.0f, (float)SQUARE_SIZE * nBlockY), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));

					break;

				}

			}
		}

	}
}

//=============================================================================
// �Z���t�|�C���^�̃Q�b�^�[����
//=============================================================================
CTalkStage2 * CStage2::GetTalkStage2(void)
{
	return m_pTalkStage2;
}