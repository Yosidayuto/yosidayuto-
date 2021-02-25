#pragma once
#ifndef _FADE_H
#define _FADE_H

/*インクルードファイル*/
#include"main.h"
/*構造体*/
typedef enum
{
	FADE_NONE = 0,		//何もない状態
	FADE_IN,			//フェード処理
	FADE_OUT,			//フェードアウト処理
	FADE_MAX
}FADE;
/*プロトタイプ宣言*/
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdaFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);


FADE GetFade(void);

#endif