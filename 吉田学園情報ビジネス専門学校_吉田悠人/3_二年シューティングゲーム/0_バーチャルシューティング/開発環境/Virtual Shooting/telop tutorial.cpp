//=============================================================================
//
//	チュートリアルテロップ[telop tutorial.cpp]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "telop tutorial.h"
#include "telop.h"
#include "manager.h"
#include "renderer.h"


//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTelopTutorial::m_TextureData = { NULL,"data/TEXTURE/Telop_Normal.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CTelopTutorial::CTelopTutorial(int nPriorit) :CScene2d(nPriorit)
{
	m_nPatternAnim = NULL;
}

//=============================================================================
// デストラクト
//=============================================================================
CTelopTutorial::~CTelopTutorial()
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CTelopTutorial::Load(void)
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
void CTelopTutorial::Unload(void)
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
CTelopTutorial * CTelopTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTelopTutorial* pTelopText;
	pTelopText = new CTelopTutorial;

	//位置設定
	pTelopText->SetPos(D3DXVECTOR3(pos.x - TELOP_X_SIZE / 2, pos.y, pos.z));
	//サイズ設定
	pTelopText->SetSize(D3DXVECTOR3(size.x - TELOP_X_SIZE, size.y - TELOP_Y_SIZE, size.z));
	//初期化処理
	pTelopText->Init();

	return pTelopText;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTelopTutorial::Init(void)
{
	//テクスチャ設定
	BindTexture(m_TextureData.m_Texture);
	//アイコンの初期化処理
	CScene2d::Init();
	TelopMove();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTelopTutorial::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTelopTutorial::Update(void)
{
	CScene2d::Update();
	TelopMove();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTelopTutorial::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// テロップを回す処理
//=============================================================================
void CTelopTutorial::TelopMove(void)
{
	// テクスチャのアニメーション処理用
	D3DXVECTOR2 Texture[4];
	//アニメーションカウント
	static int nCounterAnim = 0;
	//アニメーションカウント加算
	nCounterAnim++;
	//一定の数値になったら
	if (nCounterAnim%2)
	{
		//アニメーションをさせる
		m_nPatternAnim++;
		//数値の初期化
		nCounterAnim = 0;
		if (m_nPatternAnim>= 10000)
		{
			//アニメーションの初期化
			m_nPatternAnim = 0;
		}
	}

	Texture[0] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f), 0.0f);
	Texture[1] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 0.0f);
	Texture[2] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f), 1.0f);
	Texture[3] = D3DXVECTOR2(((float)m_nPatternAnim * 0.005f)*(1.0f / 6.0f) + (1.0f / 6.0f), 1.0f);

	//アニメーションの移動量のセット
	TextureAnim(Texture);
}
