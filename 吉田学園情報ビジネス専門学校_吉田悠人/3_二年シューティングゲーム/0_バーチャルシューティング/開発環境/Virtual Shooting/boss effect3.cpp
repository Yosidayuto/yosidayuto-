//=============================================================================
//
// �{�X�G�t�F�N�g3���� [boss effect3.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss effect3.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE		(60)	//�ő�e�N�X�`���̃R�}��
#define MAX_ANIME_COUNT (2)		//�ő�A�j���[�V�����J�E���^
#define LOOP_SWITCH		(true)	//���[�v���邩
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CBossEffectType3::m_TextureData = { NULL,"data/TEXTURE/BossAnime_2.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CBossEffectType3::CBossEffectType3()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CBossEffectType3::~CBossEffectType3()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBossEffectType3::Load(void)
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
void CBossEffectType3::Unload(void)
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
CBossEffectType3 * CBossEffectType3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CBossEffectType3* pBossEffectType3 = NULL;
	pBossEffectType3 = new CBossEffectType3;

	//NULL�`�F�b�N
	if (pBossEffectType3 != NULL)
	{
		//�ʒu�Z�b�g
		pBossEffectType3->SetPos(pos);
		//�T�C�Y�Z�b�g
		pBossEffectType3->SetSize(size);
		//����������
		pBossEffectType3->Init();
		//�ő�e�N�X�`���̃R�}���Z�b�g
		pBossEffectType3->SetMaxTexture(MAX_TEXTURE);
		//�ő�A�j���[�V�����J�E���^�Z�b�g
		pBossEffectType3->SetCountAnime(MAX_ANIME_COUNT);
		//���[�v�ݒ�Z�b�g
		pBossEffectType3->SetLoop(LOOP_SWITCH);

		return pBossEffectType3;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossEffectType3::Init(void)
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
void CBossEffectType3::Uninit(void)
{
	//�I������
	CBossEffectBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossEffectType3::Update(void)
{
	CBossEffectBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossEffectType3::Draw(void)
{
	CBossEffectBase::Draw();
}
