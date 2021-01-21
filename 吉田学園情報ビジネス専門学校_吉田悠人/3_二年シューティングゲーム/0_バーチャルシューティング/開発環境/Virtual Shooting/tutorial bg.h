//=============================================================================
//
//	チュートリアル背景[tutorial bg.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _TUTORIAL_BG_H_
#define _TUTORIAL_BG_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "bg.h"
//=============================================================================
// クラス定義
//=============================================================================
class CTutorialBg :public CBgc
{
public:

	CTutorialBg(int nPriorit = 0);			//コンストラクタ
	~CTutorialBg();							//デストラクタ
	static HRESULT			Load(void);
	static void				Unload(void);
	static CTutorialBg*		Create(void);

	HRESULT	Init(void);			//初期化処理
	void	Uninit(void);		//終了処理
	void	Update(void);		//更新処理
	void	Draw(void);			//描画処理

	void	TextureMove(bool bScroll);	//テクスチャの移動
private:
	static TEXTURE_DATA	m_TextureData;	//テクスチャデータ
	float				m_fTexture;		//テクスチャのスクロール値
};
#endif
