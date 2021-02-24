//=============================================================================
//
// �{�X�f���[�g�G�t�F�N�g2���� [delete effect2.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "delete effect2.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE		(60)	//�ő�e�N�X�`���̃R�}��
#define MAX_ANIME_COUNT (3)		//�ő�A�j���[�V�����J�E���^
#define LOOP_SWITCH		(false)	//���[�v���邩
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CDeleteEffect2::m_TextureData = { NULL,"data/TEXTURE/DeleteEffect_1.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CDeleteEffect2::CDeleteEffect2()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CDeleteEffect2::~CDeleteEffect2()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CDeleteEffect2::Load(void)
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
void CDeleteEffect2::Unload(void)
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
CDeleteEffect2 * CDeleteEffect2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CDeleteEffect2* pDeleteEffect2 = NULL;
	pDeleteEffect2 = new CDeleteEffect2;

	//NULL�`�F�b�N
	if (pDeleteEffect2 != NULL)
	{
		//�ʒu�Z�b�g
		pDeleteEffect2->SetPos(pos);
		//�T�C�Y�Z�b�g
		pDeleteEffect2->SetSize(size);
		//����������
		pDeleteEffect2->Init();
		//�ő�e�N�X�`���̃R�}���Z�b�g
		pDeleteEffect2->SetMaxTexture(MAX_TEXTURE);
		//�ő�A�j���[�V�����J�E���^�Z�b�g
		pDeleteEffect2->SetCountAnime(MAX_ANIME_COUNT);
		//���[�v�ݒ�Z�b�g
		pDeleteEffect2->SetLoop(LOOP_SWITCH);

		return pDeleteEffect2;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CDeleteEffect2::Init(void)
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
void CDeleteEffect2::Uninit(void)
{
	//�I������
	CBossEffectBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CDeleteEffect2::Update(void)
{
	CBossEffectBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDeleteEffect2::Draw(void)
{
	CBossEffectBase::Draw();
}
