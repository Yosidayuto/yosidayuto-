//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 俵谷 健太郎　吉田悠人
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "renderer.h"
#include "input_keyboard.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInputKeyboard;
class CPolygon;
class CInhMouse;
class CTitle;
class CWait;
class CGame;
class CResult;
class CFade;
class CCommunication;
class CSound;
class CLoad;
//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_LOAD,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;
	CManager();													// コンストラクタ
	~CManager();												// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CRenderer *GetRenderer(void);						// レンダリングの取得
	static CInputKeyboard *Getkeyboard(void);					// キーボードの取得
	static CInhMouse *GetMouse(void);							// マウスの取得
	static CPolygon *GetPolygon(void);							// ポリゴンナンバーの取得
	static void SetMode(MODE mode);								// モード切替
	static MODE GetMode(void);									// モードの取得
	static CFade *GetFade(void);								// フェードの取得
	static CCommunication*GetCommunication(void);				// 通信の取得		
	static CSound *GetSound(void);								// サウンドの取得

private:

	static CRenderer *m_pRenderer;								// レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;					// キーボードのポインタ
	static CPolygon *m_pPolygon;								// ポリゴンナンバーのポインタ
	static CInhMouse *m_pInputMouse;							// マウスのポインタ
	static CTitle *m_pTitle;									// タイトルのポインタ
	static CLoad *m_pLoad;										// ロードのポインタ
	static CGame *m_pGame;										// ゲームのポインタ
	static CResult *m_pResult;									// リザルトのポインタ
	static MODE m_mode;											// モードの変数
	static CFade *m_pFade;										// フェードのポインタ
	static CCommunication *pCommunication;						// 通信のポインタ
	static CSound *m_pSound;									// サウンドのポインタ
};




#endif








