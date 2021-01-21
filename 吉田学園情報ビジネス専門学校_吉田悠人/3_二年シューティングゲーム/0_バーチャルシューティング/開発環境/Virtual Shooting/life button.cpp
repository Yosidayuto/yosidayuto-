//=============================================================================
//
//	ライフボタン[life button.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "life button.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "game.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CLifeButton::m_TextureData = { NULL,	"data/TEXTURE/Text_Life.png", };

CLifeButton::CLifeButton(int nPriorit) :CButtonp(nPriorit)
{
}

CLifeButton::~CLifeButton()
{
}

HRESULT CLifeButton::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_pTexture);

	return S_OK;
}

void CLifeButton::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_pTexture != NULL)
	{
		m_TextureData.m_pTexture->Release();
		m_TextureData.m_pTexture = NULL;
	}
}

CLifeButton * CLifeButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CLifeButton *pLifeButton;
	pLifeButton = new CLifeButton;

	//位置設定
	pLifeButton->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//サイズ設定
	pLifeButton->SetSize(D3DXVECTOR3(size.x, size.y, size.z));
	//テクスチャ設定
	pLifeButton->BindTexture(m_TextureData.m_pTexture);
	//初期化処理
	pLifeButton->Init();
	return pLifeButton;
}

HRESULT CLifeButton::Init(void)
{
	CButtonp::Init();
	SetPos(D3DXVECTOR3(GetPos().x + 85, GetPos().y, 0.0f));

	return S_OK;
}

void CLifeButton::Uninit(void)
{
	CButtonp::Uninit();
}

void CLifeButton::Update(void)
{

	CButtonp::Update();
}

void CLifeButton::Draw(void)
{

	CButtonp::Draw();
}
