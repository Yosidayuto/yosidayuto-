//=============================================================================
//
// 歯のテクスチャ処理 [ui.h]
// Author : 若山　言稀
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//1Pのテクスチャ
#define UI_TEXTURE_CAT	"data/TEXTURE/cat001.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_1P	"data/TEXTURE/playerui_001.png"// ポリゴンのテクスチャパス
//2Pのテクスチャ
#define UI_TEXTURE_DOG	"data/TEXTURE/dog001.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_2P "data/TEXTURE/playerui_002.png"// ポリゴンのテクスチャパス
//3Pのテクスチャ	 _
#define UI_TEXTURE_USAGI "data/TEXTURE/usa001.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_3P "data/TEXTURE/playerui_003.png"// ポリゴンのテクスチャパス
//4Pのテクスチャ	 _
#define UI_TEXTURE_RISU "data/TEXTURE/risu001.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_4P "data/TEXTURE/playerui_004.png"// ポリゴンのテクスチャパス
//ターンテクスチャ_ 
#define UI_TEXTURE_YOUTRUN "data/TEXTURE/yourturn.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_WAIT "data/TEXTURE/wait.png"// ポリゴンのテクスチャパス
//死亡テクスチャ  _ 
#define UI_TEXTURE_DEATH "data/TEXTURE/death.png"// ポリゴンのテクスチャパス
//勝利テクスチャ
#define UI_TEXTURE_WINS_1P "data/TEXTURE/Wins_1P.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_WINS_2P "data/TEXTURE/Wins_2P.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_WINS_3P "data/TEXTURE/Wins_3P.png"// ポリゴンのテクスチャパス
#define UI_TEXTURE_WINS_4P "data/TEXTURE/Wins_4P.png"// ポリゴンのテクスチャパス
//ロードテクスチャ
#define UI_TEXTURE_LOAD "data/TEXTURE/brush1.png"// ポリゴンのテクスチャパス


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// ポリゴンクラス
//*****************************************************************************
class CUi : public CScene2D
{
public:
	typedef enum
	{
		TEX_LOAD = 0,
		TEX_DOG,
		TEX_CAT,
		TEX_RABBIT,
		TEX_SQUIRREL,
		TEX_1P,
		TEX_2P,
		TEX_3P,
		TEX_4P,
		TEX_YOUTRUN,
		TEX_WAIT,
		TEX_DEATH,
		TEX_WINS_1P,
		TEX_WINS_2P,
		TEX_WINS_3P,
		TEX_WINS_4P,
		TEX_MAX
	}TEXTYPE;
	CUi();																// コンストラクタ
	~CUi();																// デストラクタ
	static HRESULT Load(void);											// テクスチャ読み込み
	static void Unload(void);											// テクスチャ破棄
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTYPE TYPE);// 作成処理
	TEXTYPE GetTexType(TEXTYPE TYPE);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void LoadPos(void);
private:

	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_MAX];				// テクスチャのポインタ
	TEXTYPE TexType;											// タイプ
	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_size;											// サイズ
	D3DXVECTOR3 m_Minsize;                                      // 最小サイズ
	static char *m_TextureName[TEX_MAX];						// テクスチャネーム
	bool m_bBig;                                                // 大きくする
	bool m_bLoad;
};
#endif // !_UI_H_



