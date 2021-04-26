//=============================================================================
//
//	セリフNo3 [talk no3.cpp]
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
#include "talk no3.h"
#include "tutorial.h"
#include "player.h"
#include "child.h"

//=============================================================================
// マクロ定義
//=============================================================================
//#define TALK_APPEAR (420)	//出現している時間

//=============================================================================
// コンストラクタ
//=============================================================================
CTalkNo3::CTalkNo3(int nPriorit)
{
	m_bTutorial = false;
	m_pTutorial = nullptr;
	m_pChild = nullptr;
}

//=============================================================================
// 生成処理
//=============================================================================
CTalkNo3 * CTalkNo3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTalkNo3* pTalkNo3 = nullptr;
	pTalkNo3 = new CTalkNo3;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pTalkNo3->m_nTexture);

	//NULLチェック
	if (pTalkNo3 != nullptr)
	{
		//位置設定
		pTalkNo3->SetPos(pos);
		//サイズ設定
		pTalkNo3->SetSize(size);
		//テクスチャ設定
		pTalkNo3->BindTexture(Texture);
		//初期化処理
		pTalkNo3->Init();
	}
	return pTalkNo3;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTalkNo3::Init(void)
{
	//出現している時間セット
	SetAppear(0);
	//フェード状況設定
	SetFade(FADE_IN);

	//初期化処理
	CTalkbase::Init();
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTalkNo3::Update(void)
{
	CTalkbase::Update();
}

//=============================================================================
// トーク処理
//=============================================================================
void CTalkNo3::Talk(void)
{
	//子供(プレイヤーのくっついてるブロック)ポインタ処理
	CChild * pChild = (CChild*)(GetTop()[PRIORITY_OBJECT_CHILD]);
	while (pChild != NULL)
	{
		//何かにくっついている
		if (pChild->GetIsActive())
		{
			//透過状況を設定
			m_Fade = FADE_OUT;
		}
		pChild = (CChild*)(pChild->GetNext());
	}
}

