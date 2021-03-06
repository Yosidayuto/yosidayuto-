//=============================================================================
//
// レーザー処理 [laser.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _LASER_H_
#define _LASER_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"
#include "bullet base.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define HIT_ENEMI (10)	//レーザーが当たったか
//=============================================================================
// クラス定義
//=============================================================================
class CLaser :public CBulletBase
{
public:
	CLaser();						//コンストラクタ
	~CLaser();						//デストラクタ	
	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄
	static CLaser* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//生成処理

	HRESULT Init(void);				// 初期化処理
	void	Uninit(void);			// 終了処理
	void	Update(void);			// 更新処理
	void	Draw(void);				// 描画処理
	void	Move(void);				// 移動処理
	void	Bullet(CScene* pObj);	// バレット処理
private:
	static TEXTURE_DATA	m_TextureData;		// テクスチャデータ
	bool				m_bHit[HIT_ENEMI];	// ヒット確認
	int					m_nHitCount;		// ヒットカウント
};	
#endif