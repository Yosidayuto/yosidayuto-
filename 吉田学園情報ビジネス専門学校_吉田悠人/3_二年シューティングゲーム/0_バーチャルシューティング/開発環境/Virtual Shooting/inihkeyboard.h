#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define NUM_KEY_MAX (256)						//キーの最大数
//---------------------------------------------------
//インクルードファイル
//---------------------------------------------------
#include"main.h"
#include"input.h"
//---------------------------------------------------
//クラス
//---------------------------------------------------
class CInihKeyboard :public CInput
{
public:
	CInihKeyboard();
	~CInihKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetKeyPress(int nKey);
	bool GetKeyPressTrigger(int nKey);
	bool GetKeyPressRelease(int nKey);
private:
	BYTE m_akeyState[NUM_KEY_MAX];					//キーボードの入力情報ワーク
	BYTE m_aKesStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報
};

#endif