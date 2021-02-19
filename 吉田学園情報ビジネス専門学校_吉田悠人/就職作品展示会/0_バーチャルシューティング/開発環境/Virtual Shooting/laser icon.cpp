//=============================================================================
//
//	レーザーアイコン[laser icon.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "laser icon.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_ICON CLaserIcon::m_TextureData = { NULL,"data/TEXTURE/UI_Laser.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CLaserIcon::CLaserIcon()
{

}

//=============================================================================
// デストラクト
//=============================================================================
CLaserIcon::~CLaserIcon()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CLaserIcon::Load(void)
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
void CLaserIcon::Unload(void)
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
CLaserIcon * CLaserIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLaserIcon* pLaserIcon;
	pLaserIcon = new CLaserIcon;

	//位置設定
	pLaserIcon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//サイズ設定
	pLaserIcon->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//初期化処理
	pLaserIcon->Init();

	return pLaserIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLaserIcon::Init(void)
{
	//テクスチャ設定
	BindTexture(m_TextureData.m_Texture);
	//アイコンの初期化処理
	CTexture::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLaserIcon::Uninit(void)
{
	CTexture::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLaserIcon::Update(void)
{
	CTexture::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CLaserIcon::Draw(void)
{
	CTexture::Draw();
}
