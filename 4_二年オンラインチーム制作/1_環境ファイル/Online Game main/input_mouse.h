//=============================================================================
//
// マウス処理 [input_mouse.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_

#define NUM_CLICK_MAX (3)						//キーの最大数

//=============================================================================
//フラグ
//=============================================================================
//マウスのポインター取得の変更
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
class CInhMouse : public CInput
{
public:
	CInhMouse();									// コンストラクタ
	~CInhMouse();									// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);					// マウスポインターの移動量
#else 
	POINT		GetMousePos(void);					// マウスポインターの位置
#endif
	bool GetClick(int nClick);						// プレス状態を取得
	bool GetClickTrigger(int nClick);				// トリガー状態を取得
	bool GetClickRelease(int nClick);				// リリース状態を取得
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