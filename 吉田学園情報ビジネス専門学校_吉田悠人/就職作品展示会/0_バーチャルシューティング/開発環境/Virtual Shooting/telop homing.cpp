//=============================================================================
//
//	ホーミングテロップ[telop homing.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "telop homing.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTelopHoming::m_TextureData = { NULL,"data/TEXTURE/Telop_Homing.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CTelopHoming::CTelopHoming(int nPriorit) :CScene2d(nPriorit)
{

}

//=============================================================================
// デストラクト
//=============================================================================
CTelopHoming::~CTelopHoming()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CTelopHoming::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CTelopHoming::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CTelopHoming * CTelopHoming::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTelopHoming* pTelopHoming;
	pTelopHoming = new CTelopHoming;

	//位置設定
	pTelopHoming->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE, pos.y, pos.z));
	//サイズ設定
	pTelopHoming->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE / 2, size.y, size.z));
	//初期化処理
	pTelopHoming->Init();

	return pTelopHoming;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTelopHoming::Init(void)
{
	//テクスチャ設定
	BindTexture(m_TextureData.m_Texture);
	//アイコンの初期化処理
	CScene2d::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTelopHoming::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTelopHoming::Update(void)
{
	CScene2d::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTelopHoming::Draw(void)
{
	CScene2d::Draw();
}
