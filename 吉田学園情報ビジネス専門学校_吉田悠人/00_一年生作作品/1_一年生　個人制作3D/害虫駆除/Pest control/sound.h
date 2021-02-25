//=============================================================================
// サウンド処理 [sound.h]
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// スタート画面
	SOUND_LABEL_BGM001,			// チュートリアル画面
	SOUND_LABEL_BGM002,			// 戦闘画面
	SOUND_LABEL_BGM003,			//ゲームクリア
	SOUND_LABEL_BGM004,			//ゲームオーバー

	SOUND_LABEL_SE_SELECT,		//選択音a
	SOUND_LABEL_SE_DECIDED,		//決定音a
	SOUND_LABEL_SE_DAMAGE,		//プレイヤーダメージ
	SOUND_LABEL_SE_DAMAGEBOOS,	//ムカデにダメージ
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_ITEM,		//アイテム取得音
	SOUND_LABEL_SE_MAGIC1,		//弱攻撃
	SOUND_LABEL_SE_MAGIC2,		//強攻撃

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
