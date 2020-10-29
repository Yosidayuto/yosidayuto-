#ifndef _BULLET_H_
#define _BULLET_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"

//----------------------------------------------
//クラス
//----------------------------------------------
class CBullet :public CScene2d
{
public:
	CBullet(int nPriorit = 1);			//コンストラクタ
	~CBullet();			//デストラクタ	
	typedef enum  //バレット種類
	{
		BULLET_TYPE_PLAYER = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_BOSS,
		BULLET_TYPE_MAX
	}BULLET_TYPE;


	HRESULT Init(D3DXVECTOR3 move, BULLET_TYPE Type);	//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理
	static CBullet*
		Create(D3DXVECTOR3 Pos, D3DXVECTOR3 move, BULLET_TYPE Type);	//生成処理
	static HRESULT Load(void);		//テクスチャ読み込み
	static void Unload(void);		//テクスチャの破棄
private:
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;					//移動量
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	int	nLife;								//球の射程距離
	BULLET_TYPE m_Type;						//球の種類
};
#endif