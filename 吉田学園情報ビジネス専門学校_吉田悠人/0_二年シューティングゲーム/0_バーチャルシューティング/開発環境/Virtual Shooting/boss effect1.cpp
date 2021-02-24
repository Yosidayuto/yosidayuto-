//=============================================================================
//
// �{�X�G�t�F�N�g1���� [boss effect1.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss effect1.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE		(45)	//�ő�e�N�X�`���̃R�}��
#define MAX_ANIME_COUNT (2)		//�ő�A�j���[�V�����J�E���^
#define LOOP_SWITCH		(true)	//���[�v���邩
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBossEffectType1::m_TextureData = { NULL,"data/TEXTURE/BossAnime_0.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossEffectType1::CBossEffectType1()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossEffectType1::~CBossEffectType1()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossEffectType1::Load(void)
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
void CBossEffectType1::Unload(void)
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
CBossEffectType1 * CBossEffectType1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CBossEffectType1* pBossEffectType1 = NULL;
	pBossEffectType1 = new CBossEffectType1;
	
	//NULL�`�F�b�N
	if (pBossEffectType1!=NULL)
	{
		//�ʒu�Z�b�g
		pBossEffectType1->SetPos(pos);
		//�T�C�Y�Z�b�g
		pBossEffectType1->SetSize(size);
		//����������
		pBossEffectType1->Init();
		//�ő�e�N�X�`���̃R�}���Z�b�g
		pBossEffectType1->SetMaxTexture(MAX_TEXTURE);
		//�ő�A�j���[�V�����J�E���^�Z�b�g
		pBossEffectType1->SetCountAnime(MAX_ANIME_COUNT);
		//���[�v�ݒ�Z�b�g
		pBossEffectType1->SetLoop(LOOP_SWITCH);

		return pBossEffectType1;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossEffectType1::Init(void)
{
	//����������
	CBossEffectBase::Init();

	//�e�N�X�`���̐ݒ�
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossEffectType1::Uninit(void)
{
	//�I������
	CBossEffectBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossEffectType1::Update(void)
{
	CBossEffectBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossEffectType1::Draw(void)
{
	CBossEffectBase::Draw();
}
