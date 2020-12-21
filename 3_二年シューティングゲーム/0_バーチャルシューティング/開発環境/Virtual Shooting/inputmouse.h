#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_
#define NUM_CLICK_MAX (3)						//キーの最大数

//=============================================================================
//フラグ
//=============================================================================
#define MOUSE_POS_TYPE
#undef MOUSE_POS_TYPE

//=============================================================================
// ヘッダファイル
//=============================================================================
#include"main.h"
#include "input.h"

//=============================================================================
// クラス
//=============================================================================
class CInihMouse :public CInput
{
public:
	CInihMouse();
	~CInihMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);
#else 
	POINT		GetMousePos(void);
#endif


	bool GetClick(int nClick);
	bool GetClickTrigger(int nClick);
	bool GetClickRelease(int nClick);
private:
	DIMOUSESTATE m_aClickState;			//マウスの入力情報ワーク
	DIMOUSESTATE m_aClickTrigger;		//マウスのトリガー情報
	DIMOUSESTATE m_aClickRelease;		//マウスのリリース情報
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE m_aMousePos;			//マウスの移動量
#else 
	POINT posMouse;						//マウスの座標
	HWND hPointerpos;					//ウィンドウのマウスポインターの座標
#endif



};



#endif