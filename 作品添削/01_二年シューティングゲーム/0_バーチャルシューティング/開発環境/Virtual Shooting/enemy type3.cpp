//=============================================================================
//
// �G�l�~�[�^�C�v3���� [enemy type3.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy type3.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TYPE1_SIZE	(100.0f)	//�T�C�Y
#define TYPE1_LIFE	(2)			//���C�t
#define TYPE1_SCORE (100)		//�X�R�A
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CEnemyType3::m_TextureData = { NULL,"data/TEXTURE/Enemy_3.png", };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CEnemyType3::CEnemyType3(int nPriorit)
{
}
//=============================================================================
// �f�X�g���N�g
//=============================================================================
CEnemyType3::~CEnemyType3()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CEnemyType3::Load(void)
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
void CEnemyType3::Unload(void)
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
CEnemyType3 * CEnemyType3::Create(ENEMY_MOVE_PATTERN MoveType, ENEMY_ATTACK_PATTERN AttackType, int nInTime, int nActionTime, int nAttacTime, int nReturnTime, D3DXVECTOR3 pos, float fSpeed, int nLife)
{
	//�������m��
	CEnemyType3* pEnemyType3 = NULL;
	pEnemyType3 = new CEnemyType3;

	//NULL�`�F�b�N
	if (pEnemyType3 != NULL)
	{
		//�s���p�^�[��
		pEnemyType3->SetMovePattern(MoveType);
		//�U���p�^�[��
		pEnemyType3->SetAttackPattern(AttackType);
		//�o������
		pEnemyType3->SetInTime(nInTime);
		//�s������
		pEnemyType3->SetActionTime(nActionTime);
		//�U���܂ł̎��Ԑݒ�
		pEnemyType3->SetAttackTime(nAttacTime);
		//�A�҂܂ł̎��Ԑݒ�
		pEnemyType3->SetOutTime(nReturnTime);
		//�ʒu�ݒ�
		pEnemyType3->SetPos(pos);
		//�X�s�[�h�ݒ�
		pEnemyType3->SetSpeed(fSpeed);
		//���C�t�ݒ�
		pEnemyType3->SetLife(nLife);
		//�T�C�Y�ݒ�
		pEnemyType3->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//�X�R�A�ݒ�
		pEnemyType3->SetScore(TYPE1_SCORE);
		//�e�N�X�`���Z�b�g
		pEnemyType3->BindTexture(m_TextureData.m_Texture);
		//����������
		pEnemyType3->Init();
	}
	return pEnemyType3;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyType3::Init(void)
{
	CEnemyBase::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyType3::Uninit(void)
{
	CEnemyBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyType3::Update(void)
{
	//�U������
	Bullet();

	CEnemyBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyType3::Draw(void)
{
	CEnemyBase::Draw();
}
