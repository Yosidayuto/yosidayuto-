//----------------------------------------------
//�w�b�_�[�t�@�C��
//----------------------------------------------
#include "weapon_UI.h"
#include "manager.h"
#include "renderer.h"
#include "ui.h"
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CWeapon_Ui::m_Texture = NULL;
//------------------------------------
//�R���X�g���N�^
//------------------------------------
CWeapon_Ui::CWeapon_Ui(int nPriorit)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pUi = NULL;
}

//------------------------------------
//�f�X�g���N�^
//------------------------------------
CWeapon_Ui::~CWeapon_Ui()
{
}

//------------------------------------
//��������
//------------------------------------
CWeapon_Ui * CWeapon_Ui::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, WEAPON_MODE Type)
{
	CWeapon_Ui *pWeaponUi;
	pWeaponUi = new CWeapon_Ui;	
	pWeaponUi->m_pos = pos;		//�ʒu�ݒ�
	pWeaponUi->m_size = size;	//�T�C�Y�ݒ�
	pWeaponUi->m_Type = Type;
	pWeaponUi->SetPos(pWeaponUi->m_pos);		//�ʒu�擾
	pWeaponUi->SetSize(pWeaponUi->m_size);		//�T�C�Y�擾
	pWeaponUi->BindTexture(pWeaponUi->m_Texture);	//�e�N�X�`���ݒ�
	pWeaponUi->Init();
	return pWeaponUi;
}

//----------------------------------
//�e�N�X�`���ǂݍ��ݏ���
//----------------------------------
HRESULT CWeapon_Ui::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_WeaponFrame.png", &m_Texture);

	return S_OK;
}

//----------------------------------
//�e�N�X�`���j������
//----------------------------------
void CWeapon_Ui::Unload(void)
{
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}

//------------------------------------
//����������
//------------------------------------
HRESULT CWeapon_Ui::Init(void)
{

	switch (m_Type)
	{
	case WEAPONS_MODE_BUTTOL:
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_BULLET);
		break;
	case WEAPONS_MODE_LASER:
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_LASER);
		break;
	case WEAPONS_MODE_HOMING:
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_HOMING);
		break;

	}
	//����������
	CScene2d::Init();


	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CWeapon_Ui::Uninit(void)
{
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = NULL;
	}
	CScene2d::Uninit();

}

//------------------------------------
//�X�V����
//------------------------------------
void CWeapon_Ui::Update(void)
{

	switch (m_Type)
	{
	case WEAPONS_MODE_NONE:
		if (m_pUi != NULL)
		{
			m_pUi->Uninit();
			m_pUi = NULL;
		}
		break;
	case WEAPONS_MODE_BUTTOL:
		if (m_pUi != NULL)
		{
			return;
		}
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_BULLET);

		break;
	case WEAPONS_MODE_LASER:
		if (m_pUi != NULL)
		{
			return;
		}
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_LASER);
		break;
	case WEAPONS_MODE_HOMING:
		if (m_pUi != NULL)
		{
			return;
		}
		m_pUi = CUi::Create(m_pos, m_size, CUi::TEXTURE_TYPE_HOMING);
		break;

	}
}

//------------------------------------
//�`�揈��
//------------------------------------
void CWeapon_Ui::Draw(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	CScene2d::Draw();
	
	if (m_pUi != NULL)
	{
		m_pUi->Draw();
	}
}

void CWeapon_Ui::SetUI(WEAPON_MODE Type)
{
	m_Type = Type;
}

