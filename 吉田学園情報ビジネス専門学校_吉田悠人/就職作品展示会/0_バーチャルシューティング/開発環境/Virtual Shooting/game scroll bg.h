//=============================================================================
//
//	ゲームスクロール背景[game scroll bg.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _GAME_SCROLL_BG_H_
#define _GAME_SCROLL_BG_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// クラス定義
//=============================================================================
class CGameScrollBg :public CBgc
{
public:
	CGameScrollBg(int nPriorit = PRIORITY_BG_0);//コンストラクタ
	~CGameScrollBg();							//デストラクタ

	static HRESULT			Load(void);		//テクスチャ読み込み
	static void				Unload(void);	//テクスチャの破棄
	static CGameScrollBg*	Create(void);	//生成処理

	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理

private:
	static TEXTURE_DATA	m_TextureData;	//テクスチャデータ

};
#endif