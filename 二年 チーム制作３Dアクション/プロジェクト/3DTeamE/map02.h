//=============================================================================
//
// マップ02 [map02.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MAP02_H_
#define _MAP02_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "gamemode.h"
#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CCamera;
class CStage02;
class CPlayer;
class CLightEnemy;
class CHeavyEnemy;
class CUav;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMap02 : public CGamemode
{
public:
	CMap02();
	~CMap02();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	CCamera* m_pCamera;					//カメラポインタ
	CPlayer* m_pPlayer;					//プレイヤーポインタ
	CStage02* m_pStage02;				//ステージモデルポインタ
	CUav *m_pUav;						//偵察機ポインタ
	CLightEnemy *m_pLightEnemy[4];			//軽装エネミーポインタ
	bool bCollEnemy;					//エネミーが増えているか

};
#endif
