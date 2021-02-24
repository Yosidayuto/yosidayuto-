//=============================================================================
//
// ターン待ち処理 [turn wait.cpp]
// Author : 吉田悠人
//
//=============================================================================

#include "turn wait.h"
#include "manager.h"
#include "scene2d.h"


//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTurnWait::m_apTexture[MAX_TURN_WAIT] = {};


//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CTurnWait::~CTurnWait()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CTurnWait::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pD3DDevice, TURN_WAIT_TEXTURE, &m_apTexture[0]);


	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CTurnWait::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
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
CTurnWait * CTurnWait::Create(D3DXVECTOR3 size)
{
	CTurnWait *pTurnWait;
	//インスタンス生成
	pTurnWait = new CTurnWait;

	//初期化処理
	if (pTurnWait != NULL)
	{
		pTurnWait->Init(size);
	}

	return pTurnWait;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTurnWait::Init(D3DXVECTOR3 size)
{
	for (int nCount = 0; nCount < MAX_TURN_WAIT; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			m_apScene2D[nCount] = new CScene2D;
			//テクスチャ設定
			m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
			//初期化処理
			m_apScene2D[nCount]->Init(size);
			//位置取得
			m_pos = m_apScene2D[nCount]->GetPosition();
			//位置設定
			m_pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
			m_apScene2D[nCount]->SetPosition(m_pos);
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
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
// 更新処理
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
// 描画処理
//=============================================================================
void CTurnWait::Draw(void)
{
}
