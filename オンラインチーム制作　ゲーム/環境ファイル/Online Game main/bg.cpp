//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : 俵谷 健太郎
//
//=============================================================================
//=============================================
// ヘッダーファイル
//=============================================
#include "bg.h"
#include "manager.h"
#include "scene2d.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_TEXTURE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg()
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pD3DDevice, BG1_TEXTURE, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pD3DDevice, BG2_TEXTURE, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pD3DDevice, BG3_TEXTURE, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pD3DDevice, BG4_TEXTURE, &m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 作成処理
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 size)
{
	CBg *pBg;
	//インスタンス生成
	pBg = new CBg;

	//初期化処理
	pBg->Init(size);

	return pBg;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//インスタンス生成
		m_apScene2D[nCount] = new CScene2D;
		switch (nCount)
		{
		case 0:
			//BG1_TEXTUREの初期化処理
			m_apScene2D[nCount]->Init(size);
			break;

		case 1:
			//BG2_TEXTUREの初期化処理
			m_apScene2D[nCount]->Init(size / 2 + (size / 4));
			break;

		case 2:
			//BG3_TEXTUREの初期化処理
			m_apScene2D[nCount]->Init(size / 2 + (size / 4));
			break;

		case 3:
			//BG4_TEXTUREの初期化処理
			m_apScene2D[nCount]->Init(size / 2 + (size / 4));
			break;

		default:
			break;
		}
	
		//位置設定
		m_pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		m_apScene2D[nCount]->SetPosition(m_pos);
		
		//テクスチャセット
		m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
	}

	return S_OK;

}

//=============================================================================
// 終了処理
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
// 更新処理
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
// 描画処理
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

