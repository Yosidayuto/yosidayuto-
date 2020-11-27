//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �U�J �����Y
//
//=============================================================================
#include "result.h"
#include "scene2d.h"
#include "game.h"
#include "manager.h"
#include "communication.h"
#include "ui.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_apTexture = {};
CResult::RESULT CResult::m_ResultType = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult() 
{
	if (m_apScene2D != NULL)
	{
		m_apScene2D = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ResultType = RESULT_WINNER;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CResult::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pD3DDevice, RESULT_TEXTURE, &m_apTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CResult::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}

}

//=============================================================================
// �쐬����
//=============================================================================
CResult * CResult::Create(D3DXVECTOR3 size)
{
	CResult *pResult;
	//�C���X�^���X����
	pResult = new CResult;
	//����������
	if (pResult != NULL)
	{
		pResult->Init(size);
	}
	return pResult;

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 size)
{
	if (m_apScene2D == NULL)
	{
		m_apScene2D = new CScene2D;
		m_apScene2D->BindTexture(m_apTexture);
		m_apScene2D->Init(size);
		m_pos = m_apScene2D->GetPosition();
		m_pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		m_apScene2D->SetPosition(m_pos);
	}
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_CAT);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_DOG);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_RABBIT);
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_SQUIRREL);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		if (CGame::GetPlayerDie(nCount)==true)
		{
			switch (nCount)
			{
			case 0:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_DEATH);

				break;
			case 1:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_DEATH);

				break;
			case 2:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_DEATH);

				break;
			case 3:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT - 200, 0), D3DXVECTOR3(200, 200, 0), CUi::TEX_DEATH);

				break;

			}
		}
		else if(CGame::GetPlayerDie(nCount) == false)
		{
			switch (nCount)
			{
			case 0:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250, 0), D3DXVECTOR3(400, 50, 0), CUi::TEX_WINS_1P);

				break;
			case 1:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250, 0), D3DXVECTOR3(400, 50, 0), CUi::TEX_WINS_2P);

				break;
			case 2:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250, 0), D3DXVECTOR3(400, 50, 0), CUi::TEX_WINS_3P);

				break;
			case 3:
				CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250, 0), D3DXVECTOR3(400, 50, 0), CUi::TEX_WINS_4P);

				break;

			}

		}
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	if (m_apScene2D != NULL)
	{
		m_apScene2D->Uninit();
		m_apScene2D = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	
	if (m_apScene2D != NULL)
	{
		m_apScene2D->Update();

	}
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}




