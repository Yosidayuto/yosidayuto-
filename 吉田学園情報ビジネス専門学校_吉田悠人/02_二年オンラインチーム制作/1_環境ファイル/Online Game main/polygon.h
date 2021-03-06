//=============================================================================
//
// 牙の並び処理 [polygon.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMBER (20)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CTooth;

//*****************************************************************************
// 計算クラス
//*****************************************************************************
class CPolygon : public CScene
{
public:
	CPolygon();										// コンストラクタ
	~CPolygon();									// デストラクタ
	static CPolygon *Create(D3DXVECTOR3 size);		// 作成処理
	HRESULT Init(D3DXVECTOR3 size);					// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	int Touch(void);								// タッチ処理
	void TouchCol(int nTooth);						// カラー処理
	static int GetTooth(void);						// 歯のゲッター処理
private:
	CTooth *m_apTooth[MAX_NUMBER];					// ナンバーのポインタ
	D3DXVECTOR3 m_pos;								// 位置
	static int	nCountTooth;						// 牙の数
};



#endif // !_POLYGON_H_

