//=============================================================================
//
// リザルト処理 [result.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RESULT	(2)
#define RESULT_TEXTURE	"data/TEXTURE/result001.png"			// テクスチャパス(リザルト)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// リザルトクラス
//*****************************************************************************
class CResult : public CScene
{
public:

	typedef enum
	{
		RESULT_WINNER = 0,								// 勝利画面
		RESULT_LOSER,									// 死亡画面
		RESULT_MAX
	}RESULT;
	CResult();											// コンストラクタ
	~CResult();											// デストラクタ
	static HRESULT Load(void);							// テクスチャ読み込み
	static void Unload(void);							// テクスチャ破棄
	static CResult*Create(D3DXVECTOR3 size);			// 作成処理
	HRESULT Init(D3DXVECTOR3 size);						// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理


private:

	static LPDIRECT3DTEXTURE9 m_apTexture;	// テクスチャのポインタ
	CScene2D *m_apScene2D;					// Scene2Dのポインタ
	D3DXVECTOR3 m_pos;						// 位置
	static RESULT m_ResultType;				// リザルトタイプ

};





#endif // !_RESULT_H_

