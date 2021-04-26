//=============================================================================
//
//	セリフNo1 [talk no1.cpp]
//	Author:筒井 俊稀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "talk_base.h"
#include "resource manager.h"
#include "inputkeyboard.h"
#include "inputcontroller.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "talk no1.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TALK_APPEAR (420)	//出現している時間

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkNo1::CTalkNo1(int nPriorit)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CTalkNo1 * CTalkNo1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTalkNo1* pTalkNo1 = nullptr;
	pTalkNo1 = new CTalkNo1;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo1->m_nTexture);

	if (pTalkNo1 != nullptr)
	{
		//位置設定
		pTalkNo1->SetPos(pos);
		//サイズ設定
		pTalkNo1->SetSize(size);
		//テクスチャ設定
		pTalkNo1->BindTexture(Texture);
		//初期化処理
		pTalkNo1->Init();
	}
	return pTalkNo1;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTalkNo1::Init(void)
{
	//出現している時間セット
	SetAppear(TALK_APPEAR);
	//フェード状況設定
	SetFade(FADE_IN);

	//初期化処理
	CTalkbase::Init();
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTalkNo1::Update(void)
{
	CTalkbase::Update();
}
