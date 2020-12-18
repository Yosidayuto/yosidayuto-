//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : �U�J �����Y
//
//=============================================================================
#include "title.h"
#include "manager.h"
#include "scene2d.h"


//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE] = {};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount] = NULL;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pD3DDevice, TITLE1_TEXTURE, &m_apTexture[0]);
	//D3DXCreateTextureFromFile(pD3DDevice, TITLE2_TEXTURE, &m_apTexture[1]);
	//D3DXCreateTextureFromFile(pD3DDevice, TITLE3_TEXTURE, &m_apTexture[2]);


	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �쐬����
//=============================================================================
CTitle * CTitle::Create(D3DXVECTOR3 size)
{
	CTitle *pTitle;
	//�C���X�^���X����
	pTitle = new CTitle;

	//����������
	if (pTitle != NULL)
	{
		pTitle->Init(size);
	}

	return pTitle;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			m_apScene2D[nCount] = new CScene2D;
			m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
			m_apScene2D[nCount]->Init(size);
			m_pos = m_apScene2D[nCount]->GetPosition();
			m_pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
			m_apScene2D[nCount]->SetPosition(m_pos);
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	//for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	//{
	//	if (m_apScene2D[nCount] != NULL)
	//	{
	//		m_apScene2D[nCount]->Draw();
	//	}
	//}
}
