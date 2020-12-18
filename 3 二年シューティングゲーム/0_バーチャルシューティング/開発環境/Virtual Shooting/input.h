#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNNGS

//インクルードファイル
#include"main.h"
//インプットクラス
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void)=0;
protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;	//入力デバイス（キーボード）へのポインタ
	static LPDIRECTINPUT8 m_pInput;	//Directlnputオブジェクトのポインタ
};


#endif