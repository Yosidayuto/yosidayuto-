//=============================================================================
//
// 待機画面処理 [wait.cpp]
// Author : 俵谷 健太郎
//
//=============================================================================
#include "wait.h"
#include "manager.h"
#include "scene2d.h"


//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CWait::m_apTexture[MAX_WAIT] = {};


//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CWait::~CWait()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CWait::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pD3DDevice, WAIT_TEXTURE, &m_apTexture[0]);


	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CWait::Unload(void)
{
	for (int nCount = 0; nCount < MAX_WAIT; nCount++)
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
CWait * CWait::Create(D3DXVECTOR3 size)
{
	CWait *pTitle;
	//インスタンス生成
	pTitle = new CWait;

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
// 終了処理
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
// 更新処理
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
// 描画処理
//=============================================================================
void CWait::Draw(void)
{
}
