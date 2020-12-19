//=============================================================================
//
// �^�[���҂����� [turn wait.cpp]
// Author : �g�c�I�l
//
//=============================================================================

#include "turn wait.h"
#include "manager.h"
#include "scene2d.h"


//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTurnWait::m_apTexture[MAX_TURN_WAIT] = {};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTurnWait::CTurnWait()
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
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
CTurnWait::~CTurnWait()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CTurnWait::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pD3DDevice, TURN_WAIT_TEXTURE, &m_apTexture[0]);


	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CTurnWait::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
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
CTurnWait * CTurnWait::Create(D3DXVECTOR3 size)
{
	CTurnWait *pTurnWait;
	//�C���X�^���X����
	pTurnWait = new CTurnWait;

	//����������
	if (pTurnWait != NULL)
	{
		pTurnWait->Init(size);
	}

	return pTurnWait;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTurnWait::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			m_apScene2D[nCount] = new CScene2D;
			//�e�N�X�`���ݒ�
			m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
			//����������
			m_apScene2D[nCount]->Init(size);
			//�ʒu�擾
			m_pos = m_apScene2D[nCount]->GetPosition();
			//�ʒu�ݒ�
			m_pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
			m_apScene2D[nCount]->SetPosition(m_pos);
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTurnWait::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
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
void CTurnWait::Update(void)
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
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
void CTurnWait::Draw(void)
{
}
