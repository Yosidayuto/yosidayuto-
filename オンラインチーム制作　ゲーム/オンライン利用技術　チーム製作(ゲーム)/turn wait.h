#ifndef _TURN_WAIT_H_
#define _TURN_WAIT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TURN_WAIT	(1)
#define TURN_WAIT_TEXTURE	"data/TEXTURE/matching.png"		// 待機画面のテクスチャパス


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
// タイトルクラス
//*****************************************************************************
class CTurnWait : public CScene
{
public:
	CTurnWait();											// コンストラクタ
	~CTurnWait();											// デストラクタ
	static HRESULT Load(void);								// テクスチャ読み込み
	static void Unload(void);								// テクスチャ破棄
	static CTurnWait *Create(D3DXVECTOR3 size);				// 作成処理
	HRESULT Init(D3DXVECTOR3 size);							// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TURN_WAIT];	// テクスチャのポインタ
	CScene2D *m_apScene2D[MAX_TURN_WAIT];					// Scene2Dのポインタ
	D3DXVECTOR3 m_pos;										// 位置
};
#endif // !_TURN_WAIT_H_

