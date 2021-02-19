//=============================================================================
//
// �V���b�g �x�[�X���� [shots base.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CShotsBase::CShotsBase()
{
	memset(m_rot, NULL, sizeof(m_rot));	//�ړ���
	memset(m_pos, NULL, sizeof(m_pos));	//�ʒu
	m_bShotsEnd = false;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CShotsBase::~CShotsBase()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShotsBase::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShotsBase::Uninit(void)
{
	delete this;
}

//=============================================================================
// �X�V����
//=============================================================================
void CShotsBase::Update(void)
{
	Shots();
}


//=============================================================================
// ����������
//=============================================================================
void CShotsBase::Tracking(float fSpeed)
{
	//�V�[���擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����V�[���|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}
	//�v���C���[�̕���
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���v���C���[�Ȃ�
				if (pNext->GetObjType() == CScene::OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
					m_rot.x = sinf(fAngle)*fSpeed;
					m_rot.y = cosf(fAngle)*fSpeed;
					return;
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}

}

float CShotsBase::Tracking(void)
{
	//�V�[���擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����V�[���|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}
	//�v���C���[�̕���
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���v���C���[�Ȃ�
				if (pNext->GetObjType() == CScene::OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
					return fAngle;
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}
	return 0.0f;
}

//=============================================================================
// �����_���Ȍ����擾����
//=============================================================================
void CShotsBase::Random(float fSpeed)
{
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);;
	//�V�[���擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����V�[���|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}
	//�v���C���[�̕���
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���v���C���[�Ȃ�
				if (pNext->GetObjType() == CScene::OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fRandom = (float)(rand() % 1500 + 1);
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y)) + (float)fRandom / 1000.0f - 0.75f;

					m_rot.x = sinf(fAngle)*fSpeed;
					m_rot.y = cosf(fAngle)*fSpeed;

					return;
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}



}

//=============================================================================
// �����Z�b�^�[
//=============================================================================
void CShotsBase::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �����Q�b�^�[
//=============================================================================
D3DXVECTOR3 CShotsBase::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �ʒu�Z�b�^�[
//=============================================================================
void CShotsBase::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �ʒu�Q�b�^�[
//=============================================================================
D3DXVECTOR3 CShotsBase::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// �����I��������̃Z�b�^�[
//=============================================================================
void CShotsBase::SetShotsEnd(bool bShots)
{
	m_bShotsEnd = bShots;
}

//=============================================================================
// �����I��������̃Q�b�^�[
//=============================================================================
bool CShotsBase::GetShotsEnd(void)
{
	return m_bShotsEnd;
}
