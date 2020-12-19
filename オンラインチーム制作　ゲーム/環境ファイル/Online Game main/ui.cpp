//=============================================================================
//
// UIテクスチャ処理 [ui.cpp]
// Author : 吉田悠人
//
//=============================================================================
#include "ui.h"
#include "manager.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TEX_MAX] = {};
char *CUi::m_TextureName[TEX_MAX] =
{
	UI_TEXTURE_LOAD,
	UI_TEXTURE_DOG,
	UI_TEXTURE_CAT,
	UI_TEXTURE_USAGI,
	UI_TEXTURE_RISU,
	UI_TEXTURE_1P,
	UI_TEXTURE_2P,
	UI_TEXTURE_3P,
	UI_TEXTURE_4P,
	UI_TEXTURE_YOUTRUN,
	UI_TEXTURE_WAIT,
	UI_TEXTURE_DEATH,
	UI_TEXTURE_WINS_1P,
	UI_TEXTURE_WINS_2P,
	UI_TEXTURE_WINS_3P,
	UI_TEXTURE_WINS_4P,
};
//=============================================================================
// コンストラクタ
//=============================================================================
CUi::CUi()
{
	m_bBig = false;
	m_bLoad = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CUi::~CUi()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CUi::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		//テクスチャ
		D3DXCreateTextureFromFile(pD3DDevice, m_TextureName[nCount], &m_pTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CUi::Unload(void)
{
	// テクスチャの破棄
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
// UI作成処理
//=============================================================================

CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTYPE TYPE)
{
	CUi *pUi;
	//インスタンス生成
	pUi = new CUi;

	//初期化処理
	if (pUi != NULL)
	{
		pUi->GetTexType(TYPE);
		pUi->Init(pos, size);
	}
	return pUi;
}

CUi::TEXTYPE CUi::GetTexType(TEXTYPE TYPE)
{
	TexType = TYPE;
	return TexType;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{

	BindTexture(m_pTexture[TexType]);

	//初期化処理
	CScene2D::Init(size);
	m_pos = pos;
	//位置設定
	SetPosition(m_pos);
	//サイズ情報保存
	m_size = size;
	m_Minsize = size;

	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUi::Update(void)
{
	if (TexType == TEX_DEATH)
	{
		if (!m_bBig)
		{
			m_size = D3DXVECTOR3(m_Minsize.x * 3, m_Minsize.y * 3, 0.0f);
			m_bBig = true;
		}
		else
		{
			//サイズを小さくする
			m_size += D3DXVECTOR3(-3.0f, -3.0f, 0.0f);

			//サイズを縮小を止める
			if (m_size.x <= m_Minsize.x && m_size.y <= m_Minsize.y)
			{
				m_size = m_Minsize;
			}
		}

		//サイズ更新
		CScene2D::SetSize(m_size);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUi::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ロードUIの処理
//=============================================================================
void CUi::LoadPos(void)
{
	D3DXVECTOR3 LoadUiPos = GetPosition();
	if (m_bLoad == false)
	{
		if (LoadUiPos.y <= m_pos.y + 15.0f)
		{
			LoadUiPos.y += 0.4f;
			SetPosition(LoadUiPos);
		}
		else
		{
			m_bLoad = true;
		}
	}
	else
	{
		if (LoadUiPos.y >= m_pos.y)
		{
			LoadUiPos.y -= 0.5f;
			SetPosition(LoadUiPos);
		}
		else
		{
			m_bLoad = false;
		}
	}

}

