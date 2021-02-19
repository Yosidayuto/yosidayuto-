//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//マクロ定義
//=============================================================================
#define STAGE_POS (780)		//ステージ中心
#define STAGE_SIZE (800)	//ステージのサイズ
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene.h"
//=============================================================================
//前方宣言
//=============================================================================
class CPlayer;
class CEnemy;
class CBg;
class CScore;
class CStage;
typedef enum //ステージタイプ
{
	STAGE_TYPE_1 = 0,	//1ステージ
	STAGE_TYPE_2,		//2ステージ
	STAGE_TYPE_3,		//3ステージ
	STAGE_TYPE_MAX
}STAGE_TYPE;

//=============================================================================
// クラス定義
//=============================================================================
class CGame 
{
public:
	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	static HRESULT	Load(void);		// テクスチャ読み込み
	static void		Unload(void);	// テクスチャの破棄

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Draw(void);		// 描画処理
	static CScore*		GetScore(void);		// スコアゲッター
	//static STAGE_TYPE	GetStageType(void);	// ステージタイプゲッター
	static CPlayer*		GetPlayer(void);
private:
	CStage*				m_pStage;			// ステージポインタ
	static CPlayer*		m_pPlayer;			// プレイヤーポインタ
	static CScore*		m_Score;			// スコアポインタ
	static STAGE_TYPE	m_StageType;		// ステージタイプ
};


#endif