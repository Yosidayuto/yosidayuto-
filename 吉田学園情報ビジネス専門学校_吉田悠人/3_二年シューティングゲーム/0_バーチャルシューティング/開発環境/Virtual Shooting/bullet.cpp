//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "sound.h"			
#include "effect.h"			
#include "enemy.h"			
#include "enemy base.h"
#include "boss base.h"
#include <typeinfo.h>
//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET_SIZE		(20)	//�o���b�g�̑傫��
#define BULLET_LIFE		(1000)	//�o���b�g�̎˒�����
#define BULLET_DAMAGE	(1)		//�o���b�g�̃_���[�W	
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBullet::m_TextureData = { NULL,"data/TEXTURE/Bullet.png" };

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CBullet::Load(void)
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
void CBullet::Unload(void)
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
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//�������m��
	CBullet *pBullet;
	pBullet = new CBullet;
	//�ʒu�ݒ�
	pBullet->SetPos(pos);
	//�T�C�Y�ݒ�
	pBullet->SetSize(D3DXVECTOR3(BULLET_SIZE / 2.0f, BULLET_SIZE / 2.0f, 0.0f));
	//�ړ��ʐݒ�
	pBullet->SetMove(move);
	//�˒������ݒ�
	pBullet->SetLife(BULLET_LIFE);
	//������
	pBullet->Init();
	return pBullet;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();	
	//�T�E���h
	pSound->Play(CSound::LABEL_SE_SHOTS);	
	//����������
	CBulletBase::Init();
	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	//�I������
	CBulletBase::Uninit();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{	
	CBulletBase::Update();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	//�`�揈��
	CBulletBase::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
void CBullet::Move(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	//�G�t�F�N�g����
	CEffect::Create(pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),D3DXVECTOR3(BULLET_SIZE/2.0f, BULLET_SIZE/2.0f,0.0f), CEffect::EFFECT_TYPE_BULLET);
	//�ʒu�X�V
	pos += move;
	//�|���S���̈ʒu��n��
	SetPos(pos);
}

//=============================================================================
// �o���b�g����
//=============================================================================
void CBullet::Bullet(CScene * pObj)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�G�l�~�[�̓����蔻�菈��
	if (pObj->GetObjType() == OBJ_TYPE_ENEMY)
	{
		D3DXVECTOR3 EnemeyPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 EnemeySize = ((CScene2d*)pObj)->GetSize();
		//�����蔻��
		if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
			&&EnemeyPos.x - EnemeySize.x / 2 < pos.x
			&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
			&&EnemeyPos.y - EnemeySize.y / 2 < pos.y)
		{
			//�G�N�X�v���[�W��������
			CExplosion::Create(pos);
			//�G�l�~�[�_���[�W����
			((CEnemyBase*)pObj)->Damage(BULLET_DAMAGE);
			//�o���b�g�I������
			Uninit();
			return;
		}
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
			&&BossPos.y - BossSize.y / 2 < pos.y)
		{
			//�G�N�X�v���[�W��������
			CExplosion::Create(pos);
			//�G�l�~�[�_���[�W����
			((CBossBase*)pObj)->Damage(BULLET_DAMAGE);
			//�o���b�g�I������
			Uninit();
			return;
		}

	}
}



