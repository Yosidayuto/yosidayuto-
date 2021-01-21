//=============================================================================
//
//	ボタン（仮）[button.h]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "button p.h"
#include "renderer.h"
#include "manager.h"
#include "inputmouse.h"
#include "scene2d.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CButtonp::m_TextureData[BUTTON_MAX] =
{	NULL,"data/TEXTURE/buttonA.png",
	NULL,"data/TEXTURE/buttonC_over.png"	};

//=============================================================================
// コンストラクタ
//=============================================================================
CButtonp::CButtonp(int nPriorit)
{
	m_pScene2d = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CButtonp::~CButtonp()
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CButtonp::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCountBotton = 0; nCountBotton<BUTTON_MAX; nCountBotton++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			m_TextureData[nCountBotton].m_cFileName,
			&m_TextureData[nCountBotton].m_pTexture);
	}

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CButtonp::Unload(void)
{
	for (int nCountBotton = 0; nCountBotton < BUTTON_MAX; nCountBotton++)
	{
		//テクスチャの破棄
		if (m_TextureData[nCountBotton].m_pTexture != NULL)
		{
			m_TextureData[nCountBotton].m_pTexture->Release();
			m_TextureData[nCountBotton].m_pTexture = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CButtonp::Init(void)
{
	//位置設定
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);
	//サイズ設定
	D3DXVECTOR3 size = D3DXVECTOR3(GetSize().x, GetSize().y, GetSize().z);

	m_pScene2d = CScene2d::Create(pos, size,0.0f, m_TextureData[BUTTON_NORMAL].m_pTexture,1);
	//オブジェクト2D初期化
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CButtonp::Uninit(void)
{
	//オブジェクト2D終了
	CScene2d::Uninit();
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CButtonp::Update(void)
{
	//オブジェクト2D更新
	CScene2d::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CButtonp::Draw(void)
{
	//オブジェクト2D描画
	CScene2d::Draw();
}

//=============================================================================
// 当たり判定処理
//=============================================================================
bool CButtonp::Hit(void)
{
	//マウスポインタ取得
	CInihMouse *pMouse = CManager::GetMouse();	
	//マウス位置取得
	D3DXVECTOR3 MousePos = D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f);
	//ボタン位置取得
	D3DXVECTOR3 ButtonPos = m_pScene2d->GetPos();
	//ボタンサイズ取得
	D3DXVECTOR3 ButtonSize = m_pScene2d->GetSize();
	//判定
	bool		bButton;

	//当たり判定
	if (MousePos.x > ButtonPos.x - ButtonSize.x / 2
		&& MousePos.x  < ButtonPos.x + ButtonSize.x / 2
		&& MousePos.y > ButtonPos.y - ButtonSize.y / 2
		&& MousePos.y < ButtonPos.y + ButtonSize.y / 2)
	{
		//当たったら
		m_pScene2d->BindTexture(m_TextureData[BUTTON_PUSH].m_pTexture);
		bButton = true;
	}
	else
	{
		//当たってないとき
		m_pScene2d->BindTexture(m_TextureData[BUTTON_NORMAL].m_pTexture);
		bButton = false;
	}
	return bButton;
}
