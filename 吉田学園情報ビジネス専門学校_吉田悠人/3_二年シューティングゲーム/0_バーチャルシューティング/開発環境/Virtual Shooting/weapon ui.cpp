//=============================================================================
//
//	�E�F�|��UI[weapon ui.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "weapon ui.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "bullet icon.h"
#include "laser icon.h"
#include "homing icon.h"

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CWeaponUi::m_TextureData = { NULL ,"data/TEXTURE/UI_WeaponFrame.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CWeaponUi::CWeaponUi(int nPriorit) :CScene2d(nPriorit)
{
	m_pWeaponIcon = NULL;

}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CWeaponUi::~CWeaponUi()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CWeaponUi::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CWeaponUi::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CWeaponUi * CWeaponUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CWeaponUi *pWeaponUi;
	pWeaponUi = new CWeaponUi;
	//�ʒu�ݒ�
	pWeaponUi->SetPos(pos);
	//�傫���ݒ�
	pWeaponUi->SetSize(size);
	//�e�N�X�`���̐ݒ�
	pWeaponUi->BindTexture(m_TextureData.m_Texture);
	//����������
	pWeaponUi->Init();

	return pWeaponUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWeaponUi::Init(void)
{
	//����������
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWeaponUi::Uninit(void)
{
	CScene2d::Uninit();
	if (m_pWeaponIcon != NULL)
	{
		m_pWeaponIcon->Uninit();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CWeaponUi::Update(void)
{
	//�A�b�v�f�[�g����
	CScene2d::Update();
	if (m_pWeaponIcon != NULL)
	{
		m_pWeaponIcon->Update();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CWeaponUi::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
	if (m_pWeaponIcon != NULL)
	{
		m_pWeaponIcon->Draw();
	}
}

//=============================================================================
// �^�C�v�Z�b�^�[
//=============================================================================
WEAPON_TYPE CWeaponUi::GetIconType(void)
{
	return m_IconType;
}

//=============================================================================
// �A�C�R���؂�ւ�����
//=============================================================================
void CWeaponUi::TypeChange(WEAPON_TYPE Type)
{
	//���݂̃A�C�R���I������
	if (m_pWeaponIcon != NULL)
	{
		m_pWeaponIcon->Uninit();
		m_pWeaponIcon = NULL;
	}

	//�^�C�v�ύX
	m_IconType = Type;

	//���݂̃A�C�R����������
	switch (m_IconType)
	{
	case WEAPONS_MODE_NONE:
		m_pWeaponIcon = NULL;
		break;
	case WEAPONS_MODE_BUTTOL:
		m_pWeaponIcon = CBulletIcon::Create(GetPos(), GetSize());
		break;
	case WEAPONS_MODE_LASER:
		m_pWeaponIcon = CLaserIcon::Create(GetPos(), GetSize());
		break;
	case WEAPONS_MODE_HOMING:
		m_pWeaponIcon = CHomingIcon::Create(GetPos(), GetSize());
		break;
	}
}

