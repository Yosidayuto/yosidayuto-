//=============================================================================
//
// ���[�U�[���� [laser.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "laser.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "sound.h"			
#include "effect.h"			
#include "enemy base.h"
#include "boss base.h"
#include <typeinfo.h>
//=============================================================================
//�}�N����`
//=============================================================================
#define LASER_X_SIZE	(10)	//���[�U�[�̉��傫��
#define LASER_Y_SIZE	(100)	//���[�U�[�̏c�傫��
#define LASER_LIFE		(1000)	//���[�U�[�̎˒�����
#define LASER_ATTACK	(1)		//���[�U�[�̍U����
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CLaser::m_TextureData = { NULL,"data/TEXTURE/Laser.png" };

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CLaser::CLaser()
{
	memset(m_bHit,false,sizeof(m_bHit));
	m_nHitCount = 0;
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CLaser::~CLaser()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CLaser::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CLaser::Unload(void)
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
CLaser * CLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//�������m��
	CLaser *pLaser = NULL;
	pLaser = new CLaser;

	//NULL�`�F�b�N
	if (pLaser != NULL)
	{
		//�ʒu�ݒ�
		pLaser->SetPos(pos);
		//�T�C�Y�ݒ�
		pLaser->SetSize(D3DXVECTOR3(LASER_X_SIZE / 2.0f, LASER_Y_SIZE / 2.0f, 0.0f));
		//�ړ��ʐݒ�
		pLaser->SetMove(move);
		//�˒������ݒ�
		pLaser->SetLife(LASER_LIFE);
		//������
		pLaser->Init();
	}

	return pLaser;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CLaser::Init(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	//�T�E���h
	pSound->Play(CSound::LABEL_SE_LASER);
	//����������
	CBulletBase::Init();
	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLaser::Uninit(void)
{
	//�I������
	CBulletBase::Uninit();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLaser::Update(void)
{
	//������
	m_nHitCount = 0;
	CBulletBase::Update();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CLaser::Draw(void)
{
	//�`�揈��
	CBulletBase::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
void CLaser::Move(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	//�G�t�F�N�g����
	CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(LASER_X_SIZE / 2.0f, LASER_Y_SIZE / 2.0f, 0.0f), CEffect::EFFECT_TYPE_LASER);
	//�ʒu�X�V
	pos += move;
	//�|���S���̈ʒu��n��
	SetPos(pos);
}

//=============================================================================
// �o���b�g����
//=============================================================================
void CLaser::Bullet(CScene * pObj)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	if (pObj->GetObjType() == OBJ_TYPE_ENEMY)
	{
		D3DXVECTOR3 EnemeyPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 EnemeySize = ((CScene2d*)pObj)->GetSize();
		//�����蔻��
		if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
			&&EnemeyPos.x - EnemeySize.x / 2 < pos.x
			&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
			&&EnemeyPos.y - EnemeySize.y / 2 < pos.y
			&&m_bHit[m_nHitCount] != true)
		{
			//�G�N�X�v���[�W��������
			CExplosion::Create(pos);
			//�G�l�~�[�_���[�W����
			((CEnemyBase*)pObj)->Damage(LASER_ATTACK);
			//�����������
			m_bHit[m_nHitCount] = true;
			return;
		}
		//�G�l�~�[�J�E���g
		m_nHitCount++;
	}
	//�{�X�̓����蔻�菈��
	if (pObj->GetObjType() == OBJ_TYPE_BOSS)
	{
		D3DXVECTOR3 BossPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 BossSize = ((CScene2d*)pObj)->GetSize();
		//�����蔻��
		if (BossPos.x + BossSize.x / 2 > pos.x
			&&BossPos.x - BossSize.x / 2 < pos.x
			&&BossPos.y + BossSize.y / 2 > pos.y
			&&BossPos.y - BossSize.y / 2 < pos.y
			&&m_bHit[m_nHitCount] != true)
		{
			//�G�N�X�v���[�W��������
			CExplosion::Create(pos);
			//�G�l�~�[�_���[�W����
			((CBossBase*)pObj)->Damage(LASER_ATTACK);
			//�����������
			m_bHit[m_nHitCount] = true;
			return;
		}
		//�G�l�~�[�J�E���g
		m_nHitCount++;

	}


}