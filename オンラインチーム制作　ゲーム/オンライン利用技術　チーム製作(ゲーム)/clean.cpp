//=============================================================================
//
// メイン処理 [bullet.cpp]
// Author : 若山言稀
//ポリゴン処理
//=============================================================================

#include"clean.h"
#include"main.h"
#include "manager.h"


//静的メンバ変数
LPDIRECT3DTEXTURE9 CClean::m_pTexture = NULL;

//インスタンス
CClean::CClean()
{
	m_nCountAnime = 0;
	m_nPatternAnime = 0;
}

//デストラクタ
CClean::~CClean()
{

}

//クリエイト
CClean * CClean::Create(D3DXVECTOR3 size)
{
	CClean *pClean;
	pClean = new CClean;
	pClean->Init(size);
	return pClean;
}

HRESULT CClean::Init(D3DXVECTOR3 size)
{
	CScene2D::Init(size);
	CScene2D::SetAnimation((float)m_nPatternAnime, MAX_ANIMATION);

	BindTexture(m_pTexture);


	return S_OK;
}

void CClean::Uninit()
{
	CScene2D::Uninit();
}

void CClean::Update()
{

	m_nCountAnime++;
	//アニメーション速度
	if (m_nCountAnime >= 4.5f)
	{
		CScene2D::SetAnimation((float)m_nPatternAnime, MAX_ANIMATION);

		m_nPatternAnime++;

		m_nCountAnime = 0;

		if (m_nPatternAnime >= MAX_ANIMATION)
		{
			Uninit();
		}
	}
}

void CClean::Draw()
{
	CScene2D::Draw();
}

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

void CClean::Unload()
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}