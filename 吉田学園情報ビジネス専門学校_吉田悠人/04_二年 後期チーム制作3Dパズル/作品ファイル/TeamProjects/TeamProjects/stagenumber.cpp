 //=============================================================================
//
//	stagenumberヘッダ [stagenumber.cpp]
//	Author : 筒井　俊稀
//
//=============================================================================
//=============================================================================
// インクルードファイル
//=============================================================================
#include "stagenumber.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_PATH_STAGENUMBER_1 "Data/Texture/stage/stage1.png"
#define TEXTURE_PATH_STAGENUMBER_2 "Data/Texture/stage/stage2.png"
#define TEXTURE_PATH_STAGENUMBER_3 "Data/Texture/stage/stage3.png"

//=============================================================================
// 静的メンバ変数宣言初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CStageNumber::m_apTexture[STAGE_NUM_MAX] = {};

//=============================================================================
// インクルードファイル
//=============================================================================
CStageNumber::CStageNumber()
{

}

//=============================================================================
// インクルードファイル
//=============================================================================
CStageNumber::~CStageNumber()
{
}

//=============================================================================
// インクルードファイル
//=============================================================================
CStageNumber * CStageNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, STAGE_NUM type)
{
	// メモリの確保
	CStageNumber * pStageNumber = new CStageNumber;

	if (pStageNumber != NULL)
	{
		// 座標をset
		pStageNumber->SetPos(pos);
		// サイズをset
		pStageNumber->SetSize(size);
		// テクスチャ指定
		pStageNumber->BindTexture(m_apTexture[type]);
		// 初期化処理
		pStageNumber->Init();
	}

	return pStageNumber;
}

//=============================================================================
// インクルードファイル
//=============================================================================
HRESULT CStageNumber::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_STAGENUMBER_1, &m_apTexture[STAGE_NUM_1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_STAGENUMBER_2, &m_apTexture[STAGE_NUM_2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH_STAGENUMBER_3, &m_apTexture[STAGE_NUM_3]);

	return S_OK;
}

//=============================================================================
// インクルードファイル
//=============================================================================
void CStageNumber::Unload(void)
{
	for (int nCount = STAGE_NUM_1; nCount < STAGE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// インクルードファイル
//=============================================================================
HRESULT CStageNumber::Init()
{
	CUi::Init();
	return S_OK;
}

//=============================================================================
// インクルードファイル
//=============================================================================
void CStageNumber::Uninit(void)
{
	CUi::Uninit();
}

//=============================================================================
// インクルードファイル
//=============================================================================
void CStageNumber::Update(void)
{
	CUi::Update();
}

//=============================================================================
// インクルードファイル
//=============================================================================
void CStageNumber::Draw(void)
{
	CUi::Draw();
}
