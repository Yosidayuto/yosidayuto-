//=============================================================================
//
// キーボード処理 [inputkeyboard.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256)	//キーの数

//*****************************************************************************
// キーボードクラス
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// コンストラクタ
	~CInputKeyboard();								// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	bool GetKeyPress(int nKey);						// プレス状態を取得
	bool GetKeyTrigger(int nKey);					// トリガー状態を取得
	bool GetKeyRelease(int nKey);					// リリース状態を取得

private:
	BYTE m_akeyState[NUM_KEY_MAX];					// キーボードの入力情報ワーク
	BYTE m_akeyStateTrigger[NUM_KEY_MAX];			// キーボードのトリガーワーク
	BYTE m_akeyStateRelease[NUM_KEY_MAX];			// キーボードのトリガーワーク


};



#endif // !_INPUT_KEYBOARD_H_





