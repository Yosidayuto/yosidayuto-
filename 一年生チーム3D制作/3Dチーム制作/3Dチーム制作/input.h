#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNNGS
//インクルードファイル
#include"main.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT luitkeyboard(HINSTANCE hInstance, HWND hWnd);
void Uninitkeyboard(void);
void Updatekeyboard(void);
bool Getkeyboardpress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboarRelease(int nKey);
#endif