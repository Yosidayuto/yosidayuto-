#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
//------------------------------------
//マクロ定義
//------------------------------------
#define MAX_STAGE 1		//ステージ数
//------------------------------------
//前置処理
//------------------------------------
class CLife;
class CPlayer;
class CEnemy;
class CBg;
class CScore;
//------------------------------------
//クラス処理
//------------------------------------
class CGame 
{
public:
	CGame();	//コンストラクタ
	~CGame();	//デストラクタ
	typedef enum
	{
		STAGE_TYPE_1 = 0,
		STAGE_TYPE_2,
		STAGE_TYPE_3,
		STAGE_TYPE_MAX
	}STAGE_TYPE;



	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理
	static CLife	*GetLife(void);	//ライフ取得
	static CScore	*GetScore(void);//ゲットスコア
	static STAGE_TYPE SetStage(void) { return m_StageType; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
private:
	void			EnemeyCreate(void);	//エネミークリエイト
	void			StageMode(void);
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
		ENEMY_CREATE_MAX,	//フェーズ
	}ENEMY_CREATE;
	ENEMY_CREATE	m_EnemyCreate;	//エネミーの出現モード
	int				m_nCountEnemy;	//エネミー出現までのカウント


	static CLife	*m_Life;				//ライフクラス
	static	CPlayer			*m_pPlayer;				//プレイヤークラス
	CBg				*m_pBg;					//背景クラス
	static CScore	*m_Score;				//スコアクラス
	static STAGE_TYPE m_StageType;
};


#endif