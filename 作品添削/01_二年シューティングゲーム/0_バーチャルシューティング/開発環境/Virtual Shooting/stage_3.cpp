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
#include "boss base.h"
#include "boss type1.h"
#include "boss type2.h"
#include "boss type3.h"
#include "warning.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PHASE_COUNT (200)	//�t�F�[�Y���ʒu�i�K�ς��܂ł̃J�E���g��

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CStage3::CStage3()
{
	m_EnemyCreate = ENEMY_CREATE_NULL;
	m_nBossPhase = 0;
	memset(&m_StageData, NULL, sizeof(m_StageData));
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
	CStage3* pStage3 = NULL;
	pStage3 = new CStage3;

	//NULL�`�F�b�N
	if (pStage3 != NULL)
	{
		//����������
		pStage3->Init();
	}
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
	pSound->Play(CSound::LABEL_BGM_STAGE_3);
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
	m_EnemyCreate = (STAGE_ENEMY)(m_EnemyCreate + 1);

	//�t�F�[�Y����
	switch (m_EnemyCreate)
	{
	case ENEMY_CREATE_1:
		//���[�j���O����
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));
		break;
	case ENEMY_CREATE_2:
		//�{�X����
		CBossType1::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
		break;
	case ENEMY_CREATE_3:
		//���[�j���O����
		CWarning::Create(D3DXVECTOR3(STAGE_POS, SCREEN_HEIGHT / 2, 0.0f));
		break;
	case ENEMY_CREATE_4:
		//�{�X����
		CBossType2::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
		break;
	case ENEMY_CREATE_5:
		//�{�X���o
		WarningCreate();
		break;
	case ENEMY_CREATE_6:
		//�T�E���h�Đ�
		pSound->Play(CSound::LABEL_BGM_BOSS_3);
		//�{�X����
		CBossType3::Create(D3DXVECTOR3(STAGE_POS, 100, 0.0f));
		break;
	case ENEMY_CREATE_7:
		//���U���g�\��
		Result(STAGE_TYPE_3);
		break;
	}
	SetEnemyCount(PHASE_COUNT);
}
