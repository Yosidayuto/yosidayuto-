//=============================================================================
//
// �z�[�~���O���� [homing.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "homing.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "sound.h"			
#include "effect.h"			
#include "boss base.h"
#include "enemy base.h"
#include <typeinfo.h>
//=============================================================================
//�}�N����`
//=============================================================================
#define HOMING_SIZE		(40)	//�z�[�~���O�̑傫��
#define HOMING_LIFE		(50)	//�z�[�~���O�̎˒�����
#define HOMING_ATTACK	(1)		//�z�[�~���O�̍U����
#define HOMING_RANGE	(780)	//�z�[�~���O�͈�
#define HOMING_SPEED	(10.0f)	//�z�[�~���O�X�s�[�h

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CHoming::m_TextureData = { NULL,"data/TEXTURE/Bullet.png" };

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CHoming::CHoming()
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	m_nRange = HOMING_RANGE;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CHoming::~CHoming()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CHoming::Load(void)
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
void CHoming::Unload(void)
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
CHoming * CHoming::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//�������m��
	CHoming *pHoming=NULL;
	pHoming = new CHoming;
	
	//NULL�`�F�b�N
	if (pHoming != NULL)
	{
		//�ʒu�ݒ�
		pHoming->SetPos(pos);
		//�T�C�Y�ݒ�
		pHoming->SetSize(D3DXVECTOR3(HOMING_SIZE / 2.0f, HOMING_SIZE / 2.0f, 0.0f));
		//�ړ��ʐݒ�
		pHoming->SetMove(move);
		//�˒������ݒ�
		pHoming->SetLife(HOMING_LIFE);
		//������
		pHoming->Init();
	}

	return pHoming;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CHoming::Init(void)
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
void CHoming::Uninit(void)
{
	//�I������
	CBulletBase::Uninit();
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CHoming::Update(void)
{
	CBulletBase::Update();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CHoming::Draw(void)
{
	//�`�揈��
	CBulletBase::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
void CHoming::Move(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	//�G�t�F�N�g����
	CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(HOMING_SIZE / 2.0f, HOMING_SIZE / 2.0f, 0.0f), CEffect::EFFECT_TYPE_BULLET);
	//�ʒu�X�V
	pos += move;
	//�|���S���̈ʒu��n��
	SetPos(pos);
}

//=============================================================================
// �o���b�g����
//=============================================================================
void CHoming::Bullet(CScene * pObj)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�G�l�~�[�̓����蔻��
	if (pObj->GetObjType() == OBJ_TYPE_ENEMY)
	{
		D3DXVECTOR3 EnemeyPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 EnemeySize = ((CScene2d*)pObj)->GetSize();

		//�^�[�Q�b�g�ߑ�
		LockOn(pos, EnemeyPos);

		//�����蔻��
		if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
			&&EnemeyPos.x - EnemeySize.x / 2 < pos.x
			&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
			&&EnemeyPos.y - EnemeySize.y / 2 < pos.y)
		{
			//�G�N�X�v���[�W��������
			CExplosion::Create(pos);
			//�G�l�~�[�_���[�W����
			((CEnemyBase*)pObj)->Damage(HOMING_ATTACK);
			//�I������
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
			((CBossBase*)pObj)->Damage(HOMING_ATTACK);
			//�o���b�g�I������
			Uninit();
			return;
		}

	}

}

//=============================================================================
// �^�[�Q�b�g�擾�֐�
//=============================================================================
void CHoming::LockOn(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos)
{
	//�^�[�Q�b�g�̋������擾�ϐ�
	float	fDistance = 0.0f;
	int		nDistance = 0;

	//�^�[�Q�b�g�̋������擾
	fDistance = (pos.x - EnemyPos.x)*(pos.x - EnemyPos.x) + (pos.y - EnemyPos.y)*(pos.y - EnemyPos.y);
	
	//int�^�Ɏ��[
	nDistance = (int)(sqrt(fDistance));

	//�z�[�~���O�͈͂Ɉ�ԋ߂��^�[�Q�b�g���[
	if (m_nRange>nDistance)
	{
		m_nRange = nDistance;
		TargetMove(pos, EnemyPos);
	}
}

//=============================================================================
// �^�[�Q�b�g�����̈ړ��ʎ擾�֐�
//=============================================================================
void CHoming::TargetMove(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos)
{
	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	//�^�[�Q�b�g�̕����擾�ϐ�
	float fAngle = 0.0f;

	fAngle = atan2f((-pos.x + EnemyPos.x), (-pos.y + EnemyPos.y));
	//�ړ��ʎ擾
	move.x = sinf(fAngle)*HOMING_SPEED;
	move.y = cosf(fAngle)*HOMING_SPEED;
	
	//�ړ��ʃZ�b�g
	SetMove(move);

}
