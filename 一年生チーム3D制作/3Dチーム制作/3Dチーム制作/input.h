#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNNGS
//�C���N���[�h�t�@�C��
#include"main.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT luitkeyboard(HINSTANCE hInstance, HWND hWnd);
void Uninitkeyboard(void);
void Updatekeyboard(void);
bool Getkeyboardpress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboarRelease(int nKey);
#endif