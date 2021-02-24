//=============================================================================
//
// �{�X�G�t�F�N�g2���� [boss effect2.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss effect2.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE		(50)	//�ő�e�N�X�`���̃R�}��
#define MAX_ANIME_COUNT (2)		//�ő�A�j���[�V�����J�E���^
#define LOOP_SWITCH		(true)	//���[�v���邩
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBossEffectType2::m_TextureData = { NULL,"data/TEXTURE/BossAnime_1.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossEffectType2::CBossEffectType2()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossEffectType2::~CBossEffectType2()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossEffectType2::Load(void)
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
void CBossEffectType2::Unload(void)
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
CBossEffectType2 * CBossEffectType2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CBossEffectType2* pBossEffectType2 = NULL;
	pBossEffectType2 = new CBossEffectType2;

	//NULL�`�F�b�N
	if (pBossEffectType2 != NULL)
	{
		//�ʒu�Z�b�g
		pBossEffectType2->SetPos(pos);
		//�T�C�Y�Z�b�g
		pBossEffectType2->SetSize(size);
		//����������
		pBossEffectType2->Init();
		//�ő�e�N�X�`���̃R�}���Z�b�g
		pBossEffectType2->SetMaxTexture(MAX_TEXTURE);
		//�ő�A�j���[�V�����J�E���^�Z�b�g
		pBossEffectType2->SetCountAnime(MAX_ANIME_COUNT);
		//���[�v�ݒ�Z�b�g
		pBossEffectType2->SetLoop(LOOP_SWITCH);

		return pBossEffectType2;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossEffectType2::Init(void)
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
void CBossEffectType2::Uninit(void)
{
	//�I������
	CBossEffectBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossEffectType2::Update(void)
{
	CBossEffectBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossEffectType2::Draw(void)
{
	CBossEffectBase::Draw();
}
