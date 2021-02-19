//=============================================================================
//
// �X�e�[�W3���� [stage_3.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stage_3.h"
#include "manager.h"
#include "sound.h"
#include "enemy.h"
#include "boss.h"
#include "warning.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CStage3::CStage3()
{
	m_EnemyCreate = ENEMY_CREATE_NONE;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CStage3::~CStage3()
{
}

//=============================================================================
// ��������
//=============================================================================
CStage3 * CStage3::Create(void)
{
	//�������̊m��
	CStage3* pStage3;
	pStage3 = new CStage3;
	//����������
	pStage3->Init();
	return pStage3;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStage3::Init(void)
{
	//�T�E���h�N���X�擾
	CSound *pSound = CManager::GetSound();
	//�T�E���h�Đ�
	pSound->Play(CSound::LABEL_BGM_STAGE_1);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStage3::Uninit(void)
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
void CStage3::Update(void)
{
	CStage::Update();
}

//=============================================================================
// �G�l�~�[�̃X�|�[�����[�h
//=============================================================================
void CStage3::StageMode(void)
{
	//�T�E���h�|�C���^�擾
	CSound *pSound = CManager::GetSound();
	//�X�e�[�W�i�s
	m_EnemyCreate = (STAGE_3_ENEMY)(m_EnemyCreate + 1);

	//780���S�@��400
	switch (m_EnemyCreate)
	{
	case ENEMY_CREATE_1:
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
	
		SetEnemyCount(350);
		break;
	case ENEMY_CREATE_2:
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_1, D3DXVECTOR3(500, 500, 0));
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_3:
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
	
		SetEnemyCount(300);
		break;
	case ENEMY_CREATE_4:
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_2, D3DXVECTOR3(500, 500, 0));
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_5:
		//�T�E���h�X�g�b�v
		pSound->Stop(CSound::LABEL_BGM_STAGE_3);
	
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(800, 200, 0.0f));
	
		SetEnemyCount(300);
		break;
	case ENEMY_CREATE_6:
		//�T�E���h�Đ�
		pSound->Play(CSound::LABEL_BGM_BOSS_3);
	
		CBoss::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f), CBoss::BOSS_TYPE_3, D3DXVECTOR3(500, 500, 0));
	
		SetEnemyCount(450);
		break;
	case ENEMY_CREATE_7:
		//���U���g�\��
		Result(STAGE_TYPE_3);
		break;
	}
}
