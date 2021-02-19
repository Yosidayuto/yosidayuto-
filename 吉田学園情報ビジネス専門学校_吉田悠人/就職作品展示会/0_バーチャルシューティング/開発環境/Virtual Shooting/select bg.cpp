//=============================================================================
//
//	�Z���N�g�w�i[select bg.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "select bg.h"	
#include "manager.h"	
#include "renderer.h"	
#include "scene.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CSelectBg::m_TextureData = { NULL,"data/TEXTURE/background_Select.png" };

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelectBg::CSelectBg(int nPriorit) :CBgc(nPriorit)
{
	//�^�C�v����
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelectBg::~CSelectBg()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSelectBg::Load(void)
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
void CSelectBg::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
//��������
//=============================================================================
CSelectBg * CSelectBg::Create(void)
{
	CSelectBg *pSelectBg;
	pSelectBg = new CSelectBg;

	//�ʒu�ݒ�
	pSelectBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	//�T�C�Y�ݒ�
	pSelectBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//�e�N�X�`���ݒ�
	pSelectBg->BindTexture(m_TextureData.m_Texture);
	//����������
	pSelectBg->Init();

	return pSelectBg;
}

//------------------------------------
//����������
//------------------------------------
HRESULT CSelectBg::Init(void)
{
	CBgc::Init();
	return S_OK;
}

//------------------------------------
//�I������
//------------------------------------
void CSelectBg::Uninit(void)
{
	CBgc::Uninit();
}

//------------------------------------
//�X�V����
//------------------------------------
void CSelectBg::Update(void)
{
	CBgc::Update();
}

//------------------------------------
//�`�揈��
//------------------------------------
void CSelectBg::Draw(void)
{
	CBgc::Draw();
}
