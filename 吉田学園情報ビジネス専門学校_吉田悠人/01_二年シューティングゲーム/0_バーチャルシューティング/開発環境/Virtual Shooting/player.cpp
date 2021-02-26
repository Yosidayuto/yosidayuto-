//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"		
#include "player data.h"
#include "input.h"			
#include "inihkeyboard.h"	
#include "inputmouse.h"		
#include "manager.h"		
#include "bullet.h"			
#include "renderer.h"		
#include "sound.h"			
#include "life.h"			
#include "game.h"			
#include "laser.h"			
#include "homing.h"			
#include "fade.h"			
#include "explosion.h"		
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_DAMAGE		(100)	//�_���[�W��Ԃ̍ő喳�G����
#define PLAYER_BULLET_TIME	(20)	//�o���b�g�̃N�[���^�C��
#define PLAYER_LASER_TIME	(30)	//���[�U�[�̃N�[���^�C��
#define PLAYER_HOMING_TIME	(35)	//�z�[�~���O�̃N�[���^�C��

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CPlayer::m_TextureData = {NULL,"data/TEXTURE/Player.png" };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CPlayer::CPlayer(int nPriorit) :CScene2d(nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_PLAYER);	
	Stats		= STATS_MODE_NONE;
	m_nLife		= NULL;
	m_fSpeed	= NULL;
	memset(&m_Weapon, NULL, sizeof(m_Weapon));
	ZeroMemory(m_nAttackCount, sizeof(m_nAttackCount));
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CPlayer::~CPlayer()
{
}


//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CPlayer::Load(void)
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
void CPlayer::Unload(void)
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
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos)
{
	//�������m��
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;

	//NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		//�ʒu�ݒ�
		pPlayer->SetPos(Pos);
		//�T�C�Y�ݒ�
		pPlayer->SetSize(D3DXVECTOR3(PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f, 0.0f));
		//���C�t�ݒ�
		pPlayer->SetLife(PLAYER_LIFE + CManager::GetPlayer()->GetLifeData());
		//�X�s�[�h�ݒ�
		pPlayer->SetSpeed(PLAYER_SPEED + CManager::GetPlayer()->GetSpeedData());
		//�E�F�|���ݒ�
		pPlayer->SetWeapon(CManager::GetPlayer()->GetWeaponData());
		//����������
		pPlayer->Init();

	}

	return pPlayer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//��Ԑݒ�
	Stats = STATS_MODE_NORMAL;
	//����������
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData.m_Texture);
	//���C�t�\�L
	pLife = CLife::Create(D3DXVECTOR3(100, 100, 0.0f));
	if (pLife != NULL)
	{
		pLife->SetLife(m_nLife);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �}�E�X�擾
	CInihMouse *pMouse	= CManager::GetMouse();			
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	if (Stats!= STATS_MODE_NONE)
	{
		//�U������
		Weapon();

		//�ړ�����
		Move();

		//�A�b�v�f�[�g����
		CScene2d::Update();

		//��ԊǗ�
		StatasManage();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	if (Stats != STATS_MODE_NONE)
	{
		//�`�揈��
		CScene2d::Draw();
	}
}


//=============================================================================
// �_���[�W����
//=============================================================================
void CPlayer::Damage(int nDamage)
{
	if (Stats == STATS_MODE_NORMAL)
	{
		//���C�t�_���[�W
		m_nLife -= nDamage;
		//���C�t�\������
		pLife->DownLife(nDamage);
		//��ԕϊ�
		if (m_nLife > 0)
		{
			//�_���[�W��ԂɈڍs
			Stats = STATS_MODE_DAMAGE;
		}
		else
		{
			//���S��ԂɈڍs
			Stats = STATS_MODE_DEATH;
		}
	}

}

//=============================================================================
// �Z�b�g���C�t
//=============================================================================
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// �Z�b�g���C�t
//=============================================================================
void CPlayer::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// �Z�b�g�E�F�|��
//=============================================================================
void CPlayer::SetWeapon(WEAPON_DATA wepon)
{
	m_Weapon = wepon;
}

//=============================================================================
// ���C�t�Q�b�^�[
//=============================================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// �X�s�[�h�Q�b�^�[
//=============================================================================
float	CPlayer::GetSpeed(void)		
{
	return m_fSpeed;
}

//=============================================================================
// �E�F�|���Q�b�^�[
//=============================================================================
WEAPON_DATA CPlayer::GetWeapon(void)
{
	return m_Weapon;
}

