//=============================================================================
//
// �Q�[�� [game.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"
#include "manager.h"
#include "object.h"
#include "camera.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "sound.h"
#include "inputkeyboard.h"
#include "pause.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CGame::MAP_TYPE CGame::m_MapMode = MAP_TYPE_1;
CStageBase* CGame::m_pStage_1	 = NULL;
CStageBase* CGame::m_pStage_2	 = NULL;
CStageBase* CGame::m_pStage_3 	 = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_pCamera		= NULL;
	m_pTalk			= NULL;
	m_pStageNumber	= NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ����������
//=============================================================================

HRESULT CGame::Init(void)
{
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init(D3DXVECTOR3(-200.0f, 0.0f, 200.0f));
	//�J�����ʒu�Z�b�g
	m_pCamera->SetCamera();

	//�I�u�W�F�N�g����
	m_pStage_1 = new CStage1;
	m_pStage_2 = new CStage2;
	m_pStage_3 = new CStage3;

	m_MapMode = MAP_TYPE_1;
	SetMapMode(m_MapMode);
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	switch (m_MapMode)
	{
	case MAP_TYPE_1:
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Update();
		}
		break;
	case MAP_TYPE_2:
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Update();
		}

		break;
	case MAP_TYPE_3:
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Update();
		}

		break;
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}

	//���[�h����
	switch (m_MapMode)
	{
	case MAP_TYPE_1:
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Draw();
		}
		break;
	case MAP_TYPE_2:
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Draw();
		}

		break;
	case MAP_TYPE_3:
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Draw();
		}

		break;
	}

}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	CManager::GetSound()->StopSound();

	CObject::ReleaseAll();
}

//=============================================================================
// �}�b�v���[�h�Z�b�^�[����
//=============================================================================
void CGame::SetMapMode(MAP_TYPE MapMode)
{
	//�|�[�Y�擾
	CPause* pPause = CManager::GetPause();
	
	//NULL�`�F�b�N
	if (pPause != NULL)
	{
		//�|�[�Y�I��
		pPause->Delete();
	}

	//�I������
	switch (m_MapMode)
	{
	case MAP_TYPE_1:	//�X�e�[�W1
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Uninit();
		}
		break;
	case MAP_TYPE_2:	//�X�e�[�W2
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Uninit();
		}
		break;
	case MAP_TYPE_3:	//�X�e�[�W3
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Uninit();
		}
		break;
	}

	//���[�h�ؑ�
	m_MapMode = MapMode;

	//����������
	switch (m_MapMode)
	{
	case MAP_TYPE_1:	//�X�e�[�W1
		if (m_pStage_1 != NULL)
		{
			m_pStage_1->Init();

		}
		break;
	case MAP_TYPE_2:	//�X�e�[�W2
		if (m_pStage_2 != NULL)
		{
			m_pStage_2->Init();

		}
		break;
	case MAP_TYPE_3:	//�X�e�[�W3
		if (m_pStage_3 != NULL)
		{
			m_pStage_3->Init();

		}
		break;

	}

}

//=============================================================================
// �}�b�v���[�h�Q�b�^�[����
//=============================================================================
CGame::MAP_TYPE CGame::GetMapMode(void)
{
	return m_MapMode;
}
