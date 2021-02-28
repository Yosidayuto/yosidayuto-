//=============================================================================
//
// ボスタイプ3処理 [boss type3.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BOSS_TYPE_3_H_
#define _BOSS_TYPE_3_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "boss base.h"
//=============================================================================
//前方宣言
//=============================================================================
class CBossEffectBase;
//=============================================================================
// クラス定義
//=============================================================================
class CBossType3 :public CBossBase
{
public:
	CBossType3(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ
	~CBossType3();									//デストラクタ	

	static HRESULT		Load(void);					// テクスチャ読み込み
	static void			Unload(void);				// テクスチャの破棄
	static CBossType3*	Create(D3DXVECTOR3 pos);	// 生成処理

	HRESULT Init(void);			// 初期化処理
	void	Uninit(void);		// 終了処理
	void	Update(void);		// 更新処理
	void	Draw(void);			// 描画処理

	void	Effect(void);		//エフェクト生成
	void	DisEffect(void);	//倒されたときのエフェクト処理

private:
	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
	CBossEffectBase*	m_Effect;		// エフェクトポインタ

};
#endif