//=============================================================================
//
// 分裂ショット処理 [split shots.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _SPLIT_SHOTS_H_
#define _SPLIT_SHOTS_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "shots base.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SPLIT_SHOTS (20)		//弾数
//=============================================================================
//  前方宣言
//=============================================================================
class CEnemyBullet;
//=============================================================================
// クラス定義
//=============================================================================
class CSplitShots :public CShotsBase
{
public:
	CSplitShots();					// コンストラクタ
	~CSplitShots();					// デストラクタ	

	static CSplitShots*	Create(D3DXVECTOR3 pos);	// 生成処理
	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Shots(void);	// ショット処理

private:
	int	 m_nBullet;						// 発射するまでのカウント
	bool m_bBullet[MAX_SPLIT_SHOTS];	// 弾丸を撃ったか
	CEnemyBullet* m_pEnemyBullet;		// 最初に出す弾丸のポインタ
};
#endif
