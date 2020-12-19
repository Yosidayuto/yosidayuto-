//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 俵谷 健太郎
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// レンダリングクラス
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();												// コンストラクタ
	~CRenderer();												// デストラクタ
	HRESULT Init(HWND hWnd, bool bWindow);						// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイスの取得
private:
	void DrawFPS(void);											// FPS処理
	LPDIRECT3D9				m_pD3D = NULL;						// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;				// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;						// フォントへのポインタ
#endif

};





#endif // !_RENDERER_H_






