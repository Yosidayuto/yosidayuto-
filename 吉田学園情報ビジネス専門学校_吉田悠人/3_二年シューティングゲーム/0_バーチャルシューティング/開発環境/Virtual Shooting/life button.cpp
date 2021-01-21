//=============================================================================
//
//	���C�t�{�^��[life button.cpp]
//	Author:�g�c�@�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "life button.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CLifeButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Life.png", };

CLifeButton::CLifeButton(int nPriorit) :CButtonp(nPriorit)
{
}

CLifeButton::~CLifeButton()
{
}

HRESULT CLifeButton::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_pTexture);

	return S_OK;
}

void CLifeButton::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_TextureData.m_pTexture != NULL)
	{
		m_TextureData.m_pTexture->Release();
		m_TextureData.m_pTexture = NULL;
	}
}

CLifeButton * CLifeButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLifeButton *pLifeButton;
	pLifeButton = new CLifeButton;

	//�ʒu�ݒ�
	pLifeButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//�T�C�Y�ݒ�
	pLifeButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//�e�N�X�`���ݒ�
	pLifeButton->BindTexture(m_TextureData.m_pTexture);
	//����������
	pLifeButton->Init();
	return pLifeButton;
}

HRESULT CLifeButton::Init(void)
{
	CButtonp::Init();
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));

	return S_OK;
}

void CLifeButton::Uninit(void)
{
	CButtonp::Uninit();
}

void CLifeButton::Update(void)
{

	CButtonp::Update();
}

void CLifeButton::Draw(void)
{

	CButtonp::Draw();
}
