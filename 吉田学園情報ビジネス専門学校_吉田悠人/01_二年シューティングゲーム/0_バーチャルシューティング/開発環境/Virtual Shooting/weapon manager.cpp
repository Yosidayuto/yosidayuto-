//=============================================================================
//
//	�E�F�|���}�l�[�W���[[weapon manager.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "weapon manager.h"
#include "weapon ui.h"
#include "player data.h"
#include "manager.h"
#include "bullet icon.h"
#include "laser icon.h"
#include "homing icon.h"
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CWeaponManager::CWeaponManager()
{
	ZeroMemory(m_pWeaponUi, sizeof(m_pWeaponUi));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CWeaponManager::~CWeaponManager()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CWeaponManager::Load(void)
{
	CBulletIcon::Load();
	CWeaponUi::Load();
	CLaserIcon::Load();
	CHomingIcon::Load();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CWeaponManager::Unload(void)
{
	CBulletIcon::Unload();
	CWeaponUi::Unload();
	CLaserIcon::Unload();
	CHomingIcon::Unload();
}

//=============================================================================
// ��������
//=============================================================================
CWeaponManager * CWeaponManager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������̊m��
	CWeaponManager* pWeaponManager = NULL;
	pWeaponManager = new CWeaponManager;
	//NULL�`�F�b�N
	if (pWeaponManager != NULL)
	{
		//�ʒu�ݒ�
		pWeaponManager->m_pos = pos;
		//�T�C�Y�ݒ�
		pWeaponManager->m_size = size;
		//����������
		pWeaponManager->Init();
	}
	return pWeaponManager;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWeaponManager::Init(void)
{
	
	//UI����
	for (int nCountWeapon = 0; nCountWeapon < MAX_WEAPON; nCountWeapon++)
	{
		//UI�̉���
		int Interval =(int)((m_size.x * nCountWeapon)*1.5f);
		//����
		m_pWeaponUi[nCountWeapon] = CWeaponUi::Create(D3DXVECTOR3(m_pos.x + Interval, m_pos.y, m_pos.z), m_size);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWeaponManager::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CWeaponManager::Update(void)
{
	CPlayerData *pPlayer = CManager::GetPlayer();
	if (m_pWeaponUi[0] != NULL)
	{
		//������
		if (m_pWeaponUi[0]->GetIconType() != pPlayer->GetWeaponData().Left)
		{
			m_pWeaponUi[0]->TypeChange(pPlayer->GetWeaponData().Left);
		}

	}
	if (m_pWeaponUi[1] != NULL)
	{
		//�E����
		if (m_pWeaponUi[1]->GetIconType() != pPlayer->GetWeaponData().Right)
		{
			m_pWeaponUi[1]->TypeChange(pPlayer->GetWeaponData().Right);
		}

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CWeaponManager::Draw(void)
{
}
