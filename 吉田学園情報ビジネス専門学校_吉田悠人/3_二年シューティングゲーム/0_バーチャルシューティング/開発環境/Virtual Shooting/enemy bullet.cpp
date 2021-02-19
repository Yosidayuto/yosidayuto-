//=============================================================================
//
// �G�l�~�[�o���b�g���� [enemy bullet.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy bullet.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "sound.h"			
#include "effect.h"			
#include "enemy.h"			
#include "boss.h"			
//=============================================================================
//�}�N����`
//=============================================================================
#define BULLET_SIZE 40		//�o���b�g�̑傫��
#define BULLET_LIFE 1000	//�o���b�g�̎˒�����
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CEnemyBullet::m_TextureData = { NULL,"data/TEXTURE/Bullet.png" };

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEnemyBullet::CEnemyBullet()
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemyBullet::~CEnemyBullet()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CEnemyBullet::Load(void)
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
void CEnemyBullet::Unload(void)
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
CEnemyBullet * CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//�������m��
	CEnemyBullet *pEnemyBullet;
	pEnemyBullet = new CEnemyBullet;
	//�ʒu�ݒ�
	pEnemyBullet->SetPos(pos);
	//�T�C�Y�ݒ�
	pEnemyBullet->SetSize(D3DXVECTOR3(BULLET_SIZE / 2.0f, BULLET_SIZE / 2.0f, 0.0f));
	//�ړ��ʐݒ�
	pEnemyBullet->SetMove(move);
	//�˒������ݒ�
	pEnemyBullet->SetLife(BULLET_LIFE);
	//������
	pEnemyBullet->Init();
	return pEnemyBullet;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CEnemyBullet::Init(void)
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
void CEnemyBullet::Uninit(void)
{
	//�I������
	CBulletBase::Uninit();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyBullet::Update(void)
{
	CBulletBase::Update();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CEnemyBullet::Draw(void)
{
	//�`�揈��
	CBulletBase::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
void CEnemyBullet::Move(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//�ʒu�X�V
	pos += move;
	//�|���S���̈ʒu��n��
	SetPos(pos);
}

//=============================================================================
// �o���b�g����
//=============================================================================
void CEnemyBullet::Bullet(CScene * pObj)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	if (pObj->GetObjType() == OBJ_TYPE_PLAYER)
	{
		D3DXVECTOR3 PlayerPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 PlayerSize = ((CScene2d*)pObj)->GetSize();
		//�����蔻��
		if (PlayerPos.x + PlayerSize.x / 2 > pos.x
			&&PlayerPos.x - PlayerSize.x / 2 < pos.x
			&&PlayerPos.y + PlayerSize.y / 2 > pos.y
			&&PlayerPos.y - PlayerSize.y / 2 < pos.y)
		{
			//�G�l�~�[�_���[�W����
			((CPlayer*)pObj)->Damage(1);
			//�o���b�g�I������
			Uninit();
			return;
		}
	}
}



