//=============================================================================
//
// �{�X�f���[�g�G�t�F�N�g3���� [delete effect3.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "delete effect3.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TEXTURE		(90)	//�ő�e�N�X�`���̃R�}��
#define MAX_ANIME_COUNT (2)		//�ő�A�j���[�V�����J�E���^
#define LOOP_SWITCH		(false)	//���[�v���邩
//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CDeleteEffect3::m_TextureData = { NULL,"data/TEXTURE/DeleteEffect_2.png" };

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CDeleteEffect3::CDeleteEffect3()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CDeleteEffect3::~CDeleteEffect3()
{
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CDeleteEffect3::Load(void)
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
void CDeleteEffect3::Unload(void)
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
CDeleteEffect3 * CDeleteEffect3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	CDeleteEffect3* pDeleteEffect3 = NULL;
	pDeleteEffect3 = new CDeleteEffect3;

	//NULL�`�F�b�N
	if (pDeleteEffect3 != NULL)
	{
		//�ʒu�Z�b�g
		pDeleteEffect3->SetPos(pos);
		//�T�C�Y�Z�b�g
		pDeleteEffect3->SetSize(size);
		//����������
		pDeleteEffect3->Init();
		//�ő�e�N�X�`���̃R�}���Z�b�g
		pDeleteEffect3->SetMaxTexture(MAX_TEXTURE);
		//�ő�A�j���[�V�����J�E���^�Z�b�g
		pDeleteEffect3->SetCountAnime(MAX_ANIME_COUNT);
		//���[�v�ݒ�Z�b�g
		pDeleteEffect3->SetLoop(LOOP_SWITCH);

		return pDeleteEffect3;
	}
	return NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CDeleteEffect3::Init(void)
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
void CDeleteEffect3::Uninit(void)
{
	//�I������
	CBossEffectBase::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CDeleteEffect3::Update(void)
{
	CBossEffectBase::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDeleteEffect3::Draw(void)
{
	CBossEffectBase::Draw();
}
