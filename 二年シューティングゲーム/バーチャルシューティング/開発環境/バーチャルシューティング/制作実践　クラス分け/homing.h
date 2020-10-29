#ifndef _HOMING_H_
#define _HOMING_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//クラス
//----------------------------------------------
class CHoming :public CScene2d
{
public:
	CHoming(int nPriorit = 1);			//コンストラクタ
	~CHoming();			//デストラクタ	
	typedef enum  //バレット種類
	{
		HOMING_TYPE_PLAYER = 0,
		HOMING_TYPE_ENEMY,
		HOMING_TYPE_BOSS,
		HOMING_TYPE_MAX
	}HOMING_TYPE;

	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);		//テクスチャの破棄
	static CHoming*	Create(D3DXVECTOR3 Pos, int nSpeed, HOMING_TYPE Type);	//生成処理


	HRESULT Init(int nSpeed, HOMING_TYPE Type);	//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理


private:
	int	TargetGet(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos);		//ターゲット
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_move;
	int			m_nSpeed;					//スピード
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	int	nLife;								//球の射程距離
	HOMING_TYPE m_Type;						//球の種類

};
#endif