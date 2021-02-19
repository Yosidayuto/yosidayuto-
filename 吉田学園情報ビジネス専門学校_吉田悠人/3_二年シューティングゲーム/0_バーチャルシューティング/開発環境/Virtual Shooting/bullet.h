//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"
#include "bullet base.h"
//=============================================================================
// クラス定義
//=============================================================================
class CBullet :public CBulletBase
{
public:
	CBullet();						//コンストラクタ
	~CBullet();						//デストラクタ	
	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//生成処理

	HRESULT Init(void);				// 初期化処理
	void	Uninit(void);			// 終了処理
	void	Update(void);			// 更新処理
	void	Draw(void);				// 描画処理
	void	Move(void);				// 移動処理
	void	Bullet(CScene* pObj);	// バレット処理
private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
};
#endif