//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 俵谷健太郎　吉田悠人
//
//=============================================================================
#include "result.h"
#include "scene2d.h"
#include "game.h"
#include "manager.h"
#include "communication.h"
#include "ui.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_apTexture = {};
CResult::RESULT CResult::m_ResultType = {};

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CResult::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pD3DDevice, RESULT_TEXTURE, &m_apTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CResult::Unload(void)
{
	// テクスチャの破棄
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}

}

//=============================================================================
// 作成処理
//=============================================================================
CResult * CResult::Create(D3DXVECTOR3 size)
{
	CResult *pResult;
	//インスタンス生成
	pResult = new CResult;
	//初期化処理
	if (pResult != NULL)
	{
		pResult->Init(size);
	}
	return pResult;

}

//=============================================================================
// 初期化処理
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
// 終了処理
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
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	
	if (m_apScene2D != NULL)
	{
		m_apScene2D->Update();

	}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}




