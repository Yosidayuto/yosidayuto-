//=============================================================================
//
// 死亡画面処理 [die screen.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _DIE_SCREEN_H_
#define _DIE_SCREEN_H_
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DIE_SCREEN "data/TEXTURE/die_001.png"// ポリゴンのテクスチャパス

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// ポリゴンクラス
//*****************************************************************************
class CDieScreen : public CScene2D
{
public:
	CDieScreen();						// コンストラクタ
	~CDieScreen();						// デストラクタ
	static HRESULT Load(void);			// テクスチャ読み込み
	static void Unload(void);			// テクスチャ破棄
	static CDieScreen *Create(void);	// 作成処理

	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャのポインタ
};




#endif // !_DIE_SCREEN_H_



