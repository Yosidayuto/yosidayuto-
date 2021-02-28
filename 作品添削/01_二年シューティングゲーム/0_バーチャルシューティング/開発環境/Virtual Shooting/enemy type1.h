//=============================================================================
//
// エネミータイプ1処理 [enemy type1.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _ENEMY_TYPE_1_H_
#define _ENEMY_TYPE_1_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "enemy base.h"
//=============================================================================
//前方宣言
//=============================================================================

//=============================================================================
// クラス定義
//=============================================================================
class CEnemyType1 :public CEnemyBase
{
public:
	CEnemyType1();	//コンストラクタ
	~CEnemyType1();									//デストラクタ	

	static HRESULT		Load(void);					// テクスチャ読み込み
	static void			Unload(void);				// テクスチャの破棄

	static CEnemyType1*	Create( ENEMY_MOVE_PATTERN MoveType,		// 行動パターン
								ENEMY_ATTACK_PATTERN AttackType,	// 攻撃パターン
								int nInTime,						// 出現タイム
								int nActionTime,					// アクションタイム
								int nAttacTime,						// アタックタイム
								int nReturnTime,					// リターンタイム
								D3DXVECTOR3 pos,					// 出現位置
								float fSpeed,						// スピード
								int nLife);							// ライフ

	HRESULT Init(void);				// 初期化処理
	void	Uninit(void);			// 終了処理
	void	Update(void);			// 更新処理
	void	Draw(void);				// 描画処理

private:
	static TEXTURE_DATA	m_TextureData;					// テクスチャデータ

};
#endif