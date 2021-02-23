//=============================================================================
//
//	�`���[�g���A���w�i[tutorial bg.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial bg.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define TEXTURE_X (0.25f)

//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CTutorialBg::m_TextureData = { NULL,"data/TEXTURE/tutorial.png" };

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorialBg::CTutorialBg(int nPriorit)
{
	m_fTexture = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorialBg::~CTutorialBg()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CTutorialBg::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CTutorialBg::Unload(void)
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
CTutorialBg * CTutorialBg::Create(void)
{
	//�������m��
	CTutorialBg *pTutorialBg = NULL;
	pTutorialBg = new CTutorialBg;

	//NULL�`�F�b�N
	if (pTutorialBg != NULL)
	{
		//�ʒu�ݒ�
		pTutorialBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//�T�C�Y�ݒ�
		pTutorialBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		//�e�N�X�`���ݒ�
		pTutorialBg->BindTexture(m_TextureData.m_Texture);
		//����������
		pTutorialBg->Init();
	}

	return pTutorialBg;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorialBg::Init(void)
{

	D3DXVECTOR2 Texture[4];
	//�e�N�X�`������
	Texture[0] = D3DXVECTOR2(0.0f, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(0.0f, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X, 1.0f);

	//����������
	CBgc::Init();

	//�e�N�X�`��UV����
	TextureAnim(Texture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorialBg::Uninit(void)
{
	CBgc::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorialBg::Update(void)
{
	CBgc::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorialBg::Draw(void)
{
	CBgc::Draw();
}

//=============================================================================
// �e�N�X�`���ړ�
//=============================================================================
void CTutorialBg::TextureMove(bool bScroll)
{
	if (bScroll == true)
	{
		m_fTexture++;
	}
	else
	{
		m_fTexture--;
	}
	if (m_fTexture<0)
	{
		m_fTexture = 0.0f;
	}
	D3DXVECTOR2 Texture[4];	//�e�N�X�`��
	Texture[0] = D3DXVECTOR2(TEXTURE_X*m_fTexture, 0.0f);
	Texture[1] = D3DXVECTOR2(TEXTURE_X*m_fTexture + TEXTURE_X, 0.0f);
	Texture[2] = D3DXVECTOR2(TEXTURE_X*m_fTexture, 1.0f);
	Texture[3] = D3DXVECTOR2(TEXTURE_X*m_fTexture + TEXTURE_X, 1.0f);
	TextureAnim(Texture);

}
