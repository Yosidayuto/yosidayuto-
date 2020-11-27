//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 俵谷 健太郎
//
//=============================================================================
#include "title.h"
#include "manager.h"
#include "scene2d.h"


//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE] = {};


//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CTitle::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pD3DDevice, TITLE1_TEXTURE, &m_apTexture[0]);
	//D3DXCreateTextureFromFile(pD3DDevice, TITLE2_TEXTURE, &m_apTexture[1]);
	//D3DXCreateTextureFromFile(pD3DDevice, TITLE3_TEXTURE, &m_apTexture[2]);


	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
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
CTitle * CTitle::Create(D3DXVECTOR3 size)
{
	CTitle *pTitle;
	//インスタンス生成
	pTitle = new CTitle;

	//初期化処理
	if (pTitle != NULL)
	{
		pTitle->Init(size);
	}

	return pTitle;
}

//=============================================================================
// 初期化処理
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
// 終了処理
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
// 更新処理
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
// 描画処理
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
