//=============================================================================
//
// �G�l�~�[�^�C�v1���� [enemy type1.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy type1.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TYPE1_SIZE	(100.0f)//�T�C�Y
#define TYPE1_LIFE	(2)		//���C�t
#define TYPE1_SCORE (100)	//�X�R�A
#define TYPE1_SPEED (5.5f)	//�X�s�[�h

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CEnemyType1::m_TextureData = { NULL,"data/TEXTURE/Enemy_1.png", };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CEnemyType1::CEnemyType1()
{
}
//=============================================================================
// �f�X�g���N�g
//=============================================================================
CEnemyType1::~CEnemyType1()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CEnemyType1::Load(void)
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
void CEnemyType1::Unload(void)
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
CEnemyType1 * CEnemyType1::Create(ENEMY_MOVE_PATTERN MoveType,ENEMY_ATTACK_PATTERN AttackType,int nInTime,int nActionTime,int nAttacTime,int nReturnTime,D3DXVECTOR3 pos,float fSpeed,int nLife)						
{
	//�������m��
	CEnemyType1* pEnemyType1 = NULL;
	pEnemyType1 = new CEnemyType1;

	//NULL�`�F�b�N
	if (pEnemyType1 != NULL)
	{
		//�s���p�^�[��
		pEnemyType1->SetMovePattern(MoveType);
		//�U���p�^�[��
		pEnemyType1->SetAttackPattern(AttackType);
		//�o������
		pEnemyType1->SetInTime(nInTime);
		//�s������
		pEnemyType1->SetActionTime(nActionTime);
		//�U���܂ł̎��Ԑݒ�
		pEnemyType1->SetAttackTime(nAttacTime);
		//�A�҂܂ł̎��Ԑݒ�
		pEnemyType1->SetOutTime(nReturnTime);
		//�ʒu�ݒ�
		pEnemyType1->SetPos(pos);
		//�X�s�[�h�ݒ�
		pEnemyType1->SetSpeed(fSpeed);
		//���C�t�ݒ�
		pEnemyType1->SetLife(nLife);
		//�T�C�Y�ݒ�
		pEnemyType1->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//�X�R�A�ݒ�
		pEnemyType1->SetScore(TYPE1_SCORE);
		//�e�N�X�`���Z�b�g
		pEnemyType1->BindTexture(m_TextureData.m_Texture);
		//����������
		pEnemyType1->Init();
	}
	return pEnemyType1;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyType1::Init(void)
{
	CEnemyBase::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyType1::Uninit(void)
{
	CEnemyBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyType1::Update(void)
{
	//�U������
	Bullet();
	CEnemyBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyType1::Draw(void)
{
	CEnemyBase::Draw();
}
