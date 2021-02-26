//=============================================================================
//
//	ゲーム背景マネージャー[game bg manager.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _GAME_BG_MANAGER_H_
#define _GAME_BG_MANAGER_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
//=============================================================================
// クラス定義
//=============================================================================
class CGameBgManager :public CScene
{
public:
	CGameBgManager(int nPriorit = PRIORITY_BG_0);	//コンストラクタ
	~CGameBgManager();								//デストラクタ

	static HRESULT			Load(void);		//テクスチャ読み込み
	static void				Unload(void);	//テクスチャの破棄
	static CGameBgManager*	Create(void);	//生成処理

	HRESULT			Init(void);		//初期化処理
	void			Uninit(void);	//終了処理
	void			Update(void);	//更新処理
	void			Draw(void);		//描画処理

private:

};
#endif