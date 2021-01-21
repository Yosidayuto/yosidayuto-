//=============================================================================
//
//	ライフui[life ui.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "life ui.h"
#include "renderer.h"
#include "manager.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CLifeUi::m_TextureData = { NULL,	"data/TEXTURE/Life_UI.png", };

CLifeUi::CLifeUi(int nPriorit) :CScene2d(nPriorit)
{
}

CLifeUi::~CLifeUi()
{
}

HRESULT CLifeUi::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_pTexture);

	return S_OK;
}

void CLifeUi::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_pTexture != NULL)
	{
		m_TextureData.m_pTexture->Release();
		m_TextureData.m_pTexture = NULL;
	}
}

CLifeUi * CLifeUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLifeUi *pLifeUi;
	pLifeUi = new CLifeUi;

	//位置設定
	pLifeUi->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//サイズ設定
	pLifeUi->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//テクスチャ設定
	pLifeUi->BindTexture(m_TextureData.m_pTexture);
	//初期化処理
	pLifeUi->Init();
	return pLifeUi;
}

HRESULT CLifeUi::Init(void)
{
	CScene2d::Init();
	return S_OK;
}

void CLifeUi::Uninit(void)
{
	CScene2d::Uninit();
}

void CLifeUi::Update(void)
{
	CScene2d::Update();
}

void CLifeUi::Draw(void)
{
	CScene2d::Draw();
}
