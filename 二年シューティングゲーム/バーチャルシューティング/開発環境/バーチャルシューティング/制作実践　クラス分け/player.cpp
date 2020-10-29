#include "player.h"			//�v���C���[�w�b�_�[
#include "input.h"			//�C���v�b�g�w�b�_�[
#include "inihkeyboard.h"	//�C���v�b�g�L�[�{�[�h�w�b�_�[
#include "inputmouse.h"		//�C���v�b�g�}�E�X�w�b�_�[
#include "manager.h"		//�}�l�[�W���[�w�b�_�[
#include "bullet.h"			//�o���b�g�w�b�_�[
#include "renderer.h"		//�����_�����O�w�b�_�[
#include "sound.h"			//�T�E���h�w�b�_�[
#include "life.h"			//���C�t�w�b�_�[
#include "game.h"			//�Q�[���w�b�_�[
#include "laser.h"			//���[�U�[�w�b�_�[
#include "homing.h"			//�z�[�~���O�w�b�_�[
#include "fade.h"			//�t�F�[�h
#include "explosion.h"		//���j
//----------------------------------
//�}�N����`
//----------------------------------
#define PLAYER_SIZE 100
#define PLAYER_MOVE 0
#define PLAYER_DAMAGE 100
//----------------------------------
//�ÓI�����o�[�ϐ�
//----------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CPlayer::WEAPON_MODE CPlayer::m_Weapon[MAX_WEAPON] =
{
	WEAPONS_MODE_BUTTOL,
	WEAPONS_MODE_NONE
};
D3DXVECTOR3 CPlayer::posMove = D3DXVECTOR3(PLAYER_MOVE, PLAYER_MOVE,0.0f);
int CPlayer::m_nLife = 3;
float CPlayer::m_fSpeed = 4.0f;
//=============================================================================
//�R���X�g���N�g
//=============================================================================
CPlayer::CPlayer(int nPriorit) :CScene2d(nPriorit)
{
	CScene::SetObjType(CScene::OBJ_TYPE_PLAYER);	//�^�C�v����
	Stats = STATS_MODE_NORMAL;						//�v���C���[�̏��
	nDamageTime = PLAYER_DAMAGE;					//���G����
	for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
	{
		nCountWeapon[nCount] = 0;					//�U���^�C�~���O
	}
	m_nLife = 3;
	m_fSpeed = 4.0f;
}

//=============================================================================
//�f�X�g���N�g
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
//��������
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Set(Pos);
	pPlayer->m_nLife += CManager::GetPlayer(0);
	pPlayer->m_fSpeed += (CManager::GetPlayer(1)*0.45f);

	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
//�e�N�X�`�����[�h����
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Player.png", &m_pTexture);
	return S_OK;
}

//=============================================================================
//�e�N�X�`���j������
//=============================================================================
void CPlayer::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//=============================================================================
//����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	for (int nCount = 0; nCount < MAX_WEAPON; nCount++)
	{
		m_Weapon[nCount]= CManager::GetWeapon(nCount);
	}
	
	//�T�C�Y
	SetSizeition(D3DXVECTOR3(PLAYER_SIZE / 2, PLAYER_SIZE / 2, 0.0f));
	//����������
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);
	//���C�t�擾
	pLife = CGame::GetLife();
	if (pLife != NULL)
	{
		pLife->SetLife(m_nLife);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPlayer::Update(void)
{
	CInihKeyboard *pKeyboard = CManager::GetKeyboard();	//�L�[�{�[�h�擾
	CInihMouse *pMouse = CManager::GetMouse();			//�}�E�X�擾
	D3DXVECTOR3 pos;
	pos = GetPosition();

	if (pMouse->GetClick(0) == true)
	{
		Weapon(pos,0);
	}
	if (pMouse->GetClick(1) == true)
	{
		Weapon(pos, 1);
	}


	//�}�E�X�̍��W�擾
	float fAngle = atan2f((-pos.x + pMouse->GetMousePos().x), (-pos.y + pMouse->GetMousePos().y));
	
	//�ʒu���̎󂯓n��
	posMove.x = sinf(fAngle)*m_fSpeed;
	posMove.y = cosf(fAngle)*m_fSpeed;

	//�ʒu����
	if (pos.x + 5 > pMouse->GetMousePos().x
		&&pos.x - 5 < pMouse->GetMousePos().x
		&&pos.y + 5 > pMouse->GetMousePos().y
		&&pos.y - 5 < pMouse->GetMousePos().y)
	{
		//�X�g�b�v
	}
	else
	{
		//�ʒu�X�V
		pos += posMove;
	}
	
	////��������
	posMove.x += (0.0f - posMove.x)*0.2f;
	posMove.y += (0.0f - posMove.y)*0.2f;
	
	pos += MoveLimit(pos, fAngle);
	//���W�X�V
	SetPosition(pos);

	CScene2d::Update();

	//��ԊǗ�
	StatasManage();

}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}

