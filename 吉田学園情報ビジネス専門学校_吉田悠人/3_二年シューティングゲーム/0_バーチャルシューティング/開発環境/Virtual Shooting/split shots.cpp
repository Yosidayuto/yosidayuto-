//=============================================================================
//
// ����V���b�g���� [split shots.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"
#include "split shots.h"
#include "enemy bullet.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SHOTS_FIRST_SPEED	(3.5f)	// ���e�̒e��
#define SHOTS_SPEED			(0.7f)	// ���e�ȊO�̒e��

#define SHOTS_NUMBER		(10)	// �V���b�g�̉�
#define SHOTS_TIME			(20)	// �U���̎��Ԃ̊Ԋu

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CSplitShots::CSplitShots()
{
	m_pEnemyBullet = NULL;
	m_nBullet = 0;
	memset(m_bBullet, false, sizeof(m_bBullet));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CSplitShots::~CSplitShots()
{
}

//=============================================================================
// ��������
//=============================================================================
CSplitShots * CSplitShots::Create(D3DXVECTOR3 pos)
{
	//�������̊m��
	CSplitShots* pSplitShots;
	pSplitShots = new CSplitShots;
	//�ʒu�ݒ�
	pSplitShots->SetPos(pos);
	//�����ݒ�
	pSplitShots->Tracking(SHOTS_SPEED);
	//����������
	pSplitShots->Init();

	return pSplitShots;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSplitShots::Init(void)
{
	CShotsBase::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSplitShots::Uninit(void)
{
	CShotsBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSplitShots::Update(void)
{
	CShotsBase::Update();
}

//=============================================================================
// �V���b�g����
//=============================================================================
void CSplitShots::Shots(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�J�E���g�v���X
	m_nBullet++;

	//�V���b�g����
	if (m_pEnemyBullet==NULL)
	{
		m_pEnemyBullet = CEnemyBullet::Create(pos, D3DXVECTOR3(0.0f, SHOTS_FIRST_SPEED, 0.0f));
	}
	//���e��NULL�`�F�b�N
	if (m_pEnemyBullet != NULL)
	{
		//10�񕪂̃V���b�g����
		for (int nNumber = 0; nNumber<SHOTS_NUMBER; nNumber++)
		{
			if (m_nBullet == (SHOTS_TIME)  * (nNumber))
			{
					//���e���ʂ�����ɉE���ɒe������
					CEnemyBullet::Create(m_pEnemyBullet->GetPos(), D3DXVECTOR3(SHOTS_SPEED, 0.0f, 0.0f));
					CEnemyBullet::Create(m_pEnemyBullet->GetPos(), D3DXVECTOR3(-SHOTS_SPEED, 0.0f, 0.0f));
					m_bBullet[nNumber] = true;
					m_bBullet[SHOTS_NUMBER + nNumber] = true;

			}
		}
	}
	//�I��
	if (m_bBullet[MAX_SPLIT_SHOTS - 1] == true)
	{
		SetShotsEnd(true);
		return;
	}
}
