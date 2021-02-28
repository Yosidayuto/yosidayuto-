//=============================================================================
//
// インプット処理 [input.cpp]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
//=============================================================================
// クラス定義
//=============================================================================
class CInput
{
public:
	CInput();				//コンストラクタ
	virtual ~CInput();		//デストラクタ	

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	virtual void	Uninit(void);							// 終了処理
	virtual void	Update(void)=0;							// 更新処理
protected:
	LPDIRECTINPUTDEVICE8	m_pDevice;	//入力デバイス（キーボード）へのポインタ
	static LPDIRECTINPUT8	m_pInput;	//Directlnputオブジェクトのポインタ
};


#endif