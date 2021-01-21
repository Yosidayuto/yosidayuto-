#ifndef _PLAYER_H_
#define _PLAYER_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
//------------------------------------
//マクロ定義
//------------------------------------
#define MAX_WEAPON 2
#define PLAYER_SIZE 100

//------------------------------------
//前置処理
//------------------------------------
class CLife;
typedef enum	//プレイヤーの武装
{
	WEAPONS_MODE_NONE = 0,	//NULL
	WEAPONS_MODE_BUTTOL,	//バレット
	WEAPONS_MODE_LASER,		//レーザー
	WEAPONS_MODE_HOMING,	//ホーミング
	WEAPONS_MODE_MAX
}WEAPON_MODE;

//----------------------------------------------
//クラス
//----------------------------------------------
class CPlayer :public CScene2d
{
public:
	CPlayer(int nPriorit = 4);			//コンストラクタ
	~CPlayer();			//デストラクタ	

	static CPlayer*	Create(D3DXVECTOR3 Pos);	//生成処理
	static void		Unload(void);		//テクスチャの破棄
	static HRESULT	Load(void);		//テクスチャ読み込み
	
	HRESULT			Init(void);				//初期化処理
	void			Uninit(void);			//終了処理
	void			Update(void);			//更新処理
	void			Draw(void);				//描画処理
	void			Set(D3DXVECTOR3 Pos);	//設置位置
	void			Damage(int nDamage);	//ダメージ処理
	int				GetLife(void) { return m_nLife; };//ライフゲット
	float			GetSpeed(void) { return m_fSpeed; };//スピードゲット
private:
	void			StatasManage(void);		//状態管理処理
	D3DXVECTOR3		MoveLimit(D3DXVECTOR3 pos, float fAngle);		//移動制限処理
	void			Weapon(D3DXVECTOR3 pos, int nWeapon);
	typedef enum	//プレイヤーの状態
	{
		STATS_MODE_NONE = 0,	//NULL
		STATS_MODE_NORMAL,		//通常状態
		STATS_MODE_DAMAGE,		//ダメージ状態
		STATS_MODE_DEATH		//死
	}STATS_MODE;

	STATS_MODE					Stats;		//プレイヤーの状態

	static D3DXVECTOR3			posMove;	//移動量
	static LPDIRECT3DTEXTURE9	m_pTexture;	//テクスチャのポインタ
	static int					m_nLife;	//ライフ
	static float				m_fSpeed;	//スピード
	static WEAPON_MODE			m_Weapon[MAX_WEAPON];//装備中武装
	CLife						*pLife;		//ライフポインタ
	int							nDamageTime;//ダメージ状態の無敵時間
	int							nCountWeapon[MAX_WEAPON];
};
#endif