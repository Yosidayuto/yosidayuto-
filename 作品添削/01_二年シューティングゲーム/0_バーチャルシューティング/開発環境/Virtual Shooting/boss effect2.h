//=============================================================================
//
// ボスエフェクト2処理 [boss effect2.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BOSS_EFFECT_2_H_
#define _BOSS_EFFECT_2_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "boss effect base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBossEffectType2 :public CBossEffectBase
{
public:
	CBossEffectType2();								//コンストラクタ
	~CBossEffectType2();							//デストラクタ	

	static HRESULT				Load(void);			//テクスチャ読み込み
	static void					Unload(void);		//テクスチャの破棄
	static CBossEffectType2*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

	HRESULT Init(void);			//初期化処理
	void	Uninit(void);		//終了処理
	void	Update(void);		//更新処理
	void	Draw(void);			//描画処理

private:
	static TEXTURE_DATA		m_TextureData;	// テクスチャデータ

};
#endif