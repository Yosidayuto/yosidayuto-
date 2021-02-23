//=============================================================================
//
// �{�X�^�C�v1���� [boss type1.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "boss type1.h"
#include "manager.h"
#include "renderer.h"
#include "boss effect base.h"
#include "boss effect1.h"
#include "delete effect1.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BOSS_TYPE1_SIZE		(500.0f)	// �T�C�Y
#define BOSS_TYPE1_LIFE		(125)		// ���C�t
#define BOSS_TYPE1_SCORE	(10000)		// �X�R�A
#define BOSS_TYPE1_COOLTIME	(400)		// �U���̃N�[���^�C��
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBossType1::m_TextureData = { NULL,"data/TEXTURE/Boss_1.png", };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossType1::CBossType1(int nPriorit)
{
	m_Effect = NULL;
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossType1::~CBossType1()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossType1::Load(void)
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
void CBossType1::Unload(void)
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
CBossType1 * CBossType1::Create(D3DXVECTOR3 pos)
{
	//�������m��
	CBossType1* pBossType1 = NULL;
	pBossType1 = new CBossType1;

	//NULL�`�F�b�N
	if (pBossType1 != NULL)
	{
		//�ʒu�ݒ�
		pBossType1->SetPos(pos);
		//�T�C�Y�ݒ�
		pBossType1->SetSize(D3DXVECTOR3(BOSS_TYPE1_SIZE / 2.0f, BOSS_TYPE1_SIZE / 2.0f, 0.0f));
		//���C�t�ݒ�
		pBossType1->SetLife(BOSS_TYPE1_LIFE);
		//�X�R�A�ݒ�
		pBossType1->SetScore(BOSS_TYPE1_SCORE);
		//�U���̃N�[���^�C���ݒ�
		pBossType1->SetCoolTime(BOSS_TYPE1_COOLTIME);
		//�e�N�X�`���Z�b�g
		pBossType1->BindTexture(m_TextureData.m_Texture);
		//����������
		pBossType1->Init();
	}
	return pBossType1;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossType1::Init(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//������
	CBossBase::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossType1::Uninit(void)
{
	CBossBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossType1::Update(void)
{
	//�U������
	Bullet();
	CBossBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossType1::Draw(void)
{
	CBossBase::Draw();
}

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
void CBossType1::Effect(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�G�t�F�N�g����
	m_Effect = CBossEffectType1::Create(pos, size);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossType1::DisEffect(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�G�t�F�N�g�I������
	if (m_Effect!=NULL)
	{
		m_Effect->Uninit();
	}

	//���ꂽ�Ƃ��̃G�t�F�N�g����
	CDeleteEffect1::Create(pos, size);
}
