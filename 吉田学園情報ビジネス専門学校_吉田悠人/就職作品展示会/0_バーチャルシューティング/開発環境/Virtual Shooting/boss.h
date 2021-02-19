//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_BOSS_BULLET (200)	//最大バレット数

//=============================================================================
//前方宣言
//=============================================================================
class CBossAnime;
class CBulletBase;
//=============================================================================
// クラス定義
//=============================================================================
class CBoss :public CScene2d
{
public:

	CBoss(int nPriorit = PRIORITY_OBJECT_0);	//コンストラクタ
	~CBoss();					//デストラクタ	
	typedef enum  //ボス種類
	{
		BOSS_TYPE_1 = 0,
		BOSS_TYPE_2,
		BOSS_TYPE_3,
		BOSS_TYPE_MAX
	}BOSS_TYPE;

	typedef enum	//ボスパターン
	{
		BOSS_PATTERN_NONE = 0,	//NULL
		BOSS_PATTERN_STRAIGHT,	//直進
		BOSS_PATTERN_CROSS,		//交差
		BOSS_PATTERN_CORNER,	//曲がる
		BOSS_PATTERN_SIDE,		//横移動
		BOSS_PATTERN_U_TURN,	//Uターン
		BOSS_PATTERN_ROUND_TRIP,//往復
		BOSS_PATTERN_MAX		//マックス
	}BOSS_PATTERN;
	typedef enum	//エネミーパターン
	{
		BULLET_PATTERN_NONE = 0,		//NULL
		BULLET_PATTERN_SHOTS,			//通常ショット
		BULLET_PATTERN_HOMING,			//追尾ショット
		BULLET_PATTERN_BUCKSHOT,		//散弾ショット
		BULLET_PATTERN_SPIRAL,			//螺旋ショット
		BULLET_PATTERN_All_DIR,			//全方位ショット
		BULLET_PATTERN_SPLIT,			//分裂ショット
		BULLET_PATTERN_HOMING2,			//追尾ショット2
		BULLET_PATTERN_MAX				//マックス
	}BOSS_PATTERN_BULLET;


	static HRESULT	Load(void);				//テクスチャ読み込み
	static void		Unload(void);			//テクスチャの破棄
	static CBoss*	Create(D3DXVECTOR3 Pos, BOSS_TYPE  nType, D3DXVECTOR3 size);//生成処理

	HRESULT			Init(void);				//初期化処理
	void			Uninit(void);			//終了処理
	void			Update(void);			//更新処理
	void			Draw(void);				//描画処理
	void			Damage(int nDamage);	//ダメージ処理
	static bool		GetEnemyNumber(void) { return m_bDie; };	//エネミーが死んだかゲット
private:
	typedef enum	//エネミーの状態
	{
		STATS_MODE_NONE = 0,	//NULL
		STATS_MODE_NORMAL,		//通常状態
		STATS_MODE_DAMAGE,		//ダメージ状態
		STATS_MODE_DEATH		//死
	}STATS_MODE;

	STATS_MODE		m_Stats;				//ボスの状態
	void			StatasManage(void);		//状態管理

	void		Rotate(void);												//回転処理
	void		Bullet(BOSS_PATTERN_BULLET BulletMode, D3DXVECTOR3 Pos);	//バレット処理
	D3DXVECTOR3	Tracking(float fSpeed, D3DXVECTOR3 Pos);					//追尾処理
	D3DXVECTOR3 Random(float fSpeed);										//ランダム処理
	float		Spiral(void);												//螺旋処理
	void		Hit(D3DXVECTOR3 Pos);										//当たり判定
		
	static TEXTURE_DATA			m_TextureData[BOSS_TYPE_MAX];	//テクスチャデータ
	D3DXVECTOR3					m_pos;							//ボス座標
	D3DXVECTOR3					m_move;							//ボスの移動量
	D3DXVECTOR3					m_size;							//ボスのサイズ
	BOSS_TYPE					m_Type;							//ボスのタイプ
	BOSS_PATTERN_BULLET			m_BulletType;					//ボスの攻撃パターン
	int							m_nLife;						//ボスのライフ
	static int					m_EnemyNumber;					//ボスの総数
	int							m_PatternCount;					//パターンのカウント
	bool						m_bBulletMode;					//攻撃が終わったか
	int							m_nBulletCoolTime;				//攻撃のクールタイム
	static bool					m_bDie;							//生きているかどうか
	int							nConutBullet[MAX_BOSS_BULLET];	//バレット数
	D3DXVECTOR3					m_rot[MAX_BOSS_BULLET];			//エネミーの向き
	bool						m_bBullet[MAX_BOSS_BULLET];		//使用しているか
	CBossAnime					*m_BossAnime;					//ボスのアニメーションクラス
	CBulletBase					*m_pBullet;						//バレットクラス

};
#endif
