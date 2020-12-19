//=============================================================================
//
// �ҋ@��ʏ��� [wait.cpp]
// Author : �U�J �����Y
//
//=============================================================================
#include "wait.h"
#include "manager.h"
#include "scene2d.h"


//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CWait::m_apTexture[MAX_WAIT] = {};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWait::CWait()
{
	for (int nCount = 0; nCount < MAX_WAIT; nCount++)
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
CWait::~CWait()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CWait::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pD3DDevice, WAIT_TEXTURE, &m_apTexture[0]);


	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CWait::Unload(void)
{
	for (int nCount = 0; nCount < MAX_WAIT; nCount++)
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
CWait * CWait::Create(D3DXVECTOR3 size)
{
	CWait *pTitle;
	//�C���X�^���X����
	pTitle = new CWait;

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
HRESULT CWait::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_WAIT; nCount++)
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
void CWait::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_WAIT; nCount++)
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
void CWait::Update(void)
{
	for (int nCount = 0; nCount < MAX_WAIT; nCount++)
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
void CWait::Draw(void)
{
}