//=============================================================================
//��ԊǗ�����
//=============================================================================
void CPlayer::StatasManage(void)
{
	//�_���[�W��Ԃ̖��G����
	static int nDamageTime = 0;

	//���
	switch (Stats)
	{
		//�ʏ���
	case STATS_MODE_NORMAL:
		break;
		//�_���[�W����
	case STATS_MODE_DAMAGE:
		
		//�J�E���g�_�E��
		nDamageTime += 1;

		//�_���[�W�J���[����
		if (nDamageTime % 25)
		{
			SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// �_���[�W�J�E���g�����ɂȂ�����
		if (nDamageTime >= PLAYER_DAMAGE)
		{
			//�J���[�Z�b�g
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//�v���C���[��Ԃ�ʏ��ԂɈڍs
			Stats = STATS_MODE_NORMAL;
			//�_���[�W������
			nDamageTime = 0;
		}
		break;

	case STATS_MODE_DEATH:
		//�T�E���h�N���X�󂯎��
		CSound *pSound = CManager::GetSound();
		//�t�F�[�h�擾	
		CFade *pFade = CManager::GetFade();

		//�T�E���h�̍Đ�
		pSound->Play(CSound::LABEL_SE_DIE);
		
		//�G�N�X�v���[�W��������
		CExplosion::Create(GetPos());

		//�Z���N�g�ړ�
		pFade->SetFade(GAME_MODE_SELECT);
		
		//�I������
		CPlayer::Uninit();
		break;
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos			= GetPos();
	// �ړ���
	D3DXVECTOR3 Move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �͈͊O�����p
	D3DXVECTOR3 MoveLimit	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �}�E�X�擾
	CInihMouse *pMouse = CManager::GetMouse();

	//�}�E�X�̍��W�擾
	float fAngle = atan2f((-pos.x + pMouse->GetMousePos().x), (-pos.y + pMouse->GetMousePos().y));

	//�ʒu���̎󂯓n��
	Move.x = sinf(fAngle)*m_fSpeed;
	Move.y = cosf(fAngle)*m_fSpeed;

	//�ʒu����
	if (pos.x + 5 > pMouse->GetMousePos().x
		&&pos.x - 5 < pMouse->GetMousePos().x
		&&pos.y + 5 > pMouse->GetMousePos().y
		&&pos.y - 5 < pMouse->GetMousePos().y)
	{
	
	}
	else
	{
		//�ʒu�X�V
		pos += Move;
	}

	//�͈͊O����
	if (pos.x < 420 || pos.x > 1145)
	{
		MoveLimit.x = sinf(fAngle)*m_fSpeed;
	}
	if (pos.y < 25 || pos.y > 700)
	{
		MoveLimit.y = cosf(fAngle)*m_fSpeed;
	}

	//�͈͊O�ɂ����Ȃ��悤��
	pos -= MoveLimit;

	//���W�X�V
	SetPos(pos);
}


//=============================================================================
//�v���C���[�̕���g�p
//=============================================================================
void CPlayer::Weapon(void)
{
	// �}�E�X�擾
	CInihMouse *pMouse	= CManager::GetMouse();
	// �ʒu�擾
	D3DXVECTOR3 pos		= GetPos();

	//���N���b�N����
	if (pMouse->GetClick(CLICK_LEFT))
	{
		//�U���܂ł̃J�E���g
		m_nAttackCount[CLICK_LEFT]++;

		//�����ɂ���čU����ς���
		switch (m_Weapon.Left)
		{
			//�ʏ�e����
		case WEAPONS_MODE_BUTTOL:
			if (m_nAttackCount[CLICK_LEFT] >= PLAYER_BULLET_TIME)
			{
				//�o���b�g����
				CBullet::Create(D3DXVECTOR3(pos.x - 20, pos.y, pos.z), D3DXVECTOR3(0, -20, 0.0f));
				//�J�E���g������
				m_nAttackCount[CLICK_LEFT] = 0;
			}
			break;
			//���[�U�[����
		case WEAPONS_MODE_LASER:
			if (m_nAttackCount[CLICK_LEFT] >= PLAYER_LASER_TIME)
			{
				//���[�U�[����
				CLaser::Create(D3DXVECTOR3(pos.x - 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//�J�E���g������
				m_nAttackCount[CLICK_LEFT] = 0;
			}
			break;
			//�z�[�~���O�e����
		case WEAPONS_MODE_HOMING:
			if (m_nAttackCount[CLICK_LEFT] >= PLAYER_HOMING_TIME)
			{
				//�z�[�~���O����
				CHoming::Create(D3DXVECTOR3(pos.x - 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//�J�E���g������
				m_nAttackCount[CLICK_LEFT] = 0;
			}
			break;
		default:
			break;
		}
	}

	//�E�N���b�N����
	if (pMouse->GetClick(CLICK_RIGHT))
	{
		//�U���܂ł̃J�E���g
		m_nAttackCount[CLICK_RIGHT]++;

		switch (m_Weapon.Right)
		{
			//�ʏ�e����
		case WEAPONS_MODE_BUTTOL:
			if (m_nAttackCount[CLICK_RIGHT] >= PLAYER_BULLET_TIME)
			{
				//�o���b�g����
				CBullet::Create(D3DXVECTOR3(pos.x + 20, pos.y, pos.z), D3DXVECTOR3(0, -20, 0.0f));
				//�J�E���g������
				m_nAttackCount[CLICK_RIGHT] = 0;
			}
			break;
			//���[�U�[����
		case WEAPONS_MODE_LASER:
			if (m_nAttackCount[CLICK_RIGHT] >= PLAYER_LASER_TIME)
			{
				//���[�U�[����
				CLaser::Create(D3DXVECTOR3(pos.x + 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//�J�E���g������
				m_nAttackCount[CLICK_RIGHT] = 0;
			}
			break;
			//�z�[�~���O�e����
		case WEAPONS_MODE_HOMING:
			if (m_nAttackCount[CLICK_RIGHT] >= PLAYER_HOMING_TIME)
			{
				//�z�[�~���O����
				CHoming::Create(D3DXVECTOR3(pos.x + 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//�J�E���g������
				m_nAttackCount[CLICK_RIGHT] = 0;
			}
			break;
		default:
			break;
		}
	}
}
