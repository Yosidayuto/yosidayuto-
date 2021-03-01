//=============================================================================
//
// �G�l�~�[�x�[�X���� [enemy base.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy base.h"
#include "score.h"
#include "game.h"
#include "player.h"
#include "enemy type1.h"
#include "enemy type2.h"
#include "enemy type3.h"
#include "enemy type4.h"
#include "shots.h"
#include "spiral.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_HIT_DAMAGE (1)	//�v���C���[�ɂԂ��������̃_���[�W
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CEnemyBase::CEnemyBase(int nPriorit)
{
	//m_nMoveCount	= 0;
	//m_nPointer	= 0;
	m_nInTime		= 0;
	m_nLife			= 0;
	m_Score			= 0;
	m_nCount		= 0;
	m_bAttack		= false;
	m_fRot			= 0.0f;
	m_Stats			= STATS_MODE_NORMAL;
	m_Shots			= BULLET_PATTERN_NONE;
	m_pShotsBase	= NULL;

	//memset(m_fSpeed, NULL, sizeof(m_fSpeed));
	//memset(m_movePointer, NULL, sizeof(m_movePointer));
	SetObjType(OBJ_TYPE_ENEMY);				//�^�C�v����
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CEnemyBase::~CEnemyBase()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CEnemyBase::Load(void)
{
	CEnemyType1::Load();
	CEnemyType2::Load();
	CEnemyType3::Load();
	CEnemyType4::Load();

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CEnemyBase::Unload(void)
{
	CEnemyType1::Unload();
	CEnemyType2::Unload();
	CEnemyType3::Unload();
	CEnemyType4::Unload();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyBase::Init(void)
{
	//����������
	CScene2d::Init();
	////�����ʒu�擾
	//SetMovePointer(GetPos(), 0, 0.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyBase::Uninit(void)
{
	if (m_pShotsBase!=NULL)
	{
		m_pShotsBase->Uninit();
		m_pShotsBase = NULL;
	}
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyBase::Update(void)
{
	CScene2d::Update();
	//�J�E���g�A�b�v
	m_nCount++;

	//�����蔻��
	Hit();
	//�ړ�����
	Move();
	//�X�e�[�^�Ǘ�
	StatasManage();
	//�V���b�g�̍X�V
	if (m_pShotsBase!=NULL)
	{
		m_pShotsBase->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyBase::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CEnemyBase::Damage(int nDamage)
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
void CEnemyBase::StatasManage(void)
{
	switch (m_Stats)
	{
	case STATS_MODE_NORMAL:
		//�_���[�W�J���[����
		//SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		//�_���[�W�J���[����
		//SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));

		m_Stats = STATS_MODE_NORMAL;

		break;
	case STATS_MODE_DEATH:
		//�X�R�A�|�C���^�擾
		CScore *pScore = CGame::GetScore();
		//�X�R�A���Z
		pScore->AddScore(m_Score);
		//�I��
		CEnemyBase::Uninit();
		break;
	}

}

//=============================================================================
// ��]����
//=============================================================================
void CEnemyBase::Rotate(void)
{
	
	//�����Z�b�g
	SetRot(m_fRot);
	//��]�p�x�v���X
	m_fRot += 2.0f;
	//��]�p�x�����ɒB������
	if (m_fRot>360.0f)
	{
		//�p�x������
		m_fRot = 0;
	}

}

//=============================================================================
// �V���b�g����
//=============================================================================
void CEnemyBase::Bullet(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	
	//�J�E���g���U�����Ԃ��߂����
	if (m_nCount>m_nAttackTime)
	{
		//�U�������Ă��邩
		if (!m_bAttack)
		{
			//�U���̃^�C�v����
			switch (m_Shots)
			{
			case BULLET_PATTERN_SHOTS:
				m_pShotsBase = CShots::Create(this);
				m_Shots = BULLET_PATTERN_NONE;
				break;
			case BULLET_PATTERN_SPIRAL:
				m_pShotsBase = CSpiral::Create(this);
				m_Shots = BULLET_PATTERN_NONE;
				break;
			}
			m_bAttack = true;
		}
	}

}

//=============================================================================
// �����蔻��
//=============================================================================
void CEnemyBase::Hit(void)
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
						((CPlayer*)pNext)->Damage(PLAYER_HIT_DAMAGE);
					}
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();

			}
		}

	}

}

//=============================================================================
// �ړ�����
//=============================================================================
void CEnemyBase::Move(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�ړ��ʒu
	//if (m_nMoveCount<m_nPointer+1)
	//{
	//	//�ڕW�̈ʒu�����擾
	//	fAngle = atan2f((-pos.x + m_movePointer[m_nMoveCount].x), (-pos.y + m_movePointer[m_nMoveCount].y));
	//	//�ڕW�܂ł̈ړ�
	//	m_move.x = sinf(fAngle) * m_fSpeed[m_nMoveCount];
	//	m_move.y = cosf(fAngle) * m_fSpeed[m_nMoveCount];
	//	//�ʒu�X�V
	//	pos += m_move;
	//	//�ʒu�ݒ�
	//	SetPos(pos);
	//
	//	
	//	if (pos.x + 5.0f>m_movePointer[m_nMoveCount].x
	//		&&pos.x - 5.0f<m_movePointer[m_nMoveCount].x
	//		&&pos.y + 5.0f>m_movePointer[m_nMoveCount].y
	//		&&pos.y - 5.0f<m_movePointer[m_nMoveCount].y)
	//	{
	//		//���̈ʒu
	//		m_nMoveCount++;
	//	}
	//}

	//�o�����Ԃ��߂��Ă���s������
	if (m_nCount>m_nInTime)
	{
		//�s���p�^�[��
		switch (m_MovePattern)
		{
		case ENEMY_MOVE_RETURN:		//U�^�[��
			//�J�E���g���A�N�V�����^�C�����z���Ă��Ȃ��Ƃ�
			if (m_nCount<m_nActionTime
				&&m_nCount < m_nOutTime)
			{
				//�ړ��ʃZ�b�g
				pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			}
			//�J�E���g�����ɂȂ�����
			if (m_nCount > m_nOutTime)
			{
				//�ړ��ʃZ�b�g
				pos += D3DXVECTOR3(0.0f, -1.0f, 0.0f)*m_fSpped;
			}
			//�ʒu�Z�b�g
			SetPos(pos);
			break;

			
		case ENEMY_MOVE_STRAIGHT:	//���i
			//�ړ��ʃZ�b�g
			pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			//�ʒu�Z�b�g
			SetPos(pos);
			break;

		case ENEMY_MOVE_RIGHT:		//�E�ɋȂ���
			//�ړ��ʃZ�b�g
			pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			//�J�E���g�����ɒB������
			if (m_nCount>m_nActionTime)
			{
				//�ړ��ʃZ�b�g
				pos.x += 3.0;
			}
			//�ʒu�Z�b�g
			SetPos(pos);
			break;

		case ENEMY_MOVE_LEFT:		//���ɋȂ���
			//�ړ��ʃZ�b�g
			pos += D3DXVECTOR3(0.0f, 1.0f, 0.0f)*m_fSpped;
			//�J�E���g�����ɒB������
			if (m_nCount>m_nActionTime)
			{
				//�ړ��ʃZ�b�g
				pos.x += -3.0;
			}
			//�ʒu�Z�b�g
			SetPos(pos);

			break;

		case ENEMY_MOVE_RIGHT_SLIDE://�E�Ɍ������ĉ��ړ�
			//�ړ��ʃZ�b�g
			pos += D3DXVECTOR3(1.0f, 0.0f, 0.0f)*m_fSpped;
			//�ʒu�Z�b�g
			SetPos(pos);
			break;

		case ENEMY_MOVE_LEFT_SLIDE:	//���Ɍ������ĉ��ړ�
			//�ړ��ʃZ�b�g
			pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*m_fSpped;
			//�ʒu�Z�b�g
			SetPos(pos);
			break;

		case ENEMY_MOVE_RIGHT_STOP:	//�E�Ɍ������ĉ��ړ�(�r���ň�x�~�܂�)
			//�J�E���g���A�N�V�����^�C�����z���Ă��Ȃ��Ƃ�
			if (m_nCount<m_nActionTime
				&&m_nCount < m_nOutTime)
			{
				//�ړ��ʃZ�b�g
				pos += D3DXVECTOR3(1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//�J�E���g�����ɂȂ�����
			if (m_nCount > m_nOutTime)
			{
				//�ړ��ʃZ�b�g
				pos += D3DXVECTOR3(1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//�ʒu�Z�b�g
			SetPos(pos);
			break;
		
		case ENEMY_MOVE_LEFT_STOP:	//���Ɍ������ĉ��ړ�(�r���ň�x�~�܂�)
			//�J�E���g���A�N�V�����^�C�����z���Ă��Ȃ��Ƃ�
			if (m_nCount<m_nActionTime
				&&m_nCount < m_nOutTime)
			{
				//�ړ��ʃZ�b�g
				pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//�J�E���g�����ɂȂ�����
			if (m_nCount > m_nOutTime)
			{
				//�ړ��ʃZ�b�g
				pos += D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*m_fSpped;
			}
			//�ʒu�Z�b�g
			SetPos(pos);
			break;
		}
	}

	//��ʊO����
	if (pos.y > SCREEN_HEIGHT + (size.y / 2)					// ��ʉ�
		|| pos.y< 0 - (size.y / 2)								// ��ʏ�
		|| pos.x >(STAGE_POS + STAGE_SIZE / 2) + (size.x / 2)	// ��ʉE
		|| pos.x < (STAGE_POS - STAGE_SIZE / 2) - (size.x / 2))	// ��ʍ�
	{
		//�A�N�V�����J�E���g��0�ɂȂ��Ă�����
		if (m_nCount >= m_nActionTime)
		{
			//�I��
			CEnemyBase::Uninit();

		}
	}

}

//=============================================================================
// �s���p�^�[���Z�b�^�[
//=============================================================================
void CEnemyBase::SetMovePattern(ENEMY_MOVE_PATTERN MovePattern)
{
	m_MovePattern =	MovePattern;
}

//=============================================================================
// �U���p�^�[���Z�b�^�[
//=============================================================================
void CEnemyBase::SetAttackPattern(ENEMY_ATTACK_PATTERN AttackPaattern)
{
	m_Shots = AttackPaattern;
}

//=============================================================================
// �o�����ԃZ�b�^�[
//=============================================================================
void CEnemyBase::SetInTime(int nInTime)
{
	m_nInTime = nInTime;
}

//=============================================================================
// �s�����ԃZ�b�^�[
//=============================================================================
void CEnemyBase::SetActionTime(int nActionTime)
{
	m_nActionTime = nActionTime;
}

//=============================================================================
// �U�����ԃZ�b�^�[
//=============================================================================
void CEnemyBase::SetAttackTime(int nAttackTime)
{
	m_nAttackTime = nAttackTime;
}

//=============================================================================
// �A�Ҏ��ԃZ�b�^�[
//=============================================================================
void CEnemyBase::SetOutTime(int nOutTime)
{
	m_nOutTime = nOutTime;
}

//=============================================================================
// ���C�t�Z�b�^�[
//=============================================================================
void CEnemyBase::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ���C�t�Z�b�^�[
//=============================================================================
int CEnemyBase::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// �X�R�A�Z�b�^�[
//=============================================================================
void CEnemyBase::SetScore(int nScore)
{
	m_Score = nScore;
}

//=============================================================================
// �X�R�A�Q�b�^�[
//=============================================================================
int CEnemyBase::GetScore(void)
{
	return m_Score;
}

//=============================================================================
// �X�s�[�h�Z�b�^�[
//=============================================================================
void CEnemyBase::SetSpeed(float nSpeed)
{
	m_fSpped = nSpeed;
}

//=============================================================================
// �X�s�[�h�Q�b�^�[
//=============================================================================
float CEnemyBase::GetSpeed(void)
{
	return m_fSpped;
}

