//=============================================================================
//
//	���C�tui[life ui.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "life ui.h"
#include "renderer.h"
#include "manager.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CLifeUi::m_TextureData = { NULL,	"data/TEXTURE/Life_UI.png", };

CLifeUi::CLifeUi(int nPriorit) :CScene2d(nPriorit)
{
}

CLifeUi::~CLifeUi()
{
}

HRESULT CLifeUi::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_pTexture);

	return S_OK;
}

void CLifeUi::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_pTexture != NULL)
	{
		m_TextureData.m_pTexture->Release();
		m_TextureData.m_pTexture = NULL;
	}
}

CLifeUi * CLifeUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLifeUi *pLifeUi;
	pLifeUi = new CLifeUi;

	//�ʒu�ݒ�
	pLifeUi->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//�T�C�Y�ݒ�
	pLifeUi->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//�e�N�X�`���ݒ�
	pLifeUi->BindTexture(m_TextureData.m_pTexture);
	//����������
	pLifeUi->Init();
	return pLifeUi;
}

HRESULT CLifeUi::Init(void)
{
	CScene2d::Init();
	return S_OK;
}

void CLifeUi::Uninit(void)
{
	CScene2d::Uninit();
}

void CLifeUi::Update(void)
{
	CScene2d::Update();
}

void CLifeUi::Draw(void)
{
	CScene2d::Draw();
}
