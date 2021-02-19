//=============================================================================
//
// �S���ʃV���b�g���� [full range shots.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"
#include "full range shots.h"
#include "enemy bullet.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SHOTS_SPEED			(4.0f)		//�e��
#define SHOTS_NUMBER		(10)		//�V���b�g�̉�
#define SHOTS_BULLET		(20)		//���Ɍ��e�ې�

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CFullRange::CFullRange()
{
	m_nBullet = 0;
	memset(m_bBullet, false, sizeof(m_bBullet));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CFullRange::~CFullRange()
{
}

//=============================================================================
// ��������
//=============================================================================
CFullRange * CFullRange::Create(D3DXVECTOR3 pos)
{
	//�������̊m��
	CFullRange* pFullRange;
	pFullRange = new CFullRange;
	//�ʒu�ݒ�
	pFullRange->SetPos(pos);
	//�����ݒ�
	pFullRange->Tracking(SHOTS_SPEED);
	//����������
	pFullRange->Init();

	return pFullRange;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFullRange::Init(void)
{
	CShotsBase::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFullRange::Uninit(void)
{
	CShotsBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFullRange::Update(void)
{
	CShotsBase::Update();
}

//=============================================================================
// �V���b�g����
//=============================================================================
void CFullRange::Shots(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�J�E���g�v���X
	m_nBullet++;

	//�V���b�g����
	for (int nNumber = 0; nNumber < SHOTS_NUMBER; nNumber++)
	{
		//�\��̊Ԋu�̏���
		if (m_nBullet == SHOTS_NUMBER * nNumber)
		{
			//���Ɍ��������e�̏���
			for (int nBullet = 0; nBullet < SHOTS_BULLET; nBullet++)
			{
				//������ݒ�
				rot.x = sinf(Tracking() + (2.0f*nBullet + (SHOTS_BULLET*(nNumber + 1))))*SHOTS_SPEED;
				rot.y = cosf(Tracking() + (2.0f*nBullet + (SHOTS_BULLET*(nNumber + 1))))*SHOTS_SPEED;
				//�o���b�g����
				CEnemyBullet::Create(pos, rot);
				//�o���b�g�g�p��Ԃ�
				m_bBullet[nBullet + (SHOTS_BULLET*(nNumber + 1))] = true;

			}
		}
	}

	//�I��
	if (m_bBullet[MAX_FULL_RANGE-1] == true)
	{
		SetShotsEnd(true);
		return;
	}
}

