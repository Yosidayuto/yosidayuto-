//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : �U�J �����Y
//
//=============================================================================
//=============================================
// �w�b�_�[�t�@�C��
//=============================================
#include "bg.h"
#include "manager.h"
#include "scene2d.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBg::CBg()
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pD3DDevice, BG1_TEXTURE, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pD3DDevice, BG2_TEXTURE, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pD3DDevice, BG3_TEXTURE, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pD3DDevice, BG4_TEXTURE, &m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
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
CBg * CBg::Create(D3DXVECTOR3 size)
{
	CBg *pBg;
	//�C���X�^���X����
	pBg = new CBg;

	//����������
	pBg->Init(size);

	return pBg;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//�C���X�^���X����
		m_apScene2D[nCount] = new CScene2D;
		switch (nCount)
		{
		case 0:
			//BG1_TEXTURE�̏���������
			m_apScene2D[nCount]->Init(size);
			break;

		case 1:
			//BG2_TEXTURE�̏���������
			m_apScene2D[nCount]->Init(size / 2 + (size / 4));
			break;

		case 2:
			//BG3_TEXTURE�̏���������
			m_apScene2D[nCount]->Init(size / 2 + (size / 4));
			break;

		case 3:
			//BG4_TEXTURE�̏���������
			m_apScene2D[nCount]->Init(size / 2 + (size / 4));
			break;

		default:
			break;
		}
	
		//�ʒu�ݒ�
		m_pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		m_apScene2D[nCount]->SetPosition(m_pos);
		
		//�e�N�X�`���Z�b�g
		m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
	}

	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
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
void CBg::Update(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
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
void CBg::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->Draw();
		}
	}
}

