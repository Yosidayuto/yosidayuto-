//=============================================================================
//
// �{�X�f���[�g�G�t�F�N�g1���� [delete effect1.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "delete effect1.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE		(45)	//�ő�e�N�X�`���̃R�}��
#define MAX_ANIME_COUNT (2)		//�ő�A�j���[�V�����J�E���^
#define LOOP_SWITCH		(false)	//���[�v���邩
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CDeleteEffect1::m_TextureData = { NULL,"data/TEXTURE/DeleteEffect_0.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CDeleteEffect1::CDeleteEffect1()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CDeleteEffect1::~CDeleteEffect1()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CDeleteEffect1::Load(void)
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
void CDeleteEffect1::Unload(void)
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
CDeleteEffect1 * CDeleteEffect1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CDeleteEffect1* pDeleteEffect1 = NULL;
	pDeleteEffect1 = new CDeleteEffect1;

	//NULL�`�F�b�N
	if (pDeleteEffect1 != NULL)
	{
		//�ʒu�Z�b�g
		pDeleteEffect1->SetPos(pos);
		//�T�C�Y�Z�b�g
		pDeleteEffect1->SetSize(size);
		//����������
		pDeleteEffect1->Init();
		//�ő�e�N�X�`���̃R�}���Z�b�g
		pDeleteEffect1->SetMaxTexture(MAX_TEXTURE);
		//�ő�A�j���[�V�����J�E���^�Z�b�g
		pDeleteEffect1->SetCountAnime(MAX_ANIME_COUNT);
		//���[�v�ݒ�Z�b�g
		pDeleteEffect1->SetLoop(LOOP_SWITCH);

		return pDeleteEffect1;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CDeleteEffect1::Init(void)
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
void CDeleteEffect1::Uninit(void)
{
	//�I������
	CBossEffectBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CDeleteEffect1::Update(void)
{
	CBossEffectBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDeleteEffect1::Draw(void)
{
	CBossEffectBase::Draw();
}
