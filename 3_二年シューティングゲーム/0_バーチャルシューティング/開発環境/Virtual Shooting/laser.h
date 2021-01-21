//=============================================================================
//
// レーザー処理 [laser.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _LASER_H_
#define _LASER_H_
//----------------------------------------------
//ヘッダーファイル
//----------------------------------------------
#include"main.h"
#include"scene2d.h"
#define MAX_ENEMY (100)

//----------------------------------------------
//クラス
//----------------------------------------------
class CLaser :public CScene2d
{
public:
	CLaser(int nPriorit = 1);	//コンストラクタ
	~CLaser();					//デストラクタ	
	typedef enum				//バレット種類
	{
		LASER_TYPE_PLAYER = 0,
		LASER_TYPE_ENEMY,
		LASER_TYPE_MAX
	}LASER_TYPE;

	static HRESULT	Load(void);						//テクスチャ読み込み
	static void		Unload(void);					//テクスチャの破棄
	static CLaser	*Create(D3DXVECTOR3 Pos, D3DXVECTOR3 move, LASER_TYPE Type);	//生成処理

	HRESULT Init(D3DXVECTOR3 move, LASER_TYPE Type);	//初期化処理
	void	Uninit(void);								//終了処理
	void	Update(void);								//更新処理
	void	Draw(void);									//描画処理


private:
	bool						m_Hit[MAX_ENEMY];					//当たったことがあるか？
	D3DXVECTOR3					m_move;				//移動量
	static LPDIRECT3DTEXTURE9	m_pTexture;			//テクスチャのポインタ
	int							nLife;				//球の射程距離
	LASER_TYPE					m_Type;				//球の種類

};
#endif