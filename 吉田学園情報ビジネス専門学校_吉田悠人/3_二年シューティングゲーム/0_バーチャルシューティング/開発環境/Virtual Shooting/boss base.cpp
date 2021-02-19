//=============================================================================
//
// �{�X�x�[�X���� [boss base.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss base.h"
#include "score.h"
#include "game.h"
#include "player.h"
#include "shots base.h"
#include "shots.h"
#include "spiral.h"
#include "buckshot.h"
#include "full range shots.h"
#include "split shots.h"
#include "boss type1.h"
#include "boss type2.h"
#include "boss type3.h"

#include <time.h>


//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossBase::CBossBase(int nPriorit)
{
	m_nLife = 0;
	m_Score = 0;
	m_nCoolTime = 0;
	m_nLimitCoolTime = 0;
	m_pShots = NULL;
	m_Stats = STATS_MODE_NORMAL;
	m_Shots = BOSS_PATTERN_NONE;
	SetObjType(OBJ_TYPE_BOSS);				//�^�C�v����
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossBase::~CBossBase()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossBase::Load(void)
{
	CBossType1::Load();
	CBossType2::Load();
	CBossType3::Load();


	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBossBase::Unload(void)
{
	CBossType1::Unload();
	CBossType2::Unload();
	CBossType3::Unload();

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossBase::Init(void)
{
	//����������
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossBase::Uninit(void)
{
	if (m_pShots!=NULL)
	{
		m_pShots->Uninit();
	}
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossBase::Update(void)
{
	CScene2d::Update();
	//�����蔻��
	Hit();
	//�X�e�[�^�Ǘ�
	StatasManage();

	//�V���b�g�̍X�V
	if (m_pShots != NULL)
	{
		m_pShots->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossBase::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CBossBase::Damage(int nDamage)
{
	//��Ԋm�F
	if (m_Stats == STATS_MODE_NORMAL)
	{
		//���C�t�_���[�W
		m_nLife -= nDamage;

		//���C�t��0�Ȃ�
		if (m_nLife > 0)
		{
			//���S��ԂɈڍs
			m_Stats = STATS_MODE_DAMAGE;
			return;
		}
		//�_���[�W��ԂɈڍs
		m_Stats = STATS_MODE_DEATH;
	}

}

//=============================================================================
// �G�l�~�[�̏�ԊǗ�����
//=============================================================================
void CBossBase::StatasManage(void)
{
	switch (m_Stats)
	{
	case STATS_MODE_NORMAL:

		break;
	case STATS_MODE_DAMAGE:

		m_Stats = STATS_MODE_NORMAL;

		break;
	case STATS_MODE_DEATH:
		//�X�R�A�|�C���^�擾
		CScore *pScore = CGame::GetScore();
		//�X�R�A���Z
		pScore->AddScore(m_Score);
		//�I��
		CBossBase::Uninit();
		break;
	}

}

//=============================================================================
// �V���b�g����
//=============================================================================
void CBossBase::Bullet(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	
	//�U���p�^�[��
	switch (m_Shots)
	{
	case BOSS_PATTERN_NONE:


		//�N�[���^�C������
		if (CoolTime())
		{	
			//�����_���֐��̏�����
			srand((unsigned)time(NULL));
			if (m_pShots == NULL)
			{
				//�����_���Ɏ��̍s�������߂�
				m_Shots = (BOSS_PATTERN)(rand() % BOSS_PATTERN_SPIRAL + BOSS_PATTERN_SHOTS);
			}
		}
		
		break;
	case  BOSS_PATTERN_SHOTS:
		m_pShots = CShots::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;
	case BOSS_PATTERN_All_DIR:
		m_pShots = CFullRange::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;
	case BOSS_PATTERN_BUCKSHOT:
		m_pShots= CBuckShot::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;

	case  BOSS_PATTERN_SPLIT:
		m_pShots = CSplitShots::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;

	case  BOSS_PATTERN_SPIRAL:
		m_pShots = CSpiral::Create(pos);
		m_Shots = BOSS_PATTERN_NONE;
		break;
	}
}

//=============================================================================
// �U�����̃N�[���^�C��
//=============================================================================
bool CBossBase::CoolTime(void)
{

	if (m_pShots!=NULL)
	{
		//�U�����I����Ă�����
		if (m_pShots->GetShotsEnd())
		{
			//�I������
			m_pShots->Uninit();
			m_pShots = NULL;
		}
	}
	//NULL�ł����
	else
	{
		//�N�[���^�C�����Z
		m_nCoolTime++;
	}

	//�N�[���^�C�������ɒB������
	if (m_nCoolTime>= m_nLimitCoolTime)
	{
		//�N�[���^�C���̏�����
		m_nCoolTime = 0;
		return true;
	}
	return false;
}


//=============================================================================
// �����蔻��
//=============================================================================
void CBossBase::Hit(void)
{
	//�I�u�W�F�N�g�擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����I�u�W�F�N�g�̃|�C���^
	CScene* pNext = NULL;
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//�v���C���[�Ƃ̓����蔻��
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���v���C���[�Ȃ�
				if (pNext->GetObjType() == OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					//�����蔻��
					if (Playerpos.x > pos.x - size.x / 2
						&& Playerpos.x  < pos.x + size.x / 2
						&& Playerpos.y > pos.y - size.y / 2
						&& Playerpos.y < pos.y + size.y / 2)
					{
						((CPlayer*)pNext)->Damage(1);
					}
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();

			}
		}

	}

}

//=============================================================================
// �N�[���^�C���Z�b�^�[
//=============================================================================
void CBossBase::SetCoolTime(int nCoolTime)
{
	m_nLimitCoolTime = nCoolTime;
}

//=============================================================================
// �N�[���^�C���Q�b�^�[
//=============================================================================
int CBossBase::GetCoolTime(void)
{
	return m_nLimitCoolTime;
}

//=============================================================================
// ���C�t�Z�b�^�[
//=============================================================================
void CBossBase::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ���C�t�Z�b�^�[
//=============================================================================
int CBossBase::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// �X�R�A�Z�b�^�[
//=============================================================================
void CBossBase::SetScore(int nScore)
{
	m_Score = nScore;
}

//=============================================================================
// �X�R�A�Q�b�^�[
//=============================================================================
int CBossBase::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// �U���p�^�[���Z�b�^�[
//=============================================================================
void CBossBase::SetPattern(BOSS_PATTERN type)
{
	m_Shots = type;
}

//=============================================================================
// �U���p�^�[���Q�b�^�[
//=============================================================================
BOSS_PATTERN CBossBase::GetPattern(void)
{
	return m_Shots;
}
