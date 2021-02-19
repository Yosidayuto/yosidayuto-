//=============================================================================
//
//	�o���b�g�{�^��[bullet button.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "bullet button.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "select.h"
#include "telop.h"
#include "player data.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BULLET_SCORE (5000)	//����X�R�A
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBulletButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Bullet.png", };

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletButton::CBulletButton(int nPriorit)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletButton::~CBulletButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBulletButton::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBulletButton::Unload(void)
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
CBulletButton * CBulletButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBulletButton* pBulletButton;
	pBulletButton = new CBulletButton;

	//�ʒu�ݒ�
	pBulletButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//�T�C�Y�ݒ�
	pBulletButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//�e�N�X�`���ݒ�
	pBulletButton->BindTexture(m_TextureData.m_Texture);
	//����������
	pBulletButton->Init();

	return pBulletButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBulletButton::Init(void)
{
	//�{�^���̏���������
	CButton::Init();
	//�ʒu�ݒ�
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBulletButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBulletButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBulletButton::Draw(void)
{
	CButton::Draw();
}

//=============================================================================
// �}�E�X�I�[�o�[����
//=============================================================================
void CBulletButton::MouseOver(void)
{
	//�X�R�A�����ʎ擾
	CScore*		pMinusScore = CSelect::GetMinusScore();
	//�e���b�v�|�C���^
	CTelop*		pTelop = CSelect::GetTelop();

	//����X�R�A���f
	pMinusScore->SetScore(BULLET_SCORE);
	//�e���b�v�ؑ�
	if (pTelop->GetTelopType() != TELOP_TYPE_BUTTOL)
	{
		pTelop->TypeChange(TELOP_TYPE_BUTTOL);
	}
}

//=============================================================================
// �v�b�V�����菈��
//=============================================================================
void CBulletButton::Push(void)
{
	//�}�E�X�|�C���^�擾
	CInihMouse* pMouse	= CManager::GetMouse();
	//�T�E���h�擾
	CSound*		pSound	= CManager::GetSound();
	//�v���C���[�f�[�^�擾
	CPlayerData*pPlayer = CManager::GetPlayer();
	//�����f�[�^�擾
	WEAPON_DATA WeaponData = pPlayer->GetWeaponData();
	//�X�R�A
	CScore*		pScore = CSelect::GetScore();
	//�擾�X�R�A�f�[�^�擾
	int			nScore	= pScore->GetScore();

	
	//���N���b�N
	if (pMouse->GetClickTrigger(CLICK_LEFT) == true)
	{
		//�v���C���[�̕����ɋ󂫂����邩
		if (WeaponData.Left == WEAPONS_MODE_NONE
			|| WeaponData.Right == WEAPONS_MODE_NONE)
		{
			//���݂̃X�R�A������X�R�A��葽����
			if (nScore >= BULLET_SCORE)
			{
				//�N���b�N��SE
				pSound->Play(CSound::LABEL_SE_CLICK);
				//�X�R�A����
				pScore->AddScore(-BULLET_SCORE);
				//�����ύX
				if (WeaponData.Left == WEAPONS_MODE_NONE)
				{
					//�����ݒ�
					WeaponData.Left = WEAPONS_MODE_BUTTOL;
				}
				else
				{
					//�����ݒ�
					WeaponData.Right = WEAPONS_MODE_BUTTOL;
				}
				//���f
				pPlayer->SetWeaponData(WeaponData);
			}
		}
	}
	//�E�N���b�N
	else if (pMouse->GetClickTrigger(CLICK_RIGHT) == true)
	{
		//�v���C���[�̕����Ƀo���b�g�����邩
		if (WeaponData.Left == WEAPONS_MODE_BUTTOL
			|| WeaponData.Right == WEAPONS_MODE_BUTTOL)
		{
			//�N���b�N��SE
			pSound->Play(CSound::LABEL_SE_CLICK);
			//�X�R�A����
			pScore->AddScore(BULLET_SCORE);
			//�����ύX
			if (WeaponData.Left == WEAPONS_MODE_BUTTOL)
			{
				//�����ݒ�
				WeaponData.Left = WEAPONS_MODE_NONE;
			}
			else
			{
				//�����ݒ�
				WeaponData.Right = WEAPONS_MODE_NONE;
			}
			//���f
			pPlayer->SetWeaponData(WeaponData);
		}
	}
}
