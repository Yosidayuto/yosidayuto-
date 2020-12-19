//=============================================================================
//
// シーン処理 [scene.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POLYGON		(50)		// ポリゴンの最大数

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene();										// コンストラクタ
	virtual ~CScene();								// デストラクタ
	virtual HRESULT Init(D3DXVECTOR3 size) = 0;		// 初期化処理
	virtual void Uninit() = 0;						// 終了処理
	virtual void Update(void) = 0;					// 更新処理
	virtual void Draw(void) = 0;					// 描画処理
	static void UpdateAll(void);					// 全オブジェクト更新処理
	static void DrawAll(void);						// 全オブジェクト描画処理
	static void ReleaseAll(void);					// 全オブジェクトリリース処理
	static CScene *GetScene(int nNumber);			// シーンの取得
	void SetObjType(OBJTYPE objType);				// オブジェクト設定
	OBJTYPE GetObjType(void) { return m_objType; }	// オブジェクト状態取得

protected:
	void Release(void);								// リリース処理

private:
	static CScene *m_apScene[MAX_POLYGON];			// シーンの配列
	static int m_nNumAll;							// オブジェクト数
	int m_nID;										// オブジェクト番号
	OBJTYPE m_objType;								// オブジェクトの種類
};

#endif 










