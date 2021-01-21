//=============================================================================
//
//	�X�^�[�g�{�^��[start button.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "start button.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "game.h"
//=============================================================================
// �ÓI�����o�[�ϐ�
//=============================================================================
TEXTURE_DATA CStartButton::m_TextureData = {NULL,	"data/TEXTURE/Text_Start.png",};

CStartButton::CStartButton(int nPriorit):CButtonp(nPriorit)
{
}

CStartButton::~CStartButton()
{
}

HRESULT CStartButton::Load(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_pTexture);

	return S_OK;
}

void CStartButton::Unload(void)
{	
	//�e�N�X�`���̔j��
	if (m_TextureData.m_pTexture != NULL)
	{
		m_TextureData.m_pTexture->Release();
		m_TextureData.m_pTexture = NULL;
	}
}

CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CStartButton *pStartButton;
	pStartButton = new CStartButton;

	//�ʒu�ݒ�
	pStartButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//�T�C�Y�ݒ�
	pStartButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//�e�N�X�`���ݒ�
	pStartButton->BindTexture(m_TextureData.m_pTexture);
	//����������
	pStartButton->Init();
	return pStartButton;
}

HRESULT CStartButton::Init(void)
{
	m_pNumber = CNumber::Create(D3DXVECTOR3(GetPos().x + 55, GetPos().y, 0.0f), D3DXVECTOR3(25.0f, GetSize().y, 0.0f));
	m_pNumber->SetNumber(CGame::SetStage() + 1);
	CButtonp::Init();
	SetPos(D3DXVECTOR3(GetPos().x + 20, GetPos().y,0.0f));
	SetSize(D3DXVECTOR3(GetSize().x-100, GetSize().y,0.0f));
	return E_NOTIMPL;
}

void CStartButton::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
	}

	CButtonp::Uninit();
}

void CStartButton::Update(void)
{

	CButtonp::Update();
}

void CStartButton::Draw(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Draw();
	}

	CButtonp::Draw();
}