//=============================================================================
//�����ʒu����
//=============================================================================
void CPlayer::Set(D3DXVECTOR3 Pos)
{
	CScene2d::Set(Pos);
}

//=============================================================================
//�_���[�W����
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
			Stats = STATS_MODE_DAMAGE;
		}
		else
		{
			Stats = STATS_MODE_DEATH;
		}
	}

}



//=============================================================================
//��ԊǗ�����
//=============================================================================
void CPlayer::StatasManage(void)
{
	switch (Stats)
	{
	case STATS_MODE_NORMAL:
		ColChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case STATS_MODE_DAMAGE:
		nDamageTime -= 1;

		//�_���[�W�J���[
		if (nDamageTime % 25)
		{
			ColChange(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		}
		else
		{
			ColChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (nDamageTime <= 0)
		{
			Stats = STATS_MODE_NORMAL;
			nDamageTime = PLAYER_DAMAGE;
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
		CExplosion::Create(GetPosition());

		//�Z���N�g�ړ�
		pFade->Set(CManager::GAME_MODE_SELECT);		
		
		//�I������
		CPlayer::Uninit();
		break;
	}
}

//=============================================================================
//�v���C���[�̈ړ��͈͏���
//=============================================================================
D3DXVECTOR3 CPlayer::MoveLimit(D3DXVECTOR3 pos, float fAngle)
{
	D3DXVECTOR3 MoveLimit= D3DXVECTOR3(0,0,0);
	if (pos.x < 420|| pos.x > 1145)
	{
		MoveLimit.x = sinf(fAngle)*-m_fSpeed;

	}
	if (pos.y < 25|| pos.y>700)
	{
		MoveLimit.y = cosf(fAngle)*-m_fSpeed;
	}
	return D3DXVECTOR3(MoveLimit);
}


//=============================================================================
//�v���C���[�̕���g�p
//=============================================================================
void CPlayer::Weapon(D3DXVECTOR3 pos, int nWeapon)
{
	nCountWeapon[nWeapon]++;
	int nPos;
	switch (nWeapon)
	{
	case 0:
		nPos = -20;
		break;
	case 1:
		nPos = 20;
		break;
	}
	switch (m_Weapon[nWeapon])
	{
	case WEAPONS_MODE_BUTTOL:
		if (nCountWeapon[nWeapon]>=20)
		{
			CBullet::Create(D3DXVECTOR3(pos.x + nPos, pos.y, pos.z), D3DXVECTOR3(0, -20, 0.0f), CBullet::BULLET_TYPE_PLAYER);
			nCountWeapon[nWeapon] = 0;
		}
		break;
	case WEAPONS_MODE_LASER:
		if (nCountWeapon[nWeapon] >= 40)
		{
			CLaser::Create(D3DXVECTOR3(pos.x + nPos, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f), CLaser::LASER_TYPE_PLAYER);
			nCountWeapon[nWeapon] = 0;
		}
		break;
	case WEAPONS_MODE_HOMING:
		if (nCountWeapon[nWeapon] >= 35)
		{
			CHoming::Create(D3DXVECTOR3(pos.x + nPos, pos.y, pos.z), 15, CHoming::HOMING_TYPE_PLAYER);
			nCountWeapon[nWeapon] = 0;
		}
		break;

	}
}
