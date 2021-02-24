//=============================================================================
//
//	タイトル背景[title bg.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _TITLE_BG_H_
#define _TITLE_BG_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// クラス定義
//=============================================================================
class CTitleBg :public CBgc
{
public:

	CTitleBg(int nPriorit = 0);			//コンストラクタ
	~CTitleBg();						//デストラクタ
	static HRESULT		Load(void);
	static void			Unload(void);
	static CTitleBg*	Create(void);


	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理
private:
	static TEXTURE_DATA	m_TextureData;	//テクスチャデータ
};
#endif
