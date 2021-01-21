#ifndef _ENEMY_H_
#define _ENEMY_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
#include "player.h"
//----------------------------------
//マクロ定義
//----------------------------------
#define MAX_ENEMY_BULLET 200
//----------------------------------------------
//クラス
//----------------------------------------------
class CEnemy:public CScene2d
{
public:

	CEnemy(int nPriorit=3);			//コンストラクタ
	~CEnemy();						//デストラクタ	
	typedef enum  //エネミー種類
	{
		ENEMY_TYPE_1 = 0,
		ENEMY_TYPE_2,
		ENEMY_TYPE_3,
		ENEMY_TYPE_4,
		ENEMY_TYPE_MAX
	}ENEMY_TYPE;

	typedef enum	//エネミーパターン
	{
		PATTERN_MODE_NONE = 0,	//NULL
		PATTERN_MODE_STRAIGHT,	//直進
		PATTERN_MODE_CROSS,		//交差
		PATTERN_MODE_CORNER,	//曲がる
		PATTERN_MODE_SIDE,		//横移動
		PATTERN_MODE_U_TURN,	//Uターン
		PATTERN_MODE_ROUND_TRIP,//往復
		PATTERN_MODE_STOP,		//ストップ
		PATTERN_MODE_MAX		//マックス
	}PATTERN_MODE;
	typedef enum	//エネミーパターン
	{
		BULLET_PATTERN_NONE = 0,		//NULL
		BULLET_PATTERN_SHOTS,			//通常ショット
		BULLET_PATTERN_HOMING,			//追尾ショット
		BULLET_PATTERN_BUCKSHOT,		//散弾ショット
		BULLET_PATTERN_SPIRAL,			//螺旋ショット
		BULLET_PATTERN_All_DIR,			//全方位ショット
		BULLET_PATTERN_MAX				//マックス
	}BULLET_PATTERN;


	static CEnemy*	Create(D3DXVECTOR3 Pos, ENEMY_TYPE  nType, 
		PATTERN_MODE nPattern,int nCountPattern=0,
		BULLET_PATTERN BulletMode = BULLET_PATTERN_NONE,
		D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE / 2, PLAYER_SIZE / 2, 0.0f));//生成処理
	static HRESULT	Load(void);				//テクスチャ読み込み
	static void		Unload(void);			//テクスチャの破棄

	HRESULT			Init(void);						//初期化処理
	void			Uninit(void);					//終了処理
	void			Update(void);					//更新処理
	void			Draw(void);						//描画処理
	void			SetTexture(ENEMY_TYPE nType);	//テクスチャの設定
	void			Damage(int nDamage);			//ダメージ処理
private:
	typedef enum	//エネミーの状態
	{
		STATS_MODE_NONE = 0,	//NULL
		STATS_MODE_NORMAL,		//通常状態
		STATS_MODE_DAMAGE,		//ダメージ状態
		STATS_MODE_DEATH		//死
	}STATS_MODE;

	STATS_MODE		m_Stats;				//エネミーの状態
	void			StatasManage(void);		//状態管理

	void		Rotate(void);								//回転処理
	void		Bullet(BULLET_PATTERN BulletMode);			//バレット処理
	D3DXVECTOR3	Tracking(float fSpeed);						//追尾処理
	D3DXVECTOR3 Random(float fSpeed);						//ランダム処理
	float Spiral(void);						//螺旋処理
	void		Move(D3DXVECTOR3 pos);						//移動処理									//移動処理
	void		Hit(D3DXVECTOR3 Pos);								//当たり判定
	static char					*pTexture[ENEMY_TYPE_MAX];	//テキスト名
	static LPDIRECT3DTEXTURE9	m_Texture[ENEMY_TYPE_MAX];	//テクスチャのポインタ
	D3DXVECTOR3					m_pos;						//エネミー座標
	D3DXVECTOR3					m_move;						//エネミーの移動量
	D3DXVECTOR3					m_size;						//エネミーのサイズ
	ENEMY_TYPE					m_Type;						//エネミーのタイプ
	PATTERN_MODE				m_Pattern;					//エネミーの行動パターン
	BULLET_PATTERN				m_BulletMode;				//バレットモード
	int							m_nLife;					//エネミーのライフ
	int							m_nScore;					//エネミーのスコア
	int							m_PatternCount;				//パターンのカウント
	
	int							nConutBullet[MAX_ENEMY_BULLET];	//バレット数
	D3DXVECTOR3					m_rot[MAX_ENEMY_BULLET];	//エネミーの向き
	bool						m_bBullet[MAX_ENEMY_BULLET];

};
#endif
