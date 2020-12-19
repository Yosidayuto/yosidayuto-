//=============================================
//
// 歯磨きエフェクト処理 [clean.cpp]
// Author : 若山言稀
//
//=============================================
//=============================================
// ヘッダーファイル
//=============================================
#include "clean.h"
#include "main.h"
#include "manager.h"

//=============================================
//静的メンバ変数宣言
//=============================================
LPDIRECT3DTEXTURE9 CClean::m_pTexture = NULL;
//=============================================
//インスタンス
//=============================================
CClean::CClean()
{
	m_nCountAnime = 0;
	m_nPatternAnime = 0;
}
//=============================================
//デストラクタ
//=============================================
CClean::~CClean()
{

}
//=============================================
// 生成処理
//=============================================
CClean * CClean::Create(D3DXVECTOR3 size)
{

	CClean *pClean;
	//インスタンス生成
	pClean = new CClean;
	//初期化処理
	pClean->Init(size);
	return pClean;
}
//=============================================
// 初期化処理
//=============================================
HRESULT CClean::Init(D3DXVECTOR3 size)
{
	CScene2D::Init(size);
	//テクスチャ位置設定
	CScene2D::SetAnimation((float)m_nPatternAnime, MAX_ANIMATION);
	//テクスチャセット
	BindTexture(m_pTexture);

	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void CClean::Uninit()
{
	CScene2D::Uninit();
}

//=============================================
// 更新処理
//=============================================
void CClean::Update()
{

	m_nCountAnime++;
	//アニメーション速度
	if (m_nCountAnime >= 4.5f)
	{
		//テクスチャアニメーションセット
		CScene2D::SetAnimation((float)m_nPatternAnime, MAX_ANIMATION);

		m_nPatternAnime++;

		m_nCountAnime = 0;

		if (m_nPatternAnime >= MAX_ANIMATION)
		{
			Uninit();
		}
	}
}

//=============================================
// 描画処理
//=============================================
void CClean::Draw()
{
	CScene2D::Draw();
}

//=============================================
// 読み込み処理
//=============================================
HRESULT CClean::Load()
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		CLEAN_TEXTURE,//ファイルの名前
		&m_pTexture);

	return S_OK;
}

//=============================================
// 読み込み破棄処理
//=============================================
void CClean::Unload()
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}