//=============================================================================
//
// マウスポインタ処理 [mouse_pointer.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _MOUSE_POINTER_H_
#define _MOUSE_POINTER_H_


#define MOUSE_POINTER "data/TEXTURE/brush1.png"	// テクスチャパス

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マウスポインタークラス
//*****************************************************************************
class CPointer : public CScene2D
{
public:
	CPointer();										// コンストラクタ
	~CPointer();									// デストラクタ
	static HRESULT Load(void);						// テクスチャ読み込み
	static void Unload(void);						// テクスチャ破棄
	static CPointer *Create(void);					// 作成処理
	HRESULT Init(void);								// 初期化処理
	void	Uninit(void);							// 終了処理
	void	Update(void);							// 更新処理
	void	Draw(void);								// 描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_size;								// サイズ
};

#endif
