//=============================================================================
//
// ステージ処理 [stage.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "game.h"
#include "enemy base.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY (200)	//最大エネミー数
#define MAX_STAGE (3)	//最大ステージ数
//=============================================================================
//前方宣言
//=============================================================================
class CEnemy;
class CEnemyBase;

typedef enum	//エネミーの出現モード
{
	ENEMY_CREATE_NONE = 0,
	ENEMY_CREATE_1,		//フェーズ１
	ENEMY_CREATE_2,		//フェーズ２
	ENEMY_CREATE_3,		//フェーズ３
	ENEMY_CREATE_4,		//フェーズ４
	ENEMY_CREATE_5,		//フェーズ5
	ENEMY_CREATE_6,		//フェーズ6
	ENEMY_CREATE_7,		//フェーズ7
	ENEMY_CREATE_8,		//フェーズ8
	ENEMY_CREATE_9,		//フェーズ9
	ENEMY_CREATE_MAX,
}STAGE_ENEMY;

typedef struct	//エネミーの移動情報
{
	D3DXVECTOR3		pos;		//位置
	float			fSpeed;		//スピード
} MOVE_DATA;

typedef struct	//エネミー情報
{
	MOVE_DATA	moveData[ENEMY_POINTER];	//移動情報
	ENEMY_TYPE	EnemyType;					//エネミータイプ
} SPAWN_DATA;

typedef struct	//フェーズ情報
{
	SPAWN_DATA	EnemySpawn[MAX_ENEMY];
} PHASE_DATA;


//=============================================================================
// クラス定義
//=============================================================================
class CStage
{
public:

	CStage();	//コンストラクタ
	~CStage();	//デストラクタ

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Result(STAGE_TYPE stage);	// リザルト
	void			SetEnemyCount(int nConut);	// エネミーカウントセット
	void			EnemeyCreate(void);			// エネミークリエイト
	static void		LoadFile(void);				// ロードファイル
	virtual void	StageMode(void) = 0;		// エネミーのスポーンモード

private:
	int					m_nCountEnemy;							// エネミー出現までのカウント
	static PHASE_DATA	m_Enemy[ENEMY_CREATE_MAX][MAX_STAGE];	// ステージのエネミー出現データ
	static char*		pFileName[STAGE_TYPE_MAX];				// ファイルネーム
};
#endif