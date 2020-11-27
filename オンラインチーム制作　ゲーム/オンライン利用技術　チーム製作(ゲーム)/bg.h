//=============================================================================
//
// 背景の処理 [bg.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE		(4)								// テクスチャの最大数
#define BG1_TEXTURE		"data/TEXTURE/bg001.png"		// 背景1のテクスチャパス
#define BG2_TEXTURE		"data/TEXTURE/wani_body001.png"	// 背景2のテクスチャパス
#define BG3_TEXTURE		"data/TEXTURE/wani_head001.png"	// 背景3のテクスチャパス
#define BG4_TEXTURE		"data/TEXTURE/wani_eye001.png"	// 背景4のテクスチャパス


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// 背景クラス
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg();													// コンストラクタ
	~CBg();													// デストラクタ
	static HRESULT Load(void);								// テクスチャ読み込み
	static void Unload(void);								// テクスチャ破棄
	static CBg *Create(D3DXVECTOR3 size);					// 作成処理
	HRESULT Init(D3DXVECTOR3 size);							// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];		// テクスチャのポインタ
	CScene2D *m_apScene2D[MAX_TEXTURE];						// Scene2Dのポインタ
	D3DXVECTOR3 m_pos;										// 背景の位置
};




#endif // !_BG_H_





