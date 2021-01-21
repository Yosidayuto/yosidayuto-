//=============================================================================
//
// 歯のテクスチャ処理 [tooth.h]
// Author : 俵谷健太郎 若山言稀
//
//=============================================================================
#ifndef _TOOTH_H_
#define _TOOTH_H_


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_TEXTURE	"data/TEXTURE/teeth001.png"// ポリゴンのテクスチャパス
#define MAX_POLYGON_TEX	(25)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// ポリゴンクラス
//*****************************************************************************
class CTooth : public CScene2D
{
public:
	CTooth();													// コンストラクタ
	~CTooth();													// デストラクタ
	static HRESULT Load(void);									// テクスチャ読み込み
	static void Unload(void);									// テクスチャ破棄
	static CTooth *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 作成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	void Color(void);											// カラー変更
	void SetRotation(float fAngle);								// テクスチャ回転

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;						// テクスチャのポインタ
	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_size;											// サイズ
};




#endif // !_TOOTH_H_



