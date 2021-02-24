//=============================================================================
//
// �{�X�^�C�v2���� [boss type2.cpp]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss type2.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "boss effect2.h"
#include "delete effect2.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BOSS_TYPE2_SIZE		(500.0f)	//�T�C�Y
#define BOSS_TYPE2_LIFE		(200)		//���C�t
#define BOSS_TYPE2_SCORE	(10000)		//�X�R�A
#define BOSS_TYPE2_COOLTIME	(350)		//�U���̃N�[���^�C��
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBossType2::m_TextureData = { NULL,"data/TEXTURE/Boss_2.png", };
//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossType2::CBossType2()
{
}
//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossType2::~CBossType2()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossType2::Load(void)
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
void CBossType2::Unload(void)
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
CBossType2 * CBossType2::Create(D3DXVECTOR3 pos)
{
	//�������m��
	CBossType2* pBossType2 = NULL;
	pBossType2 = new CBossType2;
	
	//NULL�`�F�b�N
	if (pBossType2 != NULL)
	{
		//�ʒu�ݒ�
		pBossType2->SetPos(pos);
		//�T�C�Y�ݒ�
		pBossType2->SetSize(D3DXVECTOR3(BOSS_TYPE2_SIZE / 2.0f, BOSS_TYPE2_SIZE / 2.0f, 0.0f));
		//���C�t�ݒ�
		pBossType2->SetLife(BOSS_TYPE2_LIFE);
		//�X�R�A�ݒ�
		pBossType2->SetScore(BOSS_TYPE2_SCORE);
		//�U���̃N�[���^�C���ݒ�
		pBossType2->SetCoolTime(BOSS_TYPE2_COOLTIME);
		//�e�N�X�`���Z�b�g
		pBossType2->BindTexture(m_TextureData.m_Texture);
		//����������
		pBossType2->Init();

	}
	return pBossType2;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossType2::Init(void)
{
	CBossBase::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossType2::Uninit(void)
{
	CBossBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossType2::Update(void)
{
	//�U������
	Bullet();
	CBossBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossType2::Draw(void)
{
	CBossBase::Draw();
}

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
void CBossType2::Effect(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�G�t�F�N�g����
	m_Effect = CBossEffectType2::Create(pos, size);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossType2::DisEffect(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();
	
	//�G�t�F�N�g�I������
	if (m_Effect != NULL)
	{
		m_Effect->Uninit();
	}

	//���ꂽ�Ƃ��̃G�t�F�N�g����
	CDeleteEffect2::Create(D3DXVECTOR3(pos.x, SCREEN_HEIGHT / 2,0.0f), D3DXVECTOR3(STAGE_SIZE, SCREEN_HEIGHT,0.0f));
}
