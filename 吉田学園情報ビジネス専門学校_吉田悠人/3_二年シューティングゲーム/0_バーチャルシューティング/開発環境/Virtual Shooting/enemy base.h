//=============================================================================
//
// エネミーベース処理 [enemy base.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define ENEMY_POINTER (5)	//エネミーの最大移動ポインタ
//=============================================================================
//前方宣言
//=============================================================================
class CShotsBase;
typedef enum						//エネミータイプ
{
	ENEMY_TYPE_1 = 0,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	ENEMY_TYPE_4
}ENEMY_TYPE;
typedef enum						//エネミーパターン
{
	BULLET_PATTERN_NONE = 0,		//NULL
	BULLET_PATTERN_SHOTS,			//通常ショット
	BULLET_PATTERN_SPIRAL,			//螺旋ショット
	BULLET_PATTERN_MAX				//マックス
}ENEMY_PATTERN;

//=============================================================================
// クラス定義
//=============================================================================
class CEnemyBase :public CScene2d
{
public:
	CEnemyBase(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ
	~CEnemyBase();									//デストラクタ	

	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄

	HRESULT Init(void);				// 初期化処理
	void	Uninit(void);			// 終了処理
	void	Update(void);			// 更新処理
	void	Draw(void);				// 描画処理
	void	StatasManage(void);		// 状態管理
	void	Damage(int nDamage);	// ダメージ処理
	void	Hit(void);				// 当たり判定
	void	Move(void);				// 移動処理
	void	Rotate(void);			// 回転処理
	void	Bullet(void);			// ショット処理

	void		SetMove(D3DXVECTOR3 move);	// 移動量セッター
	D3DXVECTOR3	GetMove(void);				// 移動量ゲッター
	void		SetLife(int nLife);			// ライフセッター
	int			GetLife(void);				// ライフゲッター
	void		SetScore(int nScore);		// スコアセッター
	int			GetScore(void);				// スコアゲッター
	void		SetMovePointer(D3DXVECTOR3 pointer, int nPointer);	//移動位置セット
	void			SetPattern(ENEMY_PATTERN type);				//攻撃パターンセッター
	ENEMY_PATTERN	GetPattern(void);								//攻撃パターンゲッター
private:
	typedef enum	// エネミーの状態
	{
		STATS_MODE_NORMAL = 0,	// 通常状態
		STATS_MODE_DAMAGE,		// ダメージ状態
		STATS_MODE_DEATH		// 死
	}STATS_MODE;

	STATS_MODE			m_Stats;						// エネミーの状態
	ENEMY_PATTERN		m_Shots;						// ショットタイプ
	D3DXVECTOR3			m_move;							// 移動量
	int					m_Score;						// スコア
	int					m_nLife;						// エネミーのライフ
	int					m_nPointer;						// ポインタ
	D3DXVECTOR3			m_movePointer[ENEMY_POINTER];	// 移動地点ポインター
	bool				m_bAttack;						// 攻撃したか
	CShotsBase*			m_pShotsBase;					// ショットポインタ
};
#endif