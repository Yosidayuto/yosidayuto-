//=============================================================================
//
// エネミータイプ2処理 [enemy type2.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy type2.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TYPE1_SIZE	(100.0f)	//サイズ
#define TYPE1_LIFE	(2)		//ライフ
#define TYPE1_SCORE (100)	//スコア
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CEnemyType2::m_TextureData = { NULL,"data/TEXTURE/Enemy_2.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CEnemyType2::CEnemyType2(int nPriorit)
{
}
//=============================================================================
// デストラクト
//=============================================================================
CEnemyType2::~CEnemyType2()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyType2::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CEnemyType2::Unload(void)
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
CEnemyType2 * CEnemyType2::Create(D3DXVECTOR3 pos)
{
	//メモリ確保
	CEnemyType2* pEnemyType2 = NULL;
	pEnemyType2 = new CEnemyType2;

	//NULLチェック
	if (pEnemyType2 != NULL)
	{
		//位置設定
		pEnemyType2->SetPos(pos);
		//サイズ設定
		pEnemyType2->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//ライフ設定
		pEnemyType2->SetLife(TYPE1_LIFE);
		//スコア設定
		pEnemyType2->SetScore(TYPE1_SCORE);
		//テクスチャセット
		pEnemyType2->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pEnemyType2->Init();

	}
	return pEnemyType2;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyType2::Init(void)
{
	CEnemyBase::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyType2::Uninit(void)
{
	CEnemyBase::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyType2::Update(void)
{
	//回転処理
	Rotate();
	//攻撃処理
	Bullet();
	CEnemyBase::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyType2::Draw(void)
{
	CEnemyBase::Draw();
}
